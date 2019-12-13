#ifndef CHARACTER_H
#define CHARACTER_H

#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QMouseEvent>

class Character
{
public:
    Character(QVector3D pos, QVector3D view);
    Character() : Character(QVector3D(0, 2, 0), QVector3D(0, 0, -1)) {};
    QMatrix4x4 modelViewMatrix, projectionMatrix;
    QMatrix3x3 normalMatrix;
    void changeFoV(float fov);
    void changeDispRatio(float disprat);
    void changeRotationAngleX(float angle);
    void changeRotationAngleY(float angle);
    void changeRotationAngleZ(float angle);
    void keyPressEvent(QKeyEvent* event);

    void changeXPosition(float n);
    void changeYPosition(float n);
    void changeZPosition(float n);
    QVector3D position;
    QVector3D eyeDirection;
protected:
private:
    float rotationAngle;
    float FoV;
    float dispRatio;

    void updateModelMatrix();
    void updateProjectionMatrix();
    void updateNormalMatrix();

    void initView();
};

#endif // CHARACTER_H
