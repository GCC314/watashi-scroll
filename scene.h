#ifndef SCENE_H
#define SCENE_H

#include "block.h"
#include "entity.h"
#include "config.h"
#include "popup.h"
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <cmath>

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
    void ShowDialog();
    void UnshowDialog();
    Entity* getWatashi(){return Watashi;}
//    bool check();
//    bool collide(Entity*, Block*);
//    inline double dis(int x1, int y1, int x2, int y2){
//        double re = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) *(y1 - y2));
//        return re;
//    }
//    QVector<Block*> blockVec;
private:
    QVector<Block*> qtbmap;
    QVector<Entity*> charas;
    Entity *Watashi;
    QTimer *tick;
    QWidget *parent;
    QGraphicsView *view;
    QJsonObject LevelInfo;
    Moji *moji;
};

#endif // SCENE_H
