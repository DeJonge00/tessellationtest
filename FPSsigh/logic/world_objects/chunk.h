#ifndef CHUNK_H
#define CHUNK_H

#include <QVector>
#include <QVector2D>
#include "logic/world_objects/worldobject.h"

class Chunk
{
public:
    Chunk(QVector2D origin, float width, float length);
    Chunk() : Chunk(QVector2D(0, 0), 1, 1) {}

    QVector<WorldObject *> getObjects() { return worldObjects; }
    void addObject(WorldObject* worldObject) { worldObjects.append(worldObject); }
    void moveObject(Chunk* chunk, WorldObject* worldObject);
    void autoMoveObject(WorldObject* wo);
    float manhattanDistanceTo(QVector3D position);
private:
    QVector<WorldObject *> worldObjects;
    Chunk* northChunk;
    Chunk* eastChunk;
    Chunk* southChunk;
    Chunk* westChunk;
    float width, length;
    QVector2D origin;
};

#endif // CHUNK_H
