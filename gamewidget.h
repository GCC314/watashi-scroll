#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "scene.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include "config.h"
#include<QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWidget; }
QT_END_NAMESPACE

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

    void __Run();
    void introBGM();

private:
    MapScene *scene;
    QGraphicsView *view;
    Ui::GameWidget *ui;
    QPushButton* b;
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // GAMEWIDGET_H
