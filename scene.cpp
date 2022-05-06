#include "scene.h"

/*
 typedef struct __map_block_info{
    int type;
} Map_BLinfo;

class Scene
{
public:
    Scene();
    ~Scene();
    void Load(int level);
    void Wakeup();
private:
    Map_BLinfo **map;
    QVector<Entity> charas;
};
*/

Scene::Scene(QGraphicsScene *qtScene)
{
    qtscene = qtScene;
    map = new Map_BLinfo *[X_NUM];
    for(int x = 0;x < X_NUM;x++){
        map[x] = new Map_BLinfo [Y_NUM];
    }
}

Scene::~Scene(){
    for(int x = 0;x < X_NUM;x++){
        free(map[x]);
    }
    free(map);
}
