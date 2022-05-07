#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    view = new QGraphicsView(this);
    view->setScene(scene);
    view->resize(SCREEN_X_WIDTH,SCREEN_Y_WIDTH);
    scene->addLine(0,0,150,150);
    scene->addPixmap(QPixmap::fromImage(block_image_cache(0)));
    view->show();
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::__Run(){
    mapscene = new Scene(scene);
    mapscene->Load(1);
}
