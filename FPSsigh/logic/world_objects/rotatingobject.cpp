#include "rotatingobject.h"

RotatingObject::RotatingObject(float s)
    : speed(s)
{

}

RotatingObject* RotatingObject::copy() {
    RotatingObject* new_b = (RotatingObject *)WorldObject::copy();
    new_b->speed = speed;
    return new_b;
}

bool RotatingObject::update(long long time) {
    double scale = timeSinceLastEdit(time) / 1000000;
    rotate(speed*scale, 0, 0);
    return false;
}
