#include "entity.h"

QImage *ENTITYS::IMAGE_CACHE[ENTITYS::TYPE_NUM] = {nullptr};

Entity::Entity(int type)
{
    QGraphicsPixmapItem::setZValue(30.0);
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
}

Entity::Entity(int x,int y,int type){
    QGraphicsPixmapItem::setZValue(30.0);
    QGraphicsPixmapItem::setPos(x,y);
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(type),-ENTITYS::getImgY(type));
    acSpeed_x = acSpeed_y = 0;
}

Entity::Entity(int x,int y,int type,int sx,int sy){
    QGraphicsPixmapItem::setZValue(30.0);
    QGraphicsPixmapItem::setPos(x,y);
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(type),-ENTITYS::getImgY(type));
    acSpeed_x = sx;acSpeed_y = sy;
}
