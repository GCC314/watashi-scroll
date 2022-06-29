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
#include <QBrush>

namespace ENTITYS{
    extern QHash<QString,QImage*> IMAGE_CACHE;
    extern QHash<QString,bool> ENTITY_ISFLOAT;
    extern QSet<QString> NPCS;
    extern QSet<QString> ITEMS;
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
    Entity(const QJsonObject& obj);
    Entity(){};
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
    static Entity* newEntity(const QJsonObject& obj,Entity* parent=nullptr);
    inline void setSpeedY(int v){
        Speed_y = v;
    }
    inline void setSpeedX(int v){
        Speed_x = v;
    }
    inline void setISpeedY(int v){
        intendSpeed_y = v;
    }
    inline void setISpeedX(int v){
        intendSpeed_x = v;
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
    inline int& getIntendtick(){
        return intendtick;
    }
    inline void deltaX(int delta){
        this->setX(this->x() + delta);
    }
    inline friend void bounce(Entity* atk,Entity* def,int delta){
        int coor = def->x() - atk->x();
        if(coor > 0) def->deltaX(delta);
        else if(coor < 0) def->deltaX(delta);
    }
protected:
    QString type;
    int intendSpeed_x,intendSpeed_y;
    int Speed_x,Speed_y;
    int acAc_y;
    bool isFloat;
    int intendtick;
public:
    virtual void attack(){}
    virtual void hit(){}
    bool onfloor = 1;
};

class Player : public Entity{
public:
    Player(const QJsonObject& obj);
    ~Player();
    int hp = 50;
    int state = 0;//state说明：0 自由移动、攻击 1 正在攻击，不能移动 2 可以移动，不能攻击（攻击之后的贤者时间） 3 受击，不能移动
    int counter = 0;
    void attack();
    void hit();
    void setStatusPic(QString sta);
    QGraphicsRectItem *blood;
    void setblood(int x);
    int dir; // -1 represents left,1 represents right
};

class Npc : public Entity{
public:
    Npc(const QJsonObject& obj);
    ~Npc();
    inline QString getName(){return name;}
private:
    QString name;
public:
    int hp = 50;
    int state = 0;
    int counter = 0;
    QJsonObject *heri;
    void hit();
    void setStatusPic(QString sta);
    QGraphicsRectItem *blood;
    void setblood(int x);
    int dir; // -1 represents left,1 represents right
};

class Bullet : public Entity{
public:
    Bullet(const int &speed,bool isW,Entity* parent);
    ~Bullet();
public:
    int hp;
    int speed;
    bool isW; // true represents the shooter is Watashi , false represents the shooter is npc;
};

class Item : public Entity{
public:
    Item(const QJsonObject& obj);
    ~Item();
    inline QString getName(){return name;}
private:
    QString name;
};

class Notice : public Entity{
public:
    Notice(const QJsonObject& obj);
    ~Notice();
    QString getMoji();
private:
    QString moji;
};

class Gate : public Entity{
public:
    Gate(const QJsonObject& obj);
    ~Gate();
    inline int getTo(){return to;}
private:
    int to;
};

#endif // ENTITY_H
