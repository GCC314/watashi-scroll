#include "musics.h"
void MUSICS::bgmSet(QMediaPlayer *player,int level){
    QString levelStr;levelStr.setNum(level);
    player->setMedia(QUrl("qrc:/bgm/" + levelStr + ".mp3"));
}
void MUSICS::soundsSet(QMediaPlayer *player,QString sname){
    player->setMedia(QUrl("qrc:/sounds/" + sname + ".mp3"));
}
