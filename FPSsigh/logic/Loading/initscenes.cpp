#include <QDir>

#include "logic/world.h"


void World::loadScene(QString name) {
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

    WorldObject* cube = getLoadedObject("cube");
    cube->scale(1);
    cube->translate(QVector3D(-3, 1, -2));
    worldObjects.append(cube);

    WorldObject* monkey = getLoadedObject("monkey");
    monkey->scale(1.5);
    monkey->translate(QVector3D(4, 2, 2));
    worldObjects.append(monkey);

    WorldObject* skybox = getLoadedObject("cube");
    skybox->name = QString("skybox");
    skybox->scale(15);
    worldObjects.append(skybox);

    WorldObject* sphere = getLoadedObject("sphere");
    sphere->translate(QVector3D(-1, 1, -1));
    worldObjects.append(sphere);

    WorldObject* tower = getLoadedObject("tower");
    tower->translate(QVector3D(1, 1, -1));
    worldObjects.append(tower);
}
