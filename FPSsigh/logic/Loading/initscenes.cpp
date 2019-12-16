#include <QDir>

#include "logic/world.h"
#include "logic/world_objects/floor.h"

# define RENDERMODE_BLAND 0
# define RENDERMODE_NORMAL 1
# define RENDERMODE_DOT_PLAYER 2


void World::loadScene(QString name) {
//    loadObject(QString("scene1"), QString("tower"));
    QDir directory(objectPath + "/" + name);
    QStringList objects = directory.entryList(QStringList() << "*.obj",QDir::Files);
    for (QString o : objects) {
        o.chop(4);
        loadObject(name, o);
    }
}

void World::initDefaultScene() {
    worldObjects = QVector<WorldObject *>();
    loadScene("scene1");

    Floor* floor = new Floor(30, 30);
    floor->name = QString("Floor");
    floor->mode = RENDERMODE_BLAND;
    worldObjects.append(floor);

    WorldObject* skybox = getLoadedObject("cube");
    skybox->name = QString("skybox");
    skybox->scale(15);
    skybox->mode = RENDERMODE_NORMAL;
    worldObjects.append(skybox);

    WorldObject* cube = getLoadedObject("cube");
    cube->toLimitPositions();
    cube->scale(1);
    cube->translate(QVector3D(-3, 1, -2));
    cube->mode = RENDERMODE_NORMAL;
    worldObjects.append(cube);

    WorldObject* tower = getLoadedObject("tower");
//    tower->toLimitPositions();
    tower->mode = RENDERMODE_NORMAL;
    tower->translate(QVector3D(0, 3, 0));
    worldObjects.append(tower);

//    WorldObject* tower2 = getLoadedObject("tower");
//    tower2->mode = RENDERMODE_NORMAL;
//    tower2->translate(QVector3D(2, 1, -1));
//    worldObjects.append(tower2);

    WorldObject* sphere = getLoadedObject("sphere");
    sphere->mode = RENDERMODE_NORMAL;
    sphere->translate(QVector3D(-1, 1, -1));
    worldObjects.append(sphere);

//    WorldObject* monkey = getLoadedObject("monkey");
//    monkey->mode = RENDERMODE_NORMAL;
//    monkey->scale(1.5);
//    monkey->translate(QVector3D(7, 2, 2));
//    worldObjects.append(monkey);
}
