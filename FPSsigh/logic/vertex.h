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

    Vertex() {
        coords = QVector3D();
        out = nullptr;
        val = 0;
        index = 0;
        sharpness = 0;
    }

    Vertex(QVector3D vcoords, HalfEdge* vout, unsigned short vval, unsigned int vindex, float vsharpness = 0) {
        coords = vcoords;
        out = vout;
        val = vval;
        index = vindex;
        sharpness = vsharpness;
    }
};

#endif // VERTEX
