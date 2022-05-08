#include "scene.h"
#include <QFile>



MapScene::MapScene()
{
    map = new Map_BLinfo *[X_NUM];
    qtbmap = new Block *[X_NUM];
    for(int x = 0;x < X_NUM;x++){
        map[x] = new Map_BLinfo [Y_NUM];
        qtbmap[x] = new Block [Y_NUM];
    }
    for(int x = 0;x < X_NUM;x++){
        for(int y = 0;y < Y_NUM;y++){
            qtbmap[x][y].setPos(x * BLOCK_SIZE,y * BLOCK_SIZE);
            addItem(&qtbmap[x][y]);
        }
    }
}

MapScene::~MapScene(){
    for(int x = 0;x < X_NUM;x++){
        free(map[x]);
    }
    free(map);
}

void MapScene::Load(int level){
    QString filename = mapdata_path(level);
    QFile mapfile(filename);
    mapfile.open(QIODevice::ReadOnly);
    for(int x = 0;x < X_NUM;x++){
        mapfile.read((char*)(map[x]),sizeof(Map_BLinfo) * Y_NUM);
    }
    mapfile.close();
    for(int x = 0;x < X_NUM;x++){
        for(int y = 0;y < Y_NUM;y++){
            qtbmap[x][y].toggleBlock(map[x][y].type);
        }
    }
    filename = entitydata_path(level);
    QFile entityfile(filename);
    entityfile.open(QIODevice::ReadOnly);
    Map_ENinfo head;
    entityfile.read((char*)(&head),sizeof(Map_ENinfo));
    qDebug("%d\n",head.x);
    for(int i = 0;i < head.x;i++){
        Map_ENinfo now;
        entityfile.read((char*)(&now),sizeof(Map_ENinfo));
        qDebug("entity %d at %d %d\n",now.x,now.y,now.type);
        Entity *ne = new Entity(now.x,now.y,now.type);
        if(now.type == ENTITYS::ID_GOD){
            Watashi = ne;
        }
        charas.push_back(ne);
        addItem(ne);
    }
    entityfile.close();
    tick = new QTimer();
    connect(tick,&QTimer::timeout,[&](){
        //TODO : Triggered every 0.1s,deal with routine work;
        qDebug("Time elapsed");
        Watashi->setPos(Watashi->x() + Watashi->getSpeedX(),Watashi->y() + Watashi->getSpeedY());
    });
}

void MapScene::Wakeup(){
    if(!tick->isActive()){
        tick->start(100);
    }
}
