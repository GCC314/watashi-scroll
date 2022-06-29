#include "gamewidget.h"
#include "ui_gamewidget.h"
#include "config.h"
#include "musics.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    scene = new MapScene(this);
    setWindowIcon(QIcon(":/ICON.png"));
}

GameWidget::~GameWidget()
{
    delete ui;
}

static bool isRunning__ = false;
static QMediaPlayer *intro = nullptr;
static QMediaPlaylist *introl = nullptr;

void GameWidget::introBGM(){
    intro = new QMediaPlayer();
    introl = new QMediaPlaylist();
    MUSICS::bgmSet(intro,introl,"intro");
    intro->setVolume(25);
    intro->play();
}

void GameWidget::__Run(){
    if(isRunning__) return;
    isRunning__ = true;
    intro->stop();
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
            scene->getWatashi()->shiftISpeedY(-WATASHI_SPEED*1.4);
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
        case Qt::Key_Shift:
            scene->getWatashi()->shiftISpeedY(-20);
            ((Player*)scene->getWatashi())->hp -= 5;
            break;
        case Qt::Key_Escape:
            delete scene;
            GameWidget::close();
            break;
        case Qt::Key_J:
            // break;
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
            scene->getWatashi()->shiftISpeedY(WATASHI_SPEED*1.4);
            break;
        case Qt::Key_S :
            scene->getWatashi()->shiftISpeedY(-WATASHI_SPEED);
            break;
    }
}
static bool isbpainted = false;
void GameWidget::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/menu.png"));
}
