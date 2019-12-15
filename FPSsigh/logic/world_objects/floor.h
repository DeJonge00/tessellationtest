#ifndef FLOOR_H
#define FLOOR_H

#include "logic/world_objects/worldobject.h"


class Floor : public WorldObject
{
public:
    Floor(float middlex, float middlez, float middley, float sizex, float sizez);
    Floor(float sizex, float sizez) : Floor(0, 0, 0, sizex, sizez) {}
    Floor(float middlex, float middlez, float middley) : Floor(middlex, middlez, middley, 10, 10) {}
    Floor() : Floor(0, 0, 0, 10, 10) {}
    ~Floor();
};

#endif // FLOOR_H
