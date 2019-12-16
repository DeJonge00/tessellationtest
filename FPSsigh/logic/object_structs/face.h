#ifndef FACE
#define FACE

#include <QVector3D>

// Forward declaration
class HalfEdge;

class Face {

public:
    HalfEdge* side;
    unsigned short val;
    unsigned int index;
    QVector3D normal;
    bool tessValid;

    // Inline constructors

    Face(HalfEdge* fside, unsigned short fval, unsigned int findex, bool tv) {
        side = fside;
        val = fval;
        index = findex;
        normal = QVector3D();
        tessValid = tv;
    }

    Face() : Face(nullptr, 0, 0, false) {}
};

#endif // FACE
