#include <QMouseEvent>
#include <QVector>
#include <QVector3D>

#include "logic/character.h"
#include "math.h"

# define PI 3.14159265358979323846

Character::Character(QVector3D pos, float view)
    : position(pos), angleUp(0), angleSide(view)
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
    modelViewMatrix.scale(QVector3D(1.0, 1.0, 1.0));
}

void Character::updateProjectionMatrix() {
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(FoV, dispRatio, 0.2, 20.0);
    projectionMatrix.rotate(angleSide, QVector3D(0, 1, 0));
    projectionMatrix.rotate(angleUp, getDirectionSide());


    projectionMatrix.translate(position.x(), -position.y(), position.z());
}

void Character::updateNormalMatrix() {
    normalMatrix = modelViewMatrix.normalMatrix();
}

void Character::changeFoV(float fov) {
    FoV += fov;
    updateProjectionMatrix();
}

void Character::setFoV(float fov) {
    FoV = fov;
    updateProjectionMatrix();
}

void Character::changeDispRatio(float disprat) {
    dispRatio = disprat;
    updateProjectionMatrix();
}

void Character::changeXPosition(float n) {
    position.setX(position.x() + n);
    updateProjectionMatrix();
}

void Character::changeYPosition(float n) {
    position.setY(position.y() + n);
    updateProjectionMatrix();
}

void Character::changeZPosition(float n) {
    position.setZ(position.z() + n);
    updateProjectionMatrix();
}

void Character::setXPosition(float n) {
    position.setX(n);
    updateProjectionMatrix();
}

void Character::setYPosition(float n) {
    position.setY(n);
    updateProjectionMatrix();
}

void Character::setZPosition(float n) {
    position.setZ(n);
    updateProjectionMatrix();
}

void Character::setPosition(QVector3D pos) {
    position = pos;
    updateProjectionMatrix();
}

void Character::changeRotationAngleX(float angle) {
    angleSide = fmod(360+angleSide + angle, 360);
    updateProjectionMatrix();
}

void Character::changeRotationAngleY(float angle) {
    angleUp = fmod(360+angleUp + angle, 360);
    updateProjectionMatrix();
}

void Character::setRotationAngleX(float angle) {
    angleSide = fmod(angle, 2);
    updateProjectionMatrix();
}

void Character::setRotationAngleY(float angle) {
    angleUp = fmod(angle, 2);
    updateProjectionMatrix();
}

void Character::setRotation(QVector2D rot) {
    angleUp = fmod(rot.y(), 1);
    angleSide = fmod(rot.x(), 1);
}

QVector3D Character::getDirection() {
    float a = (angleSide/360.0)*(2*PI);
    return QVector3D(-sin(a), 0, cos(a));
}

QVector3D Character::getDirectionSide() {
    float a = ((angleSide+90)/360.0)*(2*PI);
    return QVector3D(-sin(a), 0, cos(a));
}

void Character::handleKeypress(char key) {
    switch(key) {
    case 'A':
        positionLeft(1.0);
        break;
    case 'D':
        positionRight(1.0);
        break;
    case 'W':
        positionForward(1.0);
        break;
    case 'S':
        positionBack(1.0);
        break;

    case '': // Arrow up
        changeRotationAngleY(1.0);
        break;
    case '': // Arrow left
        changeRotationAngleX(-2.0);
        break;
    case '': // Arrow down
        changeRotationAngleY(-1.0);
        break;
    case '': // Arrow right
        changeRotationAngleX(2.0);
        break;

    case 'R':
        setPosition(QVector3D(0, 2, 0));
        setRotation(QVector2D(0, -1));
        break;
    }
}

void Character::positionForward(float n) {
    position += getDirection() * n;
    updateProjectionMatrix();
}

void Character::positionBack(float n) {
    position -= getDirection() * n;
    updateProjectionMatrix();
}

void Character::positionLeft(float n) {
    position -= getDirectionSide() * n;
    updateProjectionMatrix();
}

void Character::positionRight(float n) {
    position += getDirectionSide() * n;
    updateProjectionMatrix();
}
