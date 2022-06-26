#include "block.h"

QHash<QString,QImage*> BLOCKS::IMAGE_CACHE;

Block::Block(const QString &type){
    QGraphicsPixmapItem::setZValue(15.0);
    QGraphicsPixmapItem::setPos(0,0);
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(BLOCKS::getImgcache(type)));
}
Block::Block(const QString &type,int x,int y){
    QGraphicsPixmapItem::setZValue(15.0);
    QGraphicsPixmapItem::setPos(x,y);
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(BLOCKS::getImgcache(type)));
}

Block::Block(const QJsonObject &obj){
    int x = obj["x"].toInt();
    int y = obj["y"].toInt();
    QString type = obj["type"].toString();
    qDebug("%s [%d %d]\n",type.toStdString().c_str(),x,y);
    this->type = type;
    QGraphicsPixmapItem::setZValue(15.0);
    QGraphicsPixmapItem::setPos(x,y);
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(BLOCKS::getImgcache(type)));
}

void BLOCKS::init(){
    //
}
