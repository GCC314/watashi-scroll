#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "scene.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "config.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWidget; }
QT_END_NAMESPACE

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Ui::GameWidget *ui;

};
#endif // GAMEWIDGET_H
