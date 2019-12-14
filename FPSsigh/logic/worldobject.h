#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLDebugLogger>
#include <QVector3D>

#include "logic/face.h"
#include "logic/vertex.h"
#include "logic/halfedge.h"


class WorldObject
{
public:
    WorldObject();
    void WorldObject::getSimpleArrays(QVector<QVector3D>& vertices, QVector<QVector3D>& normals);
    void WorldObject::getTessArrays(QVector<QVector3D>& vertices, QVector<QVector3D>& normals);

    void addFace(Face *f);
    void addVertex(Vertex *v);
    void addHalfedge(HalfEdge *h);

    void addFaces(QVector<Face *> fs);
    void addVertices(QVector<Vertex *> vs);
    void addHalfedges(QVector<HalfEdge *> hs);

    QString name;
    QVector<Vertex *> vertices;
    QVector<QVector3D *> normals;
    QVector<Face *> faces;
    QVector<HalfEdge *> halfedges;

    void scale(float s);
    void translate(QVector3D t);
};

#endif // WORLDOBJECT_H
