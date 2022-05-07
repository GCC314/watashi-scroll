#include "scene.h"
#include <QFile>



Scene::Scene(QGraphicsScene *qtScene)
{
    qtscene = qtScene;
    map = new Map_BLinfo *[X_NUM];
    qtbmap = new Block *[X_NUM];
    for(int x = 0;x < X_NUM;x++){
        map[x] = new Map_BLinfo [Y_NUM];
        qtbmap[x] = new Block [Y_NUM];
    }
    for(int x = 0;x < X_NUM;x++){
        for(int y = 0;y < Y_NUM;y++){
            qtbmap[x][y].setPos(x * BLOCK_SIZE,y * BLOCK_SIZE);
            qtscene->addItem(&qtbmap[x][y]);
        }
    }
}

Scene::~Scene(){
    for(int x = 0;x < X_NUM;x++){
        free(map[x]);
    }
    free(map);
}

void Scene::Load(int level){
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
    QGraphicsPixmapItem *px = new QGraphicsPixmapItem(QPixmap::fromImage(block_image_cache(0)));
    qtscene->addItem(px);
    for(int x = 0;x < X_NUM;x++){
        for(int y = 0;y < Y_NUM;y++){
            qDebug("%d %d [%d] \n",x,y,map[x][y].type);
        }
    }
}
