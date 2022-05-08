#ifndef ENTITY_H
#define ENTITY_H

#include "config.h"
#include <QGraphicsItem>

namespace ENTITYS{
    const int TYPE_NUM = 1;
    const int ID_GOD = 0;
    const QString ID_NAME[TYPE_NUM] = {
        "god"
    };

    inline QString txtpath(const int &t){
        return QString(":/hero/assets/") + ID_NAME[t] + QString(".png");
    }
    extern QImage *IMAGE_CACHE[TYPE_NUM];
    inline QImage& getImgcache(const int &t){
        if(IMAGE_CACHE[t] == nullptr){
            IMAGE_CACHE[t] = new QImage(txtpath(t));
        }
        return *(IMAGE_CACHE[t]);
    }
    inline int getImgX(const int &t){
        if(IMAGE_CACHE[t] == nullptr){
            IMAGE_CACHE[t] = new QImage(txtpath(t));
        }
        return IMAGE_CACHE[t]->width();
    }
    inline int getImgY(const int &t){
        if(IMAGE_CACHE[t] == nullptr){
            IMAGE_CACHE[t] = new QImage(txtpath(t));
        }
        return IMAGE_CACHE[t]->height();
    }
}

class Entity : public QGraphicsPixmapItem
{
public:
    Entity(int type = -1);
    Entity(int x,int y,int type);
    Entity(int x,int y,int type,int sx,int sy);
    inline int getSpeedX(){
        return acSpeed_x;
    }
    inline int getSpeedY(){
        return acSpeed_y;
    }
    inline void shiftSpeedX(int delta){
        acSpeed_x += delta;
    }
    inline void shiftSpeedY(int delta){
        acSpeed_y += delta;
    }
private:
    int type;
    int acSpeed_x,acSpeed_y;
};

class Player : public Entity{
    //
};

class Npc : public Entity{
    //
};

class Barrier : public Entity{
    //
};

#endif // ENTITY_H
