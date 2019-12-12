#ifndef CHARACTER_H
#define CHARACTER_H

#include <QMatrix3x3>
#include <QMatrix4x4>

class Character
{
public:
    Character();
    QMatrix4x4 modelViewMatrix, projectionMatrix;
    QMatrix3x3 normalMatrix;
    void changeFoV(float fov);
    void changeDispRatio(float disprat);
private:
    float rotationAngle;
    float FoV;
    float dispRatio;

    void initView();
};

#endif // CHARACTER_H
