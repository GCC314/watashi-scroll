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
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>
#include "musics.h"

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
    void DoZ();
    void DoX();
    void Teleport(int level);
    void Pickup(Item* it);
    Entity* getWatashi(){return Watashi;}
private:
    QVector<Block*> qtbmap;
    QVector<Entity*> charas;
    Entity *Watashi;
    QTimer *tick;
    QWidget *parent;
    QGraphicsView *view;
    QJsonObject LevelInfo;
    QVector<Item*> ItemList;
    Moji *moji;
    QMediaPlayer *BGM;
    QMediaPlayer *Sounds;
    QMediaPlaylist *bgmlist;
};

#endif // SCENE_H
