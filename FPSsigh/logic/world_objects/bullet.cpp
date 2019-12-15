#include <QVector>
#include <QString>

#include "math.h"
#include "bullet.h"


Bullet::Bullet(QVector3D d, float s)
    : direction(d), speed(s)
{

}

Bullet::~Bullet() {

}

Bullet::Bullet(WorldObject* wo)
{
    vertices = wo->vertices;
    normals = wo->normals;
    faces = wo->faces;
    halfedges = wo->halfedges;
    name = wo->name;
    timeLastEdited = wo->timeLastEdited;
}

Bullet* Bullet::copy() {
    Bullet* new_b = (Bullet *)WorldObject::copy();
    new_b->direction = direction;
    new_b->speed = speed;
    return new_b;
}

bool Bullet::update(long long time) {
    double scale = timeSinceLastEdit(time) / 1000;
    qDebug() << "Scale:" << scale * direction << scale << direction;
    for (Vertex *v : vertices) {
        v->coords += scale * speed * direction;
    }
    return false;
}
