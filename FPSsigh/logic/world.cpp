#include "world.h"

#include <QVector>
#include <QVector3D>

# define WORLD_MAX_X 15
# define WORLD_MAX_Y 15
# define WORLD_MAX_Z 15
# define WORLD_MIN_X -15
# define WORLD_MIN_Y -15
# define WORLD_MIN_Z -15

World::World()
    : objectPath(QString("./../FPSSigh/models/")),
      worldObjects(QVector<WorldObject *>()),
      loadedWorldObjects(QVector<WorldObject *>())
{
    initDefaultScene();

    // Load non-scene objects
    loadObject("character", "bullet");
}

void World::updateWorld(long long time) {
    for (WorldObject *wo : worldObjects) {
        wo->update(time);
        if (checkOutOfBounds(wo)) {
            qDebug() << "Deleting" << wo->name;
            worldObjects.removeOne(wo);
        }
    }
}

bool World::checkOutOfBounds(WorldObject *wo) {
    for (Vertex *v : wo->vertices) {
        if ((v->coords.x() > WORLD_MAX_X) || (v->coords.x() < WORLD_MIN_X) ||
                (v->coords.y() > WORLD_MAX_Y) || (v->coords.y() < WORLD_MIN_Y) ||
                (v->coords.z() > WORLD_MAX_Z) || (v->coords.z() < WORLD_MIN_Z)) {
            return true;
        }
    }
    return false;
}
