#include <QDir>

#include "logic/world.h"


void World::addScene(QString name) {
    QString path = "./../FPSSigh/models/";
    path.append(name);
    QDir directory(path);
    QStringList objects = directory.entryList(QStringList() << "*.obj",QDir::Files);
    for (QString o : objects) {
        worldObjects.append(objectLoader(path + "/" + o, o));
    }
}

void World::initDefaultScene() {
    worldObjects = QVector<WorldObject *>();
    addScene("scene1");

    // Cube
    worldObjects.at(0)->scale(1);
    worldObjects.at(0)->translate(QVector3D(-4, 1, -1));
    // Monkey
    worldObjects.at(1)->scale(1.5);
    worldObjects.at(1)->translate(QVector3D(4, 2, -1));
    // Skybox
    worldObjects.at(2)->scale(15);
    // Sphere
    worldObjects.at(3)->translate(QVector3D(-1, 1, -1));
    // Tower
    worldObjects.at(4)->translate(QVector3D(1, 1, -1));

}
