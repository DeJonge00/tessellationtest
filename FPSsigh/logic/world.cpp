#include "world.h"

#include <QVector>
#include <QVector3D>


World::World()
    : objectPath(QString("./../FPSSigh/models/")),
      worldObjects(QVector<WorldObject *>()),
      loadedWorldObjects(QVector<WorldObject *>())
{
    initDefaultScene();

    // Load non-scene objects
    loadObject("character", "bullet");
}


void World::getSimpleWorldObjects(QVector<QVector3D>& vertices, QVector<QVector3D>& normals) {
    float size = 1;
    float middlex = 0;
    float middley = 0;

    float y = 0;
    float floor_size = 15;

    for (int nx = -floor_size; nx < floor_size; nx++) {
        for (int nz = -floor_size; nz < floor_size; nz++) {
            float x = middlex + nx*size;
            float z = middley + nz*size;
            vertices.append(QVector3D(x, y, z));
            vertices.append(QVector3D(x+size, y, z));
            vertices.append(QVector3D(x, y, z+size));

            normals.append(QVector3D(0, 1, 0));
            normals.append(QVector3D(0, 1, 0));
            normals.append(QVector3D(0, 1, 0));

            vertices.append(QVector3D(x+size, y, z));
            vertices.append(QVector3D(x+size, y, z+size));
            vertices.append(QVector3D(x, y, z+size));

            normals.append(QVector3D(0, 1, 0));
            normals.append(QVector3D(0, 1, 0));
            normals.append(QVector3D(0, 1, 0));
        }
    }

}

void World::getTessWorldObjects(QVector<QVector3D> &vertices, QVector<QVector3D> &normals) {
//    qDebug() << "getTessWOs";
    for (WorldObject *obj : worldObjects) {
        obj->getTessArrays(vertices, normals);
        for (Vertex *v : obj->vertices) {
//            qDebug() << v->coords;
        }
    }
}

void World::updateWorld(long long time) {
    for (WorldObject *wo : worldObjects) {
        wo->update(time);
    }
}

