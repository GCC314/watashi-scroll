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

static bool isRunning__ = false;

void GameWidget::__Run(){
    if(isRunning__) return;
    isRunning__ = true;
    //scene->Load(1);
    scene->Load(1);
    scene->Start();
}

void GameWidget::keyPressEvent(QKeyEvent *event){
//    qDebug("key Pressed\n");
    switch(event->key()){
        case Qt::Key_A :
            ((Player*)scene->getWatashi())->dir = -1;
            scene->getWatashi()->shiftISpeedX(-WATASHI_SPEED);
            break;
        case Qt::Key_D :
            ((Player*)scene->getWatashi())->dir = 1;
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
        case Qt::Key_R :
            scene->Pause();
            scene->Clear();
            scene->Load(scene->nowlevel);
            break;
        case Qt::Key_Escape:
            delete scene;
            GameWidget::close();
            break;
        case Qt::Key_J:
            if(((Player*)(scene->getWatashi()))->state==0&&scene->getWatashi()->onfloor==1)
            {
                ((Player*)(scene->getWatashi()))->attack();
            }
            break;
        case Qt::Key_K: // For test
            scene->Shoot((Player*)(scene->getWatashi()));
            break;
        case Qt::Key_Space:
            //
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
