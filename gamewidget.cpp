#include "gamewidget.h"
#include "ui_gamewidget.h"
#include "config.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    scene = new MapScene;
    view = new QGraphicsView(this);
    view->setScene(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->resize(SCREEN_X_WIDTH + 2,SCREEN_Y_WIDTH + 2);
    view->show();
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::__Run(){
    scene->Load(1);
    scene->Wakeup();
}

void GameWidget::keyPressEvent(QKeyEvent *event){
    qDebug("key Pressed\n");
    switch(event->key()){
        case Qt::Key_A :
            scene->getWatashi()->shiftSpeedX(-GOD_SPEED);
            break;
        case Qt::Key_D :
            scene->getWatashi()->shiftSpeedX(GOD_SPEED);
            break;
        case Qt::Key_W :
            scene->getWatashi()->shiftSpeedY(-GOD_SPEED);
            break;
        case Qt::Key_S :
            scene->getWatashi()->shiftSpeedY(GOD_SPEED);
            break;
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent *event){
    qDebug("key Released\n");
    switch(event->key()){
        case Qt::Key_A :
            scene->getWatashi()->shiftSpeedX(GOD_SPEED);
            break;
        case Qt::Key_D :
            scene->getWatashi()->shiftSpeedX(-GOD_SPEED);
            break;
        case Qt::Key_W :
            scene->getWatashi()->shiftSpeedY(GOD_SPEED);
            break;
        case Qt::Key_S :
            scene->getWatashi()->shiftSpeedY(-GOD_SPEED);
            break;
    }
}
