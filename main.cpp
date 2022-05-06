#include "gamewidget.h"

#include <QApplication>

#include "scene.h"
#include "entity.h"
#include "block.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget w;
    w.show();
    return a.exec();
}
