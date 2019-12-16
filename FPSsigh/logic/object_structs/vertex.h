#ifndef VERTEX
#define VERTEX

#include <QVector3D>
#include <QDebug>

class HalfEdge;

class Vertex {
public:
    QVector3D coords;
    HalfEdge* out;
    unsigned short val;
    unsigned int index;
    unsigned short sharpness;
    QVector3D normal;
    bool isEdge;

    Vertex() : Vertex(QVector3D(), nullptr, 0, 0, QVector3D()) {}

    Vertex(QVector3D vcoords, HalfEdge* vout, unsigned short vval, unsigned int vindex, QVector3D vnormal, float vsharpness = 0) {
        coords = vcoords;
        out = vout;
        val = vval;
        index = vindex;
        sharpness = vsharpness;
        normal = vnormal;
        isEdge = false;
    }
};

#endif // VERTEX
