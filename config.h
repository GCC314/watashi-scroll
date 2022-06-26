#ifndef CONFIG_H
#define CONFIG_H

#include <QDebug>
#include <QFile>
#include <QTextStream>

const int SCREEN_X_WIDTH = 640;
const int SCREEN_Y_WIDTH = 480;

#include <QString>
using namespace std;

const QString TEXTURE_PATH_PREFIX = "/home/gcc314/dev/cxsj/watashi-scroll/texture/";
const QString ATTR_PATH_PREFIX = "/home/gcc314/dev/cxsj/watashi-scroll/attr/";

const QString MAP_DATA_PATH_PREFIX = "/home/gcc314/dev/cxsj/watashi-scroll/map/level-";
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
