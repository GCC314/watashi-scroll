#ifndef SCENE_H
#define SCENE_H

#include "block.h"
#include "entity.h"
#include "config.h"
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsView>

typedef struct __map_block_info{
    int type;
} Map_BLinfo;

class Scene
{
public:
    Scene(QGraphicsScene *qtScene);
    ~Scene();
    void Load(int level);
    void Wakeup();
private:
    Map_BLinfo **map;
    Block **qtbmap;
    //QVector<Entity> charas;
    QGraphicsScene *qtscene;
};

#endif // SCENE_H
