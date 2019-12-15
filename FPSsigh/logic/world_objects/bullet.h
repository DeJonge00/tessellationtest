#ifndef BULLET_H
#define BULLET_H

#include "logic/world_objects/worldobject.h"


class Bullet : public WorldObject
{
public:
    Bullet(QVector3D direction, float speed);
    Bullet() : Bullet(QVector3D(0, 1, 0), 1) {}

    virtual ~Bullet();

    bool update(long long time) override;
    Bullet* copy() override;

    QVector3D direction;
    float speed;

private:

};

#endif // BULLET_H
