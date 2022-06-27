#include "scene.h"
#include <QFile>


MapScene::MapScene(QWidget *parent)
{
    this->parent = parent;
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
        Entity *ett = new Entity(val.toObject());
        this->addItem(ett);
        qDebug(ett->getType().toStdString().c_str());
        if(ett->getType() == "watashi"){
            this->Watashi = ett;
            view->centerOn(Watashi);
        }
    }
    delete istream;
    jFile.close();

    view->show();

    if(Watashi == nullptr) qDebug("Watashi mo nai");

    tick = new QTimer();
    connect(tick,&QTimer::timeout,[&](){
//        qDebug("Time elapsed");
        Refresh();
    });
}

void MapScene::Start(){
    if(!tick->isActive()){
        tick->start(100);
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
    Watashi = nullptr;
    view = nullptr;
}

void MapScene::ShowDialog(const QString& msg){
    if(moji != nullptr) return;
    Pause();
    moji = new Moji(msg,view);
    moji->show(this);
}

void MapScene::UnshowDialog(){
    if(moji == nullptr) return;
    moji->clear(this);
    delete moji;
    moji = nullptr;
    Start();
}

void MapScene::Refresh(){
    // TEST : ONLY TO MOVE
    //
    Watashi->setPos(Watashi->x() + Watashi->getSpeedX(),Watashi->y() + Watashi->getSpeedY());
    view->centerOn(Watashi);
}
