#include <QMouseEvent>

#include "logic/character.h"

Character::Character()
{
    initView();
}

void Character::initView() {
    rotationAngle = 0.0;
    FoV = 60.0;

    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(QVector3D(0.0, 0.0, -3.0));
    modelViewMatrix.scale(QVector3D(1.0, 1.0, 1.0));
    modelViewMatrix.rotate(rotationAngle, QVector3D(0.0, 1.0, 0.0));

    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(FoV, dispRatio, 0.2, 4.0);

    normalMatrix = modelViewMatrix.normalMatrix();
}

void Character::changeFoV(float fov) {
    FoV = fov;
    projectionMatrix.perspective(FoV, dispRatio, 0.2, 4.0);
}

void Character::changeDispRatio(float disprat) {
    dispRatio = disprat;
    projectionMatrix.perspective(FoV, dispRatio, 0.2, 4.0);
}
