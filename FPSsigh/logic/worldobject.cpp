#include "worldobject.h"

WorldObject::WorldObject(QVector<QVector3D> vs, QVector<QVector3D> ns)
    : vertices(vs), normals(ns)
{

}

QVector<QVector3D> WorldObject::getVertices() {
    return vertices;
}

QVector<QVector3D> WorldObject::getNormals() {
    return normals;
}

void WorldObject::addFace(QVector<QVector3D> vs, QVector<QVector3D> ns) {
    vertices.append(vs);
    normals.append(ns);
}
