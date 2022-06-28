#include "musics.h"
void MUSICS::bgmSet(QMediaPlayer *player,QMediaPlaylist *plist,int level){
    plist->setPlaybackMode(QMediaPlaylist::Loop);
    QString levelStr;levelStr.setNum(level);
    plist->addMedia(QUrl("qrc:/bgm/" + levelStr + ".mp3"));
    player->setPlaylist(plist);
}
void MUSICS::soundsSet(QMediaPlayer *player,QString sname){
    player->setMedia(QUrl("qrc:/sounds/" + sname + ".mp3"));
}
