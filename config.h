#ifndef CONFIG_H
#define CONFIG_H

//#include <QDebug>

const int SCREEN_X_WIDTH = 640;
const int SCREEN_Y_WIDTH = 480;
const int BLOCK_SIZE = 16;
const int X_NUM = SCREEN_X_WIDTH / BLOCK_SIZE;
const int Y_NUM = SCREEN_Y_WIDTH / BLOCK_SIZE;
const int GOD_SPEED = 2;

#include <QString>
using namespace std;

const QString MAP_DATA_PATH_PREFIX = "/home/gcc314/dev/cxsj/watashi-scroll/map/level-";
inline QString mapdata_path(int level){
    QString levelStr;
    return MAP_DATA_PATH_PREFIX + levelStr.setNum(level);
}
inline QString entitydata_path(int level){
    QString levelStr;
    return MAP_DATA_PATH_PREFIX + levelStr.setNum(level) + "-entity";
}

#endif // CONFIG_H
