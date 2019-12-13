#include <QMouseEvent>
#include <QVector>
#include <QVector3D>

#include "logic/character.h"
#include "math.h"

# define PI 3.14159265358979323846

Character::Character(QVector3D pos, QVector3D view)
    : position(pos), eyeDirection(view)
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
}

void Character::updateProjectionMatrix() {
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(FoV, dispRatio, 0.2, 20.0);
    projectionMatrix.rotate(eyeDirection.x(), QVector3D(0.0, 1.0, 0.0));
    projectionMatrix.rotate(eyeDirection.y(), QVector3D(1.0, 0.0, 0.0));
    projectionMatrix.rotate(eyeDirection.z(), QVector3D(0.0, 0.0, 1.0));
    projectionMatrix.translate(position.x(), -position.y(), position.z());
}

void Character::updateNormalMatrix() {
    normalMatrix = modelViewMatrix.normalMatrix();
}

void Character::changeFoV(float fov) {
    FoV = fov;
    updateProjectionMatrix();
}

void Character::changeDispRatio(float disprat) {
    dispRatio = disprat;
    updateProjectionMatrix();
}

void Character::changeXPosition(float n) {
    position.setX(n);
    updateProjectionMatrix();
}

void Character::changeYPosition(float n) {
    position.setY(n);
    updateProjectionMatrix();
}

void Character::changeZPosition(float n) {
    position.setZ(n);
    updateProjectionMatrix();
}

void Character::changeRotationAngleX(float angle) {
    eyeDirection.setX(angle);
    updateModelMatrix();
    updateProjectionMatrix();
}

void Character::changeRotationAngleY(float angle) {
    eyeDirection.setY(angle);
    updateModelMatrix();
    updateProjectionMatrix();
}

void Character::changeRotationAngleZ(float angle) {
    eyeDirection.setZ(angle);
    updateModelMatrix();
    updateProjectionMatrix();
}

void Character::keyPressEvent(QKeyEvent* event) {
    qDebug() << event->key();
    switch(event->key()) {
    case 'a':
        changeRotationAngleX(1);
        break;
    case 'd':
        changeRotationAngleX(-1);
        break;
    case 'w':
        changeRotationAngleY(1);
        break;
    case 's':
        changeRotationAngleY(-1);
        break;
    }
}
