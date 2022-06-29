#include "entity.h"
#include <QtGlobal>
#include <QTime>
#include <cmath>

QHash<QString,QImage*> ENTITYS::IMAGE_CACHE;
QHash<QString,bool> ENTITYS::ENTITY_ISFLOAT;
QSet<QString> ENTITYS::NPCS;
QSet<QString> ENTITYS::ITEMS;

Entity::Entity(const QJsonObject &obj){
    int x = obj["x"].toInt();
    int y = obj["y"].toInt();
    QString type = obj["type"].toString();
    qDebug("%s [%d %d]\n",type.toStdString().c_str(),x,y);
    this->type = type;
    QGraphicsPixmapItem::setZValue(15.0);
    QGraphicsPixmapItem::setPos(x,y);
    isFloat = ENTITYS::getEttFloat(type);
    intendSpeed_x = intendSpeed_y = 0;
    Speed_x = Speed_y = 0;
    acAc_y = 0;
}

void ENTITYS::init(){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    [&](){
        // Get float.json
        QFile cfgFile;
        cfgFile.setFileName(ATTR_PATH_PREFIX + "entity/float.json");
        cfgFile.open(QIODevice::ReadOnly);
        QTextStream istream(&cfgFile);
        QString jsonStr = istream.readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(jsonStr.toLocal8Bit().data());
        QJsonObject jsonIsFloat = jDoc.object();
        for(auto it = jsonIsFloat.begin();it != jsonIsFloat.end();it++){
            ENTITYS::ENTITY_ISFLOAT[it.key()] = it.value().toBool();
        }
        cfgFile.close();
    }();
    [&](){
        // Get typename.json
        QFile cfgFile;
        cfgFile.setFileName(ATTR_PATH_PREFIX + "entity/typename.json");
        cfgFile.open(QIODevice::ReadOnly);
        QTextStream istream(&cfgFile);
        QString jsonStr = istream.readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(jsonStr.toLocal8Bit().data());
        QJsonObject jsonTypeList = jDoc.object();
        auto arr_n = jsonTypeList["npc"].toArray();
        for(auto it = arr_n.begin();it != arr_n.end();it++){
            ENTITYS::NPCS.insert(it->toString());
            qDebug("npc %s",it->toString().toStdString().c_str());
        }
        auto arr_i = jsonTypeList["item"].toArray();
        for(auto it = arr_i.begin();it != arr_i.end();it++){
            ENTITYS::ITEMS.insert(it->toString());
            qDebug("item %s",it->toString().toStdString().c_str());
        }
        cfgFile.close();
    }();
}

Player::Player(const QJsonObject &obj):Entity(obj){
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(type),-ENTITYS::getImgY(type));
    hp = obj["hp"].toInt();
    blood = new QGraphicsRectItem(this);
    blood->setBrush(QBrush(qRgb(255,0,0)));
    blood->setRect(-ENTITYS::getImgX(this->type),-ENTITYS::getImgY(this->type) - 4,20,3);
    dir = 1;
}

void Player::setblood(int x){
    blood->setRect(-ENTITYS::getImgX(this->type),-ENTITYS::getImgY(this->type) - 4,x * 0.2,3);
}

void Player::attack()
{
    state = 1;
    counter = 1;
    //修改贴图：近战攻击
}

void Player::hit()
{
    qDebug("player got hit");
    state = 3;
    counter = 1;
    hp -= 10;
}

void Player::setStatusPic(QString sta){
    this->setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type,sta)));
}

Player::~Player(){
    delete blood;
}

Npc::Npc(const QJsonObject &obj):Entity(obj){
    name = obj["name"].toString();
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(name)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(name),-ENTITYS::getImgY(name));
    hp = obj["hp"].toInt();
    if(obj.contains("heritage")){
        heri = new QJsonObject(obj["heritage"].toObject());
    }else heri = nullptr;
    myspeed = (int)floor(((rand() % 30) + 71.0) / 100 * NPC_SPEED);
    this->setISpeedX(myspeed);
    intendtick = 0;
    blood = new QGraphicsRectItem(this);
    blood->setBrush(QBrush(qRgb(255,0,0)));
    blood->setRect(-ENTITYS::getImgX(this->name),-ENTITYS::getImgY(this->name) - 4,20,3);
    dir = 1;
}

void Npc::setblood(int x){
    blood->setRect(-ENTITYS::getImgX(this->name),-ENTITYS::getImgY(this->name) - 4,x * 0.2,3);
}

void Npc::setStatusPic(QString sta){
    this->setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(name,sta)));
}

void Npc::hit()
{
    qDebug("npc get hit");
    state = 3;
    counter = 1;
    hp -= 20;
}

Npc::~Npc(){
    qDebug("npc?");
    delete blood;
    delete heri;
    qDebug("npc!");
}

Item::Item(const QJsonObject &obj):Entity(obj){
    name = obj["name"].toString();
    qDebug("item %s",name.toStdString().c_str());
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(name)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(name),-ENTITYS::getImgY(name));
}

Item::~Item(){
    //
}

Notice::Notice(const QJsonObject &obj):Entity(obj){
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(type),-ENTITYS::getImgY(type));
    this->moji = obj["moji"].toString();
    this->setZValue(12.0);
}

Notice::~Notice(){
    //
}

QString Notice::getMoji(){return this->moji;}

Gate::Gate(const QJsonObject &obj):Entity(obj){
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(type),-ENTITYS::getImgY(type));
    this->to = obj["to"].toInt();
}

Gate::~Gate(){
    //
}

Entity* Entity::newEntity(const QJsonObject& obj_,Entity* parent){
    QJsonObject obj(obj_);
    if(parent != nullptr && obj["attached"].toBool() == true){
        obj.remove("x");
        obj.remove("y");
        obj.insert("x",parent->x());
        obj.insert("y",parent->y());
    }
    QString tp = obj["type"].toString();
    if(tp == "watashi"){
        return new Player(obj);
    }
    if(tp == "notice"){
        return new Notice(obj);
    }
    if(tp == "gate"){
        return new Gate(obj);
    }
    if(tp == "npc"){
        return new Npc(obj);
    }
    if(tp == "item"){
        return new Item(obj);
    }
    return new Entity(obj);
}

Bullet::Bullet(const int &speed,bool isW,Entity* parent){
    this->setPos(parent->x(),parent->y());
    qDebug("bullet %f %f",this->x(),this->y());
    type = "bullet";
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(type),-ENTITYS::getImgY(type));
    QGraphicsPixmapItem::setZValue(18.0);
    isFloat = true;
    hp = BULLET_HP;
    this->speed = speed;
    this->intendSpeed_x = speed;
    this->intendSpeed_y = 0;
    this->Speed_x = speed;
    this->Speed_y = 0;
    this->isW = isW;
}

Bullet::~Bullet(){
    qDebug("bullet!");
}
