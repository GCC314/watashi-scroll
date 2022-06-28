#include "scene.h"
#include <QFile>


MapScene::MapScene(QWidget *parent)
{
    this->parent = parent;
    moji = nullptr;
    BGM = new QMediaPlayer;
    BGM->setVolume(30);
    Sounds = new QMediaPlayer;
    Sounds->setVolume(30);
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
            this->Watashi = ett;
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

    MUSICS::bgmSet(BGM,level);
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
    charas.clear();
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
    Start();
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
    for(auto ett : charas){
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
    qDebug("picked it up %s",it->getName().toStdString().c_str());
    this->removeItem(it);
}

void MapScene::Refresh(){
    int ground = LevelInfo["ground"].toInt();
    int xmin = LevelInfo["xmin"].toInt();
    int xmax = LevelInfo["xmax"].toInt();
    for(auto it = ItemList.begin();it != ItemList.end();){
        if(Watashi->collidesWithItem(*it)){
            Pickup(*it);
            it = ItemList.erase(it);
        }else it++;
    }
    for(auto ett : charas){
        if(ENTITYS::getEttFloat(ett->getType())) continue;

        ett->setSpeedX(ett->getISpeedX());
        //Y axis move
        int y0 = ett->y();
        QGraphicsLineItem bot(ett->x(),y0,ett->x() - ENTITYS::getImgX(ett->getType()),y0);

        [&](){
            // Deal with Y Axis (Using Lambda function to make it clear?)

            // 1. on the floor OR block
            bool ff = false;
            if(y0 >= ground) ff = true;
            else for(auto blo : qtbmap){
                if(bot.collidesWithItem(blo,Qt::IntersectsItemShape)){
                    ff = true;
                    break;
                }
            }
            if(ff){
                if(ett->getSpeedY() > 0) ett->setSpeedY(0);
                else ett->setSpeedY(min(ett->getISpeedY(),0));
//                qDebug("{floor}");
                return;
            }
            // 2. free but track intersects with floor OR block
            y0 += ett->getSpeedY();
            bot.setX(bot.x() + ett->getSpeedX());
            bot.setY(bot.y() + ett->getSpeedY());
            if(y0 >= ground){
                ett->setY(ground);
                ett->setSpeedY(0);
//                qDebug("{inter}");
                return;
            }else if(ett->getSpeedY() >= 0) for(auto blo : qtbmap){
                if(bot.collidesWithItem(blo,Qt::IntersectsItemShape)){
                    ett->setY(blo->y());
                    ett->setSpeedY(0);
//                    qDebug("{inter}");
                    return;
                }
            }
//            qDebug("{free}");
            // 3. free
            ett->shiftSpeedY(G);

        }();
        int tox = ett->x() + ett->getSpeedX();
        tox = max(tox,xmin);
        tox = min(tox,xmax);
        ett->setX(tox);
        ett->setY(ett->y() + ett->getSpeedY());
    }
    view->centerOn(Watashi);
}
