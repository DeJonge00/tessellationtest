#ifndef ROTATINGOBJECT_H
#define ROTATINGOBJECT_H

#include "worldobject.h"

class RotatingObject : public WorldObject
{
public:
    RotatingObject(float speed);
    RotatingObject() : RotatingObject(1) {}

    bool update(long long time) override;
    RotatingObject* copy() override;

private:
    float speed;
};

#endif // ROTATINGOBJECT_H
