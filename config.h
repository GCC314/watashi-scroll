#ifndef CONFIG_H
#define CONFIG_H

const int SCREEN_X_WIDTH = 640;
const int SCREEN_Y_WIDTH = 480;
const int BLOCK_SIZE = 32;
const int X_NUM = SCREEN_X_WIDTH / BLOCK_SIZE;
const int Y_NUM = SCREEN_Y_WIDTH / BLOCK_SIZE;

#include <QTextStream>
const QString MAP_DATA_PATH_PREFIX = "map/level-";
inline QString mapdata_path(int level){
    QString levelStr;
    return MAP_DATA_PATH_PREFIX + levelStr.setNum(level);
}

#endif // CONFIG_H
