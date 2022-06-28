#ifndef MUSICS_H
#define MUSICS_H

#include "config.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsItem>
#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

namespace MUSICS{
    void bgmSet(QMediaPlayer *player,QMediaPlaylist *plist,int level);
    void soundsSet(QMediaPlayer *player,QString sname);
}

#endif // MUSICS_H
