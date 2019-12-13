#include "world.h"
#include <QVector>
#include <QVector3D>

World::World()
{
    worldObjects = QVector<WorldObject>();
    initDefaultScene();
}

void World::initDefaultScene() {
    worldObjects.append(createCube(QVector3D(0, 0, -2), 1));
    worldObjects.append(createCube(QVector3D(2, 0, -2), 1));
    worldObjects.append(createCube(QVector3D(-2, 0, -3), 1));
    worldObjects.append(createCube(QVector3D(-2, 1, -3), 1));
    worldObjects.append(createCube(QVector3D(-2, 2, -3), 1));
}

void World::getWorldObjects(QVector<QVector3D>& vertices, QVector<QVector3D>& normals) {
    float size = 1;
    float middlex = 0;
    float middley = 0;

    float y = 0;
    float floor_size = 10;

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

void World::getWorldQuads(QVector<QVector3D>& vertices, QVector<QVector3D>& normals) {
    for (WorldObject obj : worldObjects) {
        vertices.append(obj.getVertices());
        normals.append(obj.getNormals());
    }
}

WorldObject World::createCube(QVector3D location, float s) {
    QVector<QVector3D> vertices = QVector<QVector3D>();
    QVector<QVector3D> normals = QVector<QVector3D>();

    float x = location.x(), y = location.y(), z = location.z();

    // Front face
    vertices.append(QVector3D(x, y, z+s));
    vertices.append(QVector3D(x+s, y,z+s));
    vertices.append(QVector3D(x+s, y+s, z+s));
    vertices.append(QVector3D(x, y+s, z+s));

    normals.append(QVector3D(0, 0, 1));
    normals.append(QVector3D(0, 0, 1));
    normals.append(QVector3D(0, 0, 1));
    normals.append(QVector3D(0, 0, 1));

    // Back face
    vertices.append(QVector3D(x+s, y, z));
    vertices.append(QVector3D(x, y, z));
    vertices.append(QVector3D(x, y+s, z));
    vertices.append(QVector3D(x+s, y+s, z));

    normals.append(QVector3D(0, 0, -1));
    normals.append(QVector3D(0, 0, -1));
    normals.append(QVector3D(0, 0, -1));
    normals.append(QVector3D(0, 0, -1));

    // Top face
    vertices.append(QVector3D(x, y+s, z+s));
    vertices.append(QVector3D(x+s, y+s, z+s));
    vertices.append(QVector3D(x+s, y+s, z));
    vertices.append(QVector3D(x, y+s, z));

    normals.append(QVector3D(0, 1, 0));
    normals.append(QVector3D(0, 1, 0));
    normals.append(QVector3D(0, 1, 0));
    normals.append(QVector3D(0, 1, 0));

    // Bottom Face
    vertices.append(QVector3D(x, y, z));
    vertices.append(QVector3D(x+s, y, z));
    vertices.append(QVector3D(x+s, y, z+s));
    vertices.append(QVector3D(x, y, z+s));

    normals.append(QVector3D(0, -1, 0));
    normals.append(QVector3D(0, -1, 0));
    normals.append(QVector3D(0, -1, 0));
    normals.append(QVector3D(0, -1, 0));

    // Left face
    vertices.append(QVector3D(x, y, z));
    vertices.append(QVector3D(x, y, z+s));
    vertices.append(QVector3D(x, y+s, z+s));
    vertices.append(QVector3D(x, y+s, z));

    normals.append(QVector3D(-1, 0, 0));
    normals.append(QVector3D(-1, 0, 0));
    normals.append(QVector3D(-1, 0, 0));
    normals.append(QVector3D(-1, 0, 0));

    // Right Face
    vertices.append(QVector3D(x+1, y, z+s));
    vertices.append(QVector3D(x+1, y, z));
    vertices.append(QVector3D(x+1, y+s, z));
    vertices.append(QVector3D(x+1, y+s, z+s));

    normals.append(QVector3D(1, 0, 0));
    normals.append(QVector3D(1, 0, 0));
    normals.append(QVector3D(1, 0, 0));
    normals.append(QVector3D(1, 0, 0));

    return WorldObject(vertices, normals);
}
