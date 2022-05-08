#ifndef SCENE_H
#define SCENE_H

#include "block.h"
#include "entity.h"
#include "config.h"
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

typedef struct __map_block_info{
    int type;
} Map_BLinfo;

typedef struct __map_entity_info{
    int x,y,type;
} Map_ENinfo;

class MapScene : public QGraphicsScene
{
public:
    MapScene();
    ~MapScene();
    void Load(int level);
    void Wakeup();
    Entity* getWatashi(){return Watashi;}
private:
    Map_BLinfo **map;
    Block **qtbmap;
    QVector<Entity*> charas;
    Entity *Watashi;
    QTimer *tick;
};

#endif // SCENE_H
