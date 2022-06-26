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
    acSpeed_x = acSpeed_y = 0;
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
    acSpeed_x = acSpeed_y = 0;
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
