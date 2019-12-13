#include <QMouseEvent>
#include <QVector>
#include <QVector3D>

#include "logic/character.h"
#include "math.h"

Character::Character()
{
    initView();
}

void Character::initView() {
    rotationAngle = 0.0;
    FoV = 60.0;
    updateModelMatrix();
    updateProjectionMatrix();
    updateNormalMatrix();
}

void Character::updateModelMatrix() {
    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(QVector3D(0.0, 0.0, -3.0));
    modelViewMatrix.scale(QVector3D(1.0, 1.0, 1.0));
    modelViewMatrix.rotate(rotationAngle, QVector3D(0.0, 1.0, 0.0));
}

void Character::updateProjectionMatrix() {
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(FoV, dispRatio, 0.2, 4.0);
}

void Character::updateNormalMatrix() {
    normalMatrix = modelViewMatrix.normalMatrix();
}

void Character::changeFoV(float fov) {
    qDebug() << fov;
    FoV = fov;
    updateProjectionMatrix();
}

void Character::changeDispRatio(float disprat) {
    qDebug() << disprat;
    dispRatio = disprat;
    updateProjectionMatrix();
}

void Character::changeRotationAngle(float angle) {
    qDebug() << angle;
    rotationAngle = fmod((angle), 360);
    updateModelMatrix();
}

void Character::keyPressEvent(QKeyEvent* event) {
    qDebug() << event->key();
    switch(event->key()) {
    case 'A':
        changeRotationAngle(1);
        break;
    case 'D':
        changeRotationAngle(-10);
        break;
    }
}
