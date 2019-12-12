#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLDebugLogger>


class WorldObject
{
public:
    WorldObject();

    QVector<QVector3D> vertices;
};

#endif // WORLDOBJECT_H
