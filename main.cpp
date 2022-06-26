#include "gamewidget.h"

#include <QApplication>

#include "scene.h"
#include "entity.h"
#include "block.h"

void Init(){
    ENTITYS::init();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget w;
    Init();
    w.show();
    w.__Run();
    return a.exec();
}
