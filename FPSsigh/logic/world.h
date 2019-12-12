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

    void getWorldObjects(QVector<QVector3D>& vertices, QVector<QVector3D>& normals);
    void addDefaultWorldObject();

protected:
    QVector<WorldObject> worldObjects;
};

#endif // WORLD_H
