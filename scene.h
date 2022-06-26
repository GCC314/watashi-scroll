#ifndef SCENE_H
#define SCENE_H

#include "block.h"
#include "entity.h"
#include "config.h"
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

class MapScene : public QGraphicsScene
{
public:
    MapScene(QWidget *parent);
    ~MapScene();
    void Load(int level);
    void Start();
    void Pause();
    void Clear();
    void Refresh();
    Entity* getWatashi(){return Watashi;}
private:
    QVector<Block*> qtbmap;
    QVector<Entity*> charas;
    Entity *Watashi;
    QTimer *tick;
    QWidget *parent;
    QGraphicsView *view;
    QJsonObject LevelInfo;
};

#endif // SCENE_H
