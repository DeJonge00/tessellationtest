#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLDebugLogger>
#include <QVector3D>


class WorldObject
{
public:
    WorldObject();

    QVector<QVector3D> vertices;
};

#endif // WORLDOBJECT_H
