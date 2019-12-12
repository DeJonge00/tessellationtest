#include "world.h"

World::World()
{
    worldObjects = QVector<WorldObject>();
}

void World::getWorldObjects(QVector<QVector3D>& vertices, QVector<QVector3D>& normals) {
    vertices.append(QVector3D(-10, -10, -10));
    vertices.append(QVector3D(-10, -10, 10));
    vertices.append(QVector3D(10, -10, 10));

    vertices.append(QVector3D(-100, -12, -100));
    vertices.append(QVector3D(-100, -12, 100));
    vertices.append(QVector3D(100, -12, 100));

    normals.append(QVector3D(0, 1, 0));
    normals.append(QVector3D(0, 1, 0));
    normals.append(QVector3D(0, 1, 0));

    normals.append(QVector3D(0, 1, 0));
    normals.append(QVector3D(0, 1, 0));
    normals.append(QVector3D(0, 1, 0));
}

void World::addDefaultWorldObject() {
    // Vertices
    QVector<Vertex *> *vertices = new QVector<Vertex *>();
    for (int i = 0; i < 8; i++) {
        vertices->append(new Vertex());
//        vertices->last()->coords = QVector3D(i / 4, );
    }


    // Halfedges


    // Faces


    // Add object

}
