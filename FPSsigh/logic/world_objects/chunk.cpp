#include "chunk.h"
#include "math.h"

Chunk::Chunk(QVector2D o, float w, float l)
    : worldObjects(QVector<WorldObject *>()),
      northChunk(nullptr), eastChunk(nullptr), southChunk(nullptr), westChunk(nullptr),
      width(w), length(l), origin(o)
{

}

void Chunk::moveObject(Chunk* c, WorldObject* wo) {
    worldObjects.removeOne(wo);
    if (c != nullptr) {
        c->addObject(wo);
    }
}

void Chunk::autoMoveObject(WorldObject* wo) {
    QVector3D obj_origin = wo->translation;
    Chunk* c = this;
    if (obj_origin.x() < origin.x()) {
        c = northChunk;
    }
    if (obj_origin.x() >= (origin.x() + width)) {
        c = southChunk;
    }
    if (obj_origin.y() < origin.y()) {
        c = westChunk;
    }
    if (obj_origin.y() >= (origin.y() + length)) {
        c = eastChunk;
    }
    if (c != this) {
        moveObject(c, wo);
    }
}

float Chunk::manhattanDistanceTo(QVector3D p) {
    return fmin(p.x() - origin.x(), p.x() - (origin.x() + width))
            + fmin(p.y() - origin.y(), p.y() - (origin.y() + length));
}
