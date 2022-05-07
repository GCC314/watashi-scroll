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
    w.__Run();
    return a.exec();
}
