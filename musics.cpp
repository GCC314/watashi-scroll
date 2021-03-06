#include "musics.h"
void MUSICS::bgmSet(QMediaPlayer *player,QMediaPlaylist *plist,QString level){
    plist->setPlaybackMode(QMediaPlaylist::Loop);
    plist->addMedia(QUrl("qrc:/bgm/" + level + ".mp3"));
    player->setPlaylist(plist);
}

QQueue<QMediaPlayer*> MUSICS::squeue;
void MUSICS::soundsPlay(QString sname){
    if(squeue.size() > 20){
        auto u = squeue.front();
        delete u;
        squeue.pop_front();
    }
    QMediaPlayer *player = new QMediaPlayer();
    player->setMedia(QUrl("qrc:/sounds/" + sname + ".mp3"));
    player->setVolume(8);
    player->play();
    squeue.push_back(player);
}
