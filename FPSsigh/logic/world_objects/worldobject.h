#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLDebugLogger>
#include <QVector3D>

#include "logic/object_structs/face.h"
#include "logic/object_structs/vertex.h"
#include "logic/object_structs/halfedge.h"


class WorldObject
{
public:
    WorldObject();
    QVector<QVector3D> getSimpleVertices();
    QVector<QVector3D> getSimpleNormals();

    QVector<QVector3D> getTessVertices();
    QVector<QVector3D> getTessNormals();

    QVector<QVector3D> getNormals();

    void addFace(Face *f);
    void addVertex(Vertex *v);
    void addHalfedge(HalfEdge *h);

    void addFaces(QVector<Face *> fs) { faces.append(fs); }
    void addVertices(QVector<Vertex *> vs) { vertices.append(vs); }
    void addHalfedges(QVector<HalfEdge *> hs) {halfedges.append(hs); }
    void addNormals(QVector<QVector3D *> ns) { normals.append(ns); }

    QString name;
    QVector<Vertex *> vertices;
    QVector<QVector3D *> normals;
    QVector<Face *> faces;
    QVector<HalfEdge *> halfedges;

    void scale(float s);
    void rotate(float x, float y, float z);
    void translate(QVector3D t);

    virtual bool update(long long time);

    long long timeLastEdited;
    float size;
    QVector3D rotation;
    QVector3D translation;
    unsigned int mode;

    virtual WorldObject* copy();
    void copyOver(WorldObject* wo);

    void toLimitPositions();

    float phase;
    int phaseType;
    float phaseSpeed;
    float phaseStrength;

protected:
    double timeSinceLastEdit(long long time);
};

#endif // WORLDOBJECT_H
