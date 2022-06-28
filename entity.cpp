#include "entity.h"

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
}

Npc::Npc(const QJsonObject &obj):Entity(obj){
    name = obj["name"].toString();
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(name)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(name),-ENTITYS::getImgY(name));
}

Item::Item(const QJsonObject &obj):Entity(obj){
    name = obj["name"].toString();
    qDebug("item %s",name.toStdString().c_str());
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(name)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(name),-ENTITYS::getImgY(name));
}

Notice::Notice(const QJsonObject &obj):Entity(obj){
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(type),-ENTITYS::getImgY(type));
    this->moji = obj["moji"].toString();
    this->setZValue(12.0);
}

QString Notice::getMoji(){return this->moji;}

Gate::Gate(const QJsonObject &obj):Entity(obj){
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(type),-ENTITYS::getImgY(type));
    this->to = obj["to"].toInt();
}

Entity* Entity::newEntity(const QJsonObject& obj){
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
