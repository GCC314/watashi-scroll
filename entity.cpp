#include "entity.h"

QHash<QString,QImage*> ENTITYS::IMAGE_CACHE;
QHash<QString,bool> ENTITYS::ENTITY_ISFLOAT;

Entity::Entity(const QString& type)
{
    QGraphicsPixmapItem::setZValue(30.0);
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
}

Entity::Entity(int x,int y,const QString& type){
    QGraphicsPixmapItem::setZValue(30.0);
    QGraphicsPixmapItem::setPos(x,y);
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(type),-ENTITYS::getImgY(type));
    isFloat = ENTITYS::getEttFloat(type);
    intendSpeed_x = intendSpeed_y = 0;
    Speed_x = Speed_y = 0;
    acAc_y = 0;
}

Entity::Entity(const QJsonObject &obj){
    int x = obj["x"].toInt();
    int y = obj["y"].toInt();
    QString type = obj["type"].toString();
    qDebug("%s [%d %d]\n",type.toStdString().c_str(),x,y);
    this->type = type;
    QGraphicsPixmapItem::setZValue(15.0);
    QGraphicsPixmapItem::setPos(x,y);
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(ENTITYS::getImgcache(type)));
    QGraphicsPixmapItem::setOffset(-ENTITYS::getImgX(type),-ENTITYS::getImgY(type));
    isFloat = ENTITYS::getEttFloat(type);
    intendSpeed_x = intendSpeed_y = 0;
    Speed_x = Speed_y = 0;
    acAc_y = 0;
}

void ENTITYS::init(){
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
}

Player::Player(const QJsonObject &obj):Entity(obj){
    //
}

Npc::Npc(const QJsonObject &obj):Entity(obj){
    //
}

Item::Item(const QJsonObject &obj):Entity(obj){
    //
}

Notice::Notice(const QJsonObject &obj):Entity(obj){
    this->moji = obj["moji"].toString();
    this->setZValue(12.0);
}

QString Notice::getMoji(){return this->moji;}

Gate::Gate(const QJsonObject &obj):Entity(obj){
    //
}


Entity* Entity::newEntity(const QJsonObject& obj){
    if(obj["type"].toString() == "watashi"){
        return new Player(obj);
    }
    if(obj["type"].toString() == "npc"){
        return new Npc(obj);
    }
    if(obj["type"].toString() == "item"){
        return new Item(obj);
    }
    if(obj["type"].toString() == "gate"){
        return new Gate(obj);
    }
    if(obj["type"].toString() == "notice"){
        return new Notice(obj);
    }
    return new Entity(obj);
}
