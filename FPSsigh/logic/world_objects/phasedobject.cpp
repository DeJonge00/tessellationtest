#include "phasedobject.h"
#include "math.h"

PhasedObject::PhasedObject(float s)
    : speed(s), phase(0)
{

}

PhasedObject* PhasedObject::copy() {
    PhasedObject* new_b = (PhasedObject *)WorldObject::copy();
    new_b->speed = speed;
    new_b->phase = phase;
    return new_b;
}

bool PhasedObject::update(long long time) {
    double scale = timeSinceLastEdit(time) / 10000;
    phase = fmod(phase + (speed * scale), 1);
    return false;
}
