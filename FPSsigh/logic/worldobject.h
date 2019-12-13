#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLDebugLogger>
#include <QVector3D>


class WorldObject
{
public:
    WorldObject(QVector<QVector3D> vertices, QVector<QVector3D> normals);
    WorldObject() : WorldObject(QVector<QVector3D>(), QVector<QVector3D>()) {};
    QVector<QVector3D> getVertices();
    QVector<QVector3D> getNormals();

    void addFace(QVector<QVector3D> vertices, QVector<QVector3D> normals);

private:
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
};

#endif // WORLDOBJECT_H
