#ifndef BLOCK_H
#define BLOCK_H

#include "config.h"
#include <QGraphicsItem>

const int BLOCKS_TYPE_NUM = 2;
const int BLOCK_ID_BLANK = 0;
const int BLOCK_ID_DIRT = 1;
const QString BLOCK_ID_NAME[BLOCKS_TYPE_NUM] = {
    "blank",
    "dirt"
};
inline QString btexture_path(const int &t){
    return QString(":/block/assets/") + BLOCK_ID_NAME[t] + QString(".png");
}
extern QImage *BLOCKS_IMAGE_CACHE[BLOCKS_TYPE_NUM];
inline QImage& block_image_cache(const int &t){
    if(BLOCKS_IMAGE_CACHE[t] == nullptr){
        BLOCKS_IMAGE_CACHE[t] = new QImage(btexture_path(t));
    }
    return *(BLOCKS_IMAGE_CACHE[t]);
}

class Block : public QGraphicsPixmapItem
{
public:
    Block():type(-1){}
    inline int getType(){
        return type;
    }
    inline void setType(const int &x){
        type = x;
    }
    inline bool toggleBlock(const int &t){
        if(type == t) return false;
        this->setPixmap(QPixmap::fromImage(block_image_cache(t)));
        return true;
    }
private:
    int type;
};

#endif // BLOCK_H
