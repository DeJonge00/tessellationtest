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
        c = southChunk;
        qDebug() << "Moving" << wo->name << "north";
    }
    if (obj_origin.x() >= (origin.x() + width)) {
        c = northChunk;
        qDebug() << "Moving" << wo->name << "south";
    }
    if (obj_origin.z() < origin.y()) {
        c = eastChunk;
        qDebug() << "Moving" << wo->name << "west";
    }
    if (obj_origin.z() >= (origin.y() + length)) {
        c = westChunk;
        qDebug() << "Moving" << wo->name << "east";
    }
    if (c != this) {
        moveObject(c, wo);
    }
}

float Chunk::manhattanDistanceTo(QVector3D p) {
    return fmin(abs(origin.x() - p.x()), abs((origin.x() + width) - p.x()))
            + fmin(abs(origin.y() - p.z()), abs((origin.y() + length) - p.y()));
}

QVector<QVector3D> Chunk::getVisualBoundary(float h) {
    h -= 12;
    QVector<QVector3D> boundary_coords = QVector<QVector3D>();
    boundary_coords.append(QVector3D(0, h, 0));
    boundary_coords.append(QVector3D(width, h, 0));

    boundary_coords.append(QVector3D(width, h, 0));
    boundary_coords.append(QVector3D(width, h, length));

    boundary_coords.append(QVector3D(width, h, length));
    boundary_coords.append(QVector3D(0, h, length));

    boundary_coords.append(QVector3D(0, h, length));
    boundary_coords.append(QVector3D(0, h, 0));
    for (QVector3D c : boundary_coords) {
        boundary_coords.append(c + QVector3D(0, -2, 0));
    }
    return boundary_coords;
}

QVector3D Chunk::getOrigin() {
    return QVector3D(origin.x(), 0, origin.y());
}
