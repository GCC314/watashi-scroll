#ifndef ENTITY_H
#define ENTITY_H

#include "config.h"
#include <QMap>
#include <QGraphicsItem>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

namespace ENTITYS{
    extern QHash<QString,QImage*> IMAGE_CACHE;
    extern QHash<QString,bool> ENTITY_ISFLOAT;
    inline QString txtpath(const QString &t){
        return TEXTURE_PATH_PREFIX + "entity/" + t + QString(".png");
    }
    inline QImage& getImgcache(const QString &t){
        if(!IMAGE_CACHE.contains(t)){
            IMAGE_CACHE[t] = new QImage(txtpath(t));
        }
        return *(IMAGE_CACHE[t]);
    }
    inline int getImgX(const QString &t){
        return getImgcache(t).width();
    }
    inline int getImgY(const QString &t){
        return getImgcache(t).height();
    }
    inline bool getEttFloat(const QString &t){
        return ENTITY_ISFLOAT[t];
    }
    void init();
}

class Entity : public QGraphicsPixmapItem
{
public:
    Entity(const QString& type);
    Entity(int x,int y,const QString& type);
    Entity(const QJsonObject& obj);
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
    inline bool getFloat(){
        return isFloat;
    }
    inline QString getType(){
        return type;
    }
private:
    QString type;
    int acSpeed_x,acSpeed_y;
    bool isFloat;
};

class Player : public Entity{
    //
};

class Npc : public Entity{
    //
};

class Item : public Entity{
    //
};

class Notice : public Entity{
    //
};

class Gate : public Entity{
    //
};

#endif // ENTITY_H
