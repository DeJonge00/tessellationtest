#ifndef CHARACTER_H
#define CHARACTER_H

#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QMouseEvent>

class Character
{
public:
    Character(QVector3D pos);
    Character() : Character(QVector3D(0, 0, 0)) {};
    QMatrix4x4 modelViewMatrix, projectionMatrix;
    QMatrix3x3 normalMatrix;
    void changeFoV(float fov);
    void changeDispRatio(float disprat);
    void changeRotationAngle(float angle);
    void keyPressEvent(QKeyEvent* event);

    void changeXPosition(float n);
    void changeYPosition(float n);
    void changeZPosition(float n);
    QVector3D position;
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
