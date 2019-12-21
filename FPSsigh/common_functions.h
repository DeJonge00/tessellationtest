#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include <QMatrix4x4>
#include "math.h"

# define PI 3.14159265358979323846


class CommonFunctions
{
public:
    static QVector3D angleToVector(float angleSide, float angleUp) {
        float a = ((angleSide+90)/360.0)*(2*PI);
        QMatrix4x4 m = QMatrix4x4();
        m.setToIdentity();
        m.rotate(angleSide, QVector3D(0, 1, 0));
        m.rotate(angleUp, QVector3D(-sin(a), 0, cos(a)));
        return QVector3D(0, 0, -1) * m;
    }

    static QVector3D rotateVectorByAngles(QVector3D in, float angleSide, float angleUp) {
        float a = ((angleSide+90)/360.0)*(2*PI);
        QMatrix4x4 m = QMatrix4x4();
        m.setToIdentity();
        m.rotate(angleSide, QVector3D(0, 1, 0));
        m.rotate(angleUp, QVector3D(-sin(a), 0, cos(a)));
        return in * m;
    }
};

#endif // COMMON_FUNCTIONS_H
