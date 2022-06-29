#include "gamewidget.h"

#include <QApplication>

#include "scene.h"
#include "entity.h"
#include "block.h"
#include<QLabel>
#include<QPushButton>

void Init(){
    ENTITYS::init();
    POPUP::init();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/stylesheet.qss");//美化按钮用的
    if(qss.open(QFile::ReadOnly))
        a.setStyleSheet(qss.readAll());
    GameWidget w;
    Init();
    w.show();
    w.introBGM();
    //设置按钮
    QPushButton begin, exit;
    begin.setParent(&w);
    begin.setText("Start the game");
    begin.move(250, 200);
    begin.show();
    GameWidget::connect(&begin, &QPushButton::clicked, &w, &GameWidget::__Run);
    exit.setParent(&w);
    exit.setText("Exit the game");
    exit.move(255, 300);
    exit.show();
    GameWidget::connect(&exit, &QPushButton::clicked, &w, &GameWidget::close);


    QLabel lab;
    lab.setParent(&w);
    lab.move(175, 100);
    lab.setAlignment(Qt::AlignCenter);
    lab.setText("WATASHI PARKOUR");
    QFont font("Microsoft JhengHei",15);
    lab.setStyleSheet("QLabel{font:30px;color:red;background-color:rgb(f9,f9,f9);}");
    lab.setFont(font);
    lab.show();
    return a.exec();
}
