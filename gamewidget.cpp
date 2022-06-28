#include "gamewidget.h"
#include "ui_gamewidget.h"
#include "config.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    scene = new MapScene(this);
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::__Run(){
    scene->Load(1);
    scene->Start();
}

const int WATASHI_SPEED = 8;

void GameWidget::keyPressEvent(QKeyEvent *event){
//    qDebug("key Pressed\n");
    switch(event->key()){
        case Qt::Key_A :
            scene->getWatashi()->shiftISpeedX(-WATASHI_SPEED);
            break;
        case Qt::Key_D :
            scene->getWatashi()->shiftISpeedX(WATASHI_SPEED);
            break;
        case Qt::Key_W :
            scene->getWatashi()->shiftISpeedY(-WATASHI_SPEED);
            break;
        case Qt::Key_S :
            scene->getWatashi()->shiftISpeedY(WATASHI_SPEED);
            break;
        case Qt::Key_Z :
            scene->DoZ();
            break;
        case Qt::Key_X :
            scene->DoX();
            break;
        case Qt::Key_Escape:
            //
            break;
        case Qt::Key_J:
            if(((Player*)(scene->getWatashi()))->state==0&&scene->getWatashi()->onfloor==1)
            {
                ((Player*)(scene->getWatashi()))->attack();
            }
            break;
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent *event){
//    qDebug("key Released\n");
    switch(event->key()){
        case Qt::Key_A :
            scene->getWatashi()->shiftISpeedX(WATASHI_SPEED);
            break;
        case Qt::Key_D :
            scene->getWatashi()->shiftISpeedX(-WATASHI_SPEED);
            break;
        case Qt::Key_W :
            scene->getWatashi()->shiftISpeedY(WATASHI_SPEED);
            break;
        case Qt::Key_S :
            scene->getWatashi()->shiftISpeedY(-WATASHI_SPEED);
            break;
    }
}
