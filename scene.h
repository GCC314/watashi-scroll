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
    void giveDeath(Entity* ett);
    void Teleport(int level);
    void Pickup(Item* it);
    void Shoot(Player* shooter);
    void Shoot(Npc* shooter);
    Entity* getWatashi(){return Watashi;}
    int nowlevel;
private:
    QVector<Block*> qtbmap;
    QVector<Entity*> charas;
    Player *Watashi;
    QTimer *tick;
    QWidget *parent;
    QGraphicsView *view;
    QJsonObject LevelInfo;
    QVector<Item*> ItemList;
    Moji *moji;
    QMediaPlayer *BGM;
    QMediaPlayer *Sounds;
    QMediaPlaylist *bgmlist;
    QSet<Entity*> GC;
    QVector<Entity*> tmp;
    bool GG;
};

#endif // SCENE_H
