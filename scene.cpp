#include "scene.h"
#include <QFile>

MapScene::MapScene(QWidget *parent)
{
    this->parent = parent;
    moji = nullptr;
    BGM = new QMediaPlayer;
    BGM->setVolume(20);
    Sounds = new QMediaPlayer;
    Sounds->setVolume(9);
    qtbmap.clear();
    charas.clear();
    bgmlist = nullptr;
    GG = false;
}

MapScene::~MapScene(){
    MapScene::Clear();
}

void MapScene::Load(int level){
    view = new QGraphicsView(parent);
    view->setScene(this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->resize(SCREEN_X_WIDTH,SCREEN_Y_WIDTH);
    GG = false;
    nowlevel = level;

    QImage *bgImg = new QImage(bgimg_path(level));
    QGraphicsPixmapItem *bgitem = new QGraphicsPixmapItem();
    bgitem->setZValue(1.0);
    bgitem->setPos(0,0);
    bgitem->setPixmap(QPixmap::fromImage(*bgImg));
    this->addItem(bgitem);

    QFile jFile;
    // Load Info
    jFile.setFileName(infodata_path(level));
    jFile.open(QIODevice::ReadOnly);
    QTextStream *istream;
    istream = new QTextStream(&jFile);
    QString jsonStr;
    jsonStr = istream->readAll();
    QJsonDocument jDoc = QJsonDocument::fromJson(jsonStr.toLocal8Bit().data());
    LevelInfo = jDoc.object();
    [&](){
        // Deal With Level Info
    }();
    delete istream;
    jFile.close();

    // Load Block
    jFile.setFileName(blockdata_path(level));
    jFile.open(QIODevice::ReadOnly);
    istream = new QTextStream(&jFile);
    jsonStr = istream->readAll();
    jDoc = QJsonDocument::fromJson(jsonStr.toLocal8Bit().data());
    QJsonArray bList = jDoc.array();
    for(auto val : bList){
        qDebug().noquote() << QJsonDocument(val.toObject()).toJson();
        Block *blo = new Block(val.toObject());
        this->addItem(blo);
        qtbmap.append(blo);
    }
    delete istream;
    jFile.close();

    // Load Entity
    jFile.setFileName(entitydata_path(level));
    jFile.open(QIODevice::ReadOnly);
    istream = new QTextStream(&jFile);
    jsonStr = istream->readAll();
    jDoc = QJsonDocument::fromJson(jsonStr.toLocal8Bit().data());
    QJsonArray eList = jDoc.array();
    for(auto val : eList){
        qDebug().noquote() << QJsonDocument(val.toObject()).toJson();
        Entity *ett = Entity::newEntity(val.toObject());
        this->addItem(ett);
        charas.append(ett);
        qDebug(ett->getType().toStdString().c_str());
        if(ett->getType() == "watashi"){
            this->Watashi = (Player*)ett;
            view->centerOn(Watashi);
        }
        if(ett->getType() == "item"){
            ItemList.append((Item*)ett);
        }
    }
    delete istream;
    jFile.close();

    view->show();

    if(Watashi == nullptr) qDebug("Watashi mo nai");

    bgmlist = new QMediaPlaylist();
    MUSICS::bgmSet(BGM,bgmlist,"1");
    BGM->play();

    tick = new QTimer();
    connect(tick,&QTimer::timeout,[&](){
//        qDebug("Time elapsed");
        Refresh();
    });
}

void MapScene::Start(){
    if(!tick->isActive()){
        tick->start(INTERVAL);
    }
}

void MapScene::Pause(){
    if(tick->isActive()){
        tick->stop();
    }
}

void MapScene::Clear(){
    delete view;
    this->clear();
    foreach(Entity* p,GC){
        delete p;
    }
    GC.clear();
    charas.clear();
    foreach(Block* p,qtbmap){
        // delete p;
    }
    qtbmap.clear();
    ItemList.clear();
    Watashi = nullptr;
    view = nullptr;
    BGM->stop();
}

void MapScene::Teleport(int level){
    Pause();
    Clear();
    Load(level);
    Start();
}

void MapScene::DoX(){
    if(moji == nullptr) return;
    moji->clear(this);
    delete moji;
    moji = nullptr;
    if(GG) Teleport(nowlevel);
    else Start();
}

void MapScene::DoZ(){
    auto ReadNotice = [&](Entity* ett){
        if(moji != nullptr) return;
        Pause();
        moji = new Moji(((Notice*)ett)->getMoji(),view);
        moji->show(this);
    };
    auto CrossGate = [&](Entity* ett){
        Teleport(((Gate*)ett)->getTo());
    };
    foreach(auto ett,charas){
        if(ett->getType() == "notice" && Watashi->collidesWithItem(ett)){
            ReadNotice(ett);
            return;
        }
        if(ett->getType() == "gate" && Watashi->collidesWithItem((ett))){
            CrossGate(ett);
            return;
        }
    }
}

void MapScene::Pickup(Item* it){
    //Deal
    MUSICS::soundsPlay("ba");
    qDebug("picked it up %s",it->getName().toStdString().c_str());
    if(it->getName() == "healpotion") Watashi->hp += 15;
    this->removeItem(it);
}

void MapScene::giveDeath(Entity* ett){
    if((Player*)(ett) == Watashi){
        Pause();
        moji = new Moji("You Dead!\nPress [X] to respawn.",view);
        moji->show(this);
        GG = true;
    }else{
        if(((Npc*)ett)->heri != nullptr){
            Entity *ntt = Entity::newEntity(*((Npc*)ett)->heri,ett);
            this->addItem(ntt);
            tmp.append(ntt);
            qDebug(ntt->getType().toStdString().c_str());
        }
        if(!GC.contains(ett)) GC.insert(ett);
    }
}

void MapScene::Shoot(Player* shooter){
    qDebug("Shoot");
    Bullet* bt = new Bullet(BULLET_SPEED * shooter->dir,true,shooter);
    this->addItem(bt);
    charas.append(bt);
    qDebug("Shot");
}
void MapScene::Shoot(Npc* shooter){
    qDebug("Shoot");
    Bullet* bt = new Bullet(BULLET_SPEED * shooter->dir,false,shooter);
    this->addItem(bt);
    charas.append(bt);
    qDebug("Shot");
}

void MapScene::Refresh(){
    tmp.clear();
    qDebug("Refresh");
    int ground = LevelInfo["ground"].toInt();
    int xmin = LevelInfo["xmin"].toInt();
    int xmax = LevelInfo["xmax"].toInt();
    for(auto it = ItemList.begin();it != ItemList.end();){
        if(Watashi->collidesWithItem(*it)){
            Pickup(*it);
            it = ItemList.erase(it);
        }else it++;
    }
    int cnt = 0;
    for(auto ett_ = charas.begin();ett_ != charas.end();ett_++){
        qDebug("chara %d",++cnt);
        if(GC.contains(*ett_)){
            continue;
        }
        auto ett = *(ett_);
        qDebug("%d %s",cnt,ett->getType().toStdString().c_str());
        if(ett->getType() == "item" || ett->getType() == "gate" || ett->getType() == "notice") continue;
        ett->setSpeedX(ett->getISpeedX());
        if(ett->getType() != "bullet") [&](){
            //Y axis move
            int y0 = ett->y();
            QGraphicsLineItem bot(ett->x(),y0,ett->x() - ENTITYS::getImgX(ett->getType()),y0);

            // Deal with Y Axis (Using Lambda function to make it clear?)

            // 1. on the floor OR block
            bool ff = false;
            if(y0 >= ground) ff = true;
            else foreach(auto blo,qtbmap){
                if(bot.collidesWithItem(blo,Qt::IntersectsItemShape)){
                    ff = true;
                    break;
                }
            }
            if(ff){
                if(ett->getSpeedY() > 0) ett->setSpeedY(0);
                else ett->setSpeedY(min(ett->getISpeedY(),0));
                return;
            }
            // 2. free but track intersects with floor OR block
            y0 += ett->getSpeedY();
            bot.setX(bot.x() + ett->getSpeedX());
            bot.setY(bot.y() + ett->getSpeedY());
            if(y0 >= ground){
                ett->setY(ground);
                ett->setSpeedY(0);
                return;
            }else if(ett->getSpeedY() >= 0) foreach(auto blo,qtbmap){
                if(bot.collidesWithItem(blo,Qt::IntersectsItemShape)){
                    ett->setY(blo->y());
                    ett->setSpeedY(0);
                    return;
                }
            }
            // 3. free
            ett->shiftSpeedY(G);
        }();

        if(ett->getType()=="watashi")
        {
            if(Watashi->state==1)
            {
                Watashi->setSpeedX(0);
                Watashi->setSpeedY(0);
                switch(Watashi->counter)
                {
                    case 1:
                        Watashi->setStatusPic("a");
                        //修改贴图至攻击
                        Watashi->counter++;
                        for(auto it = charas.begin();it != charas.end();)
                        {
                            if(GC.contains(*it)) continue;
                            if((*it)->getType()=="npc")
                                if(Watashi->collidesWithItem(*it))
                                {
                                    (*it)->hit();
                                    MUSICS::soundsPlay("biu");
                                    bounce(Watashi,*it,BOUNCE_BACK);
                                    if(((Npc*)(*it))->hp<=0){
                                        giveDeath(*it);
                                        if(!GC.contains(*it)) GC.insert(*it);
                                        continue;
                                    }
                                }
                           it++;
                        }
                        break;
                    case 5:
                        Watashi->state = 2;
                        Watashi->counter++;
                        break;
                    default:
                        Watashi->counter++;
                        break;
                }
            }
            else if(Watashi->state==2)
            {
                switch(Watashi->counter)
                {
                    case 6:
                        Watashi->setStatusPic("");
                        //修改贴图至正常行动
                        Watashi->counter++;
                        break;
                    case 10:
                        Watashi->state=0;
                        Watashi->counter=0;
                        break;
                    default:
                        Watashi->counter++;
                        break;
                }
            }
            else if(Watashi->state==3)
            {
                Watashi->setSpeedX(0);
                Watashi->setSpeedY(0);
                switch(Watashi->counter)
                {
                    case 1:
                        Watashi->setStatusPic("b");
                        Watashi->counter++;
                        break;
                    case 8:
                        Watashi->state=0;
                        Watashi->counter=0;
                        break;
                    default:
                        Watashi->counter++;
                        break;
                }
            }
            Watashi->setblood(Watashi->hp);
        }
        if(ett->getType()=="npc")
        {
            Npc* npt = (Npc*)ett;
            int wside = ++npt->getIntendtick() / NPC_TICK;
            npt->dir = wside & 1 ? -1 : 1;
            npt->setISpeedX(wside & 1 ? -NPC_SPEED : NPC_SPEED);
            if(npt->state==0)
            {
                if(npt->collidesWithItem(Watashi))
                {
                    npt->state=-1;
                    npt->counter=1;
                }
            }
            else if(npt->state==-1)
            {
                npt->setSpeedX(0);
                npt->setSpeedY(0);
                switch(npt->counter)
                {
                    case 1:
                        npt->counter++;
                        break;
                    case 5:
                        npt->state=1;
                        npt->counter=1;
                        break;
                    default:
                        npt->counter++;
                        break;
                }
            }
            else if(npt->state==1)
            {
                npt->setSpeedX(0);
                npt->setSpeedY(0);
                switch(npt->counter)
                {
                    case 1:
                        npt->setStatusPic("a");
                        //修改贴图为攻击
                        if(npt->collidesWithItem(Watashi))
                        {
                            (Watashi)->hit();
                            MUSICS::soundsPlay("biu");
                            bounce(npt,Watashi,BOUNCE_BACK);
                            if((Watashi)->hp<=0)
                                giveDeath(Watashi);
                        }
                        npt->counter++;
                        break;
                    case 5:
                        npt->state=0;
                        npt->counter=0;
                        break;
                    default:
                        npt->counter++;
                        break;
                }
            }
            else if(npt->state==3)
            {
                npt->setSpeedX(0);
                npt->setSpeedY(0);
                switch(npt->counter)
                {
                    case 1:
                        npt->setStatusPic("b");
                        //修改贴图至受击
                        npt->counter++;
                    break;
                    case 5:
                        npt->state = 0;
                        npt->counter = 0;
                    break;
                    default:
                        npt->counter++;
                    break;
                }
            }
            npt->setblood(npt->hp);
        }
        if(ett->getType() == "bullet"){
            Bullet* bt = (Bullet*)ett;
            if(bt->hp-- <= 0){
                GC.insert(bt);
                continue;
            }
            for(auto it = charas.begin();it != charas.end();it++){
                if(GC.contains(*it)) continue;
                if(bt->x() <= xmin || bt->x() >= xmax){
                    GC.insert(bt);
                    break;
                }
                if(!bt->collidesWithItem(*it)) continue;
                qDebug("it %s",(*it)->getType().toStdString().c_str());
                qDebug("it %d",bt->isW);
                if(bt->isW){
                    if((*it)->getType() == "npc"){
                        //hit Npc
                        (*it)->hit();
                        MUSICS::soundsPlay("biu");
                        bounce(bt,*it,BOUNCE_BACK);
                        if(((Npc*)(*it))->hp<=0){
                            giveDeath(*it);
                            if(!GC.contains(*it)) GC.insert(*it);
                        }
                        GC.insert(bt);
                        break;
                    }
                }else{
                    if((*it)->getType() == "watashi"){
                        // hit watashi
                        (Watashi)->hit();
                        MUSICS::soundsPlay("biu");
                        bounce(bt,Watashi,BOUNCE_BACK);
                        if((Watashi)->hp<=0)
                            giveDeath(Watashi);
                        GC.insert(bt);
                        break;
                    }
                }
            }
            for(auto it = qtbmap.begin();it != qtbmap.end();it++){
                if((*it)->collidesWithItem(bt)){
                    GC.insert(bt);
                    break;
                }
            }
        }
        int tox = ett->x() + ett->getSpeedX();
        tox = max(tox,xmin);
        tox = min(tox,xmax);
        ett->setX(tox);
        ett->setY(ett->y() + ett->getSpeedY());
    }
    for(auto ett_ = charas.begin();ett_ != charas.end();){
        if(GC.contains(*ett_)){
            this->removeItem(*ett_);
            GC.remove(*ett_);
            delete *ett_;
            ett_ = charas.erase(ett_);
        }else ett_++;
    }
    foreach(auto p,tmp) charas.append(p);
    view->centerOn(Watashi);
    qDebug("Refreshed");
}
