#ifndef BLOCK_H
#define BLOCK_H

#include "config.h"
#include <QGraphicsItem>

namespace BLOCKS{
    const int TYPE_NUM = 2;
    const int ID_BLANK = 0;
    const int ID_DIRT = 1;
    const QString ID_NAME[TYPE_NUM] = {
        "blank",
        "dirt"
    };

    inline QString txtpath(const int &t){
        return QString(":/block/assets/") + ID_NAME[t] + QString(".png");
    }
    extern QImage *IMAGE_CACHE[TYPE_NUM];
    inline QImage& getImgcache(const int &t){
        if(IMAGE_CACHE[t] == nullptr){
            IMAGE_CACHE[t] = new QImage(txtpath(t));
        }
        return *(IMAGE_CACHE[t]);
    }
}



class Block : public QGraphicsPixmapItem
{
public:
    Block():type(-1){QGraphicsPixmapItem::setZValue(15.0);}
    inline int getType(){
        return type;
    }
    inline void setType(const int &x){
        type = x;
    }
    inline bool toggleBlock(const int &t){
        if(type == t) return false;
        this->setPixmap(QPixmap::fromImage(BLOCKS::getImgcache(t)));
        return true;
    }
private:
    int type;
};

#endif // BLOCK_H
