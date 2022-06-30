#ifndef CONFIG_H
#define CONFIG_H

#include <QDebug>
#include <QFile>
#include <QTextStream>

const int SCREEN_X_WIDTH = 640;
const int SCREEN_Y_WIDTH = 480;

#include <QString>
using namespace std;

const int G = 1;
const int xspeed = 5;
const int yspeed = 15;
const int INTERVAL = 50;

const int WATASHI_SPEED = 8;
const int NPC_SPEED = 6;
const int NPC_TICK = 30;
const int BOUNCE_BACK = 15;
const int BULLET_HP = 8;
const int BULLET_SPEED = 10;

const QString ROOT_PREFIX = ":/";
const QString TEXTURE_PATH_PREFIX = ROOT_PREFIX + "texture/";
const QString ATTR_PATH_PREFIX = ROOT_PREFIX + "attr/";
const QString MAP_DATA_PATH_PREFIX = ROOT_PREFIX + "map/level-";

inline QString data_path(int level){
    QString levelStr;
    return MAP_DATA_PATH_PREFIX + levelStr.setNum(level) + "/";
}
inline QString entitydata_path(int level){
    return data_path(level) + "entity.json";
}
inline QString blockdata_path(int level){
    return data_path(level) + "block.json";
}
inline QString infodata_path(int level){
    return data_path(level) + "info.json";
}
inline QString bgimg_path(int level){
    return data_path(level) + "bgimg.png";
}

#endif // CONFIG_H
