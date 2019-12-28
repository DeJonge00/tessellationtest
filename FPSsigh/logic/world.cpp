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
