#ifndef WORLD_H
#define WORLD_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLDebugLogger>
#include <QVector>
#include <QVector3D>

#include "logic/worldobject.h"
#include "logic/worldobject.h"
#include "logic/vertex.h"
#include "logic/halfedge.h"
#include "logic/face.h"

class World
{
public:
    World();

    void getSimpleWorldObjects(QVector<QVector3D>& vertices, QVector<QVector3D>& normals);
    void getTessWorldObjects(QVector<QVector3D>& vertices, QVector<QVector3D>& normals);

    void addScene(QString name);
    void initDefaultScene();

protected:
    QVector<WorldObject *> worldObjects;

private:
    WorldObject* objectLoader(QString fileName, QString name);
    inline WorldObject* objectLoader(QString fileName) { return objectLoader(fileName, "Object"); };
};

#endif // WORLD_H
