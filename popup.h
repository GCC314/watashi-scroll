#ifndef POPUP_H
#define POPUP_H

#include "config.h"
#include <QGraphicsItem>

namespace POPUP{
    //
}

class Popup : public QGraphicsPixmapItem
{
public:
    Popup(int type = -1);
    Popup(int x,int y,int type);
    Popup(int x,int y,int type,int sx,int sy);
private:
    int type;
};

class Moji : public Popup{
public:
    Moji();
    Moji(QString moji);
private:
    QString moji;
};

#endif // POPUP_H
