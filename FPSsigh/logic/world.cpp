#include "world.h"

#include <QVector>
#include <QVector3D>

World::World()
    : objectPath(QString("./../FPSSigh/models/")),
      chunks(QVector<Chunk *>()),
      loadedWorldObjects(QVector<WorldObject *>())
{
    initDefaultScene();

    // Load non-scene objects
    loadObject("character", "bullet");
}

void World::updateWorld(long long time) {
    for (Chunk* c : chunks) {
        for (WorldObject *wo : c->getObjects()) {
            if (wo->update(time)) {
                c->autoMoveObject(wo);
            }
        }
    }
}

bool inSight(Chunk* chunk, Character* character) {
    if (chunk->manhattanDistanceTo(character->position) > 30) {
        return false;
    }

    qDebug() << character->getDirection();
    if (QVector3D::dotProduct((character->position - chunk->getOrigin()).normalized(),
                              character->getDirection()) < 0) {
        return false;
    }
    return true;
}

QVector<Chunk *> World::getChunks(Character* cha) {
    QVector<Chunk *> cs = QVector<Chunk *>();
    for (Chunk *c : chunks) {
        if (inSight(c, cha)) {
            cs.append(c);
        }
    }
    return cs;
}
