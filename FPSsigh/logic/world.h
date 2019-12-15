#ifndef WORLD_H
#define WORLD_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLDebugLogger>
#include <QVector>
#include <QVector3D>

#include "logic/world_objects/worldobject.h"
#include "logic/object_structs/vertex.h"
#include "logic/object_structs/halfedge.h"
#include "logic/object_structs/face.h"


class World
{
public:
    World();

    void getSimpleWorldObjects(QVector<QVector3D>& vertices, QVector<QVector3D>& normals);
    void getTessWorldObjects(QVector<QVector3D>& vertices, QVector<QVector3D>& normals);

    QString objectPath;
    // initscenes
    void loadScene(QString name);
    void initDefaultScene();

    // character
//    void addCharacterObjects();
    void addBullet(QVector3D location, float angleSide, float angleUp);

    void updateWorld(long long time);
    WorldObject* getLoadedObject(QString name);
    void loadObject(QString dir_name, QString name);

protected:
    QVector<WorldObject *> worldObjects;
    QVector<WorldObject *> loadedWorldObjects;

private:
    WorldObject* objectLoader(QString fileName, QString name);
    inline WorldObject* objectLoader(QString fileName) { return objectLoader(fileName, "Object"); };
};

#endif // WORLD_H
