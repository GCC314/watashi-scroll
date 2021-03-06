#include "popup.h"

QHash<QString,QImage*> POPUP::IMAGE_CACHE;

Popup::Popup(int x,int y,QGraphicsView *view){
    QPointF pt = view->mapToScene(QPoint(x,y));
    qDebug("%f %f\n",pt.x(),pt.y());
    this->setPos(pt.x(),pt.y());
}

Moji::Moji(QString moji,QGraphicsView *view):Popup(30,330,view){
    this->moji = moji;
    QGraphicsPixmapItem::setZValue(50.0);
    QGraphicsPixmapItem::setPixmap(QPixmap::fromImage(POPUP::getImgcache("moji")));
    qmoji = new QGraphicsTextItem(moji,this);
    QFont tf;
    tf.setPixelSize(20);
    tf.setFamily("Fira Code");
    qmoji->setDefaultTextColor(Qt::white);
    qmoji->setTextWidth(550);
    qmoji->setFont(tf);
    qmoji->setPos(10,10);
}

void Moji::show(QGraphicsScene *scene){
    scene->addItem(this);
}

void Moji::clear(QGraphicsScene *scene){
    scene->removeItem(this);
    delete qmoji;
}

void POPUP::init(){
    //
}

//
