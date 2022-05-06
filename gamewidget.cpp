#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    view = new QGraphicsView;
    view->setScene(scene);
    view->resize(SCREEN_X_WIDTH,SCREEN_Y_WIDTH);
    view->show();
}

GameWidget::~GameWidget()
{
    delete ui;
}

