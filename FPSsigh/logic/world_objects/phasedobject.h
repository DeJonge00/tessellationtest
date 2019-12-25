#ifndef PHASEDOBJECT_H
#define PHASEDOBJECT_H

#include "logic/world_objects/worldobject.h"

class PhasedObject : WorldObject
{
public:
    PhasedObject(float speed);
    PhasedObject() : PhasedObject(1) {}

    bool update(long long time) override;
    PhasedObject* copy() override;

private:
    float speed;
    float phase;
};

#endif // PHASEDOBJECT_H
