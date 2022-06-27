#ifndef BLOCK_H
#define BLOCK_H

#include "config.h"
#include <QGraphicsItem>
#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

namespace BLOCKS{
    extern QHash<QString,QImage*> IMAGE_CACHE;
    inline QString txtpath(const QString &t){
        return TEXTURE_PATH_PREFIX + "block/" + t + QString(".png");
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
    void init();
}



class Block : public QGraphicsPixmapItem
{
public:
    Block(const QString &type);
    Block(const QString &type,int x,int y);
    Block(const QJsonObject &obj);
private:
    QString type;
};

#endif // BLOCK_H
