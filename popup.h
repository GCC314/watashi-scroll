#ifndef POPUP_H
#define POPUP_H

#include "config.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace POPUP{
    extern QHash<QString,QImage*> IMAGE_CACHE;
    inline QString txtpath(const QString &t){
        return TEXTURE_PATH_PREFIX + "popup/" + t + QString(".png");
    }
    inline QImage& getImgcache(const QString &t){
        if(!IMAGE_CACHE.contains(t)){
            IMAGE_CACHE[t] = new QImage(txtpath(t));
        }
        return *(IMAGE_CACHE[t]);
    }
    void init();
}

class Popup : public QGraphicsPixmapItem
{
public:
    Popup(int x,int y,QGraphicsView *view);
private:
    int type;
};

class Moji : public Popup{
public:
    Moji(QString moji,QGraphicsView *view);
    void show(QGraphicsScene *scene);
    void clear(QGraphicsScene *scene);
private:
    QString moji;
    QGraphicsTextItem *qmoji;
};

#endif // POPUP_H
