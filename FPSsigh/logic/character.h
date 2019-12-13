#ifndef CHARACTER_H
#define CHARACTER_H

#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QVector2D>

class Character
{
public:
    Character(QVector3D pos, float eye);
    Character() : Character(QVector3D(0, 2, 0), 1) {};
    QMatrix4x4 modelViewMatrix, projectionMatrix;
    QMatrix3x3 normalMatrix;
    void changeFoV(float fov);
    void setFoV(float fov);
    void changeDispRatio(float disprat);
    void changeRotationAngleX(float angle);
    void changeRotationAngleY(float angle);
    void setRotationAngleX(float angle);
    void setRotationAngleY(float angle);
    void setRotation(QVector2D);
    void handleKeypress(char key);

    void changeXPosition(float n);
    void changeYPosition(float n);
    void changeZPosition(float n);
    void setXPosition(float n);
    void setYPosition(float n);
    void setZPosition(float n);
    void setPosition(QVector3D);
    QVector3D position;
    float angleSide;
    float angleUp;

    void positionForward(float n);
    void positionBack(float n);
    void positionLeft(float n);
    void positionRight(float n);
protected:
private:
    float rotationAngle;
    float FoV;
    float dispRatio;

    QVector3D getDirection();
    QVector3D getDirectionSide();

    void updateModelMatrix();
    void updateProjectionMatrix();
    void updateNormalMatrix();

    void initView();
};

#endif // CHARACTER_H
