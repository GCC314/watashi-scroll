#ifndef ENTITY_H
#define ENTITY_H

#include "config.h"
#include "block.h"
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
    inline QImage& getImgcache(QString t,QString status=""){
        if(status != ""){
            t += "-" + status;
        }
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
    inline bool getFloat(){
        return isFloat;
    }
    inline QString getType(){
        return type;
    }
    inline int getISpeedX(){
        return intendSpeed_x;
    }
    inline int getISpeedY(){
        return intendSpeed_y;
    }
    inline void shiftISpeedX(int delta){
        intendSpeed_x += delta;
    }
    inline void shiftISpeedY(int delta){
        intendSpeed_y += delta;
    }
    inline void shiftSpeedY(int delta){
        Speed_y += delta;
    }
    inline void shiftSpeedX(int delta){
        Speed_x += delta;
    }
    static Entity* newEntity(const QJsonObject& obj);
    inline void setSpeedY(int v){
        Speed_y = v;
    }
    inline void setSpeedX(int v){
        Speed_x = v;
    }
    inline int getSpeedY(){
        return Speed_y;
    }
    inline int getSpeedX(){
        return Speed_x;
    }
    inline void setAcY(int a){
        acAc_y = a;
    }
    inline int getAcY(){
        return acAc_y;
    }
private:
    QString type;
    int intendSpeed_x,intendSpeed_y;
    int Speed_x,Speed_y;
    int acAc_y;
    bool isFloat;
};

class Player : public Entity{
public:
    Player(const QJsonObject& obj);
};

class Npc : public Entity{
public:
    Npc(const QJsonObject& obj);
};

class Item : public Entity{
public:
    Item(const QJsonObject& obj);
};

class Notice : public Entity{
public:
    Notice(const QJsonObject& obj);
    QString getMoji();
private:
    QString moji;
};

class Gate : public Entity{
public:
    Gate(const QJsonObject& obj);
};

#endif // ENTITY_H
