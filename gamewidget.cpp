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

const int WATASHI_SPEED = 10;

void GameWidget::keyPressEvent(QKeyEvent *event){
    qDebug("key Pressed\n");
    switch(event->key()){
        case Qt::Key_A :
            scene->getWatashi()->shiftSpeedX(-WATASHI_SPEED);
            break;
        case Qt::Key_D :
            scene->getWatashi()->shiftSpeedX(WATASHI_SPEED);
            break;
        case Qt::Key_W :
            scene->getWatashi()->shiftSpeedY(-WATASHI_SPEED);
            break;
        case Qt::Key_S :
            scene->getWatashi()->shiftSpeedY(WATASHI_SPEED);
            break;
        case Qt::Key_Z :
            scene->UnshowDialog();
            break;
        case Qt::Key_X :
            scene->ShowDialog("Hello");
            break;
        case Qt::Key_C :
            //
            break;
        case Qt::Key_Escape:
            //
            break;
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent *event){
    qDebug("key Released\n");
    switch(event->key()){
        case Qt::Key_A :
            scene->getWatashi()->shiftSpeedX(WATASHI_SPEED);
            break;
        case Qt::Key_D :
            scene->getWatashi()->shiftSpeedX(-WATASHI_SPEED);
            break;
        case Qt::Key_W :
            scene->getWatashi()->shiftSpeedY(WATASHI_SPEED);
            break;
        case Qt::Key_S :
            scene->getWatashi()->shiftSpeedY(-WATASHI_SPEED);
            break;
    }
}
