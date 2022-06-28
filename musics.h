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
#include <QQueue>

namespace MUSICS{
    void bgmSet(QMediaPlayer *player,QMediaPlaylist *plist,int level);
    void soundsPlay(QString sname);
    extern QQueue<QMediaPlayer*> squeue;
}
#endif // MUSICS_H
