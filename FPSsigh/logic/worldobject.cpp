#include "worldobject.h"

WorldObject::WorldObject()
    : vertices(QVector<Vertex *>()), normals(QVector<QVector3D *>()),
      faces(QVector<Face *>()), halfedges(QVector<HalfEdge *>()), name(QString(""))
{

}

void WorldObject::getSimpleArrays(QVector<QVector3D>& vertices, QVector<QVector3D>& normals) {
    for (Face *f : faces) {
        if (f->val == 3) {
            HalfEdge *current = f->side;
            do {
                vertices.append(current->target->coords);
                normals.append(current->target->normal);
                current = current->next;
            } while (current != f->side);
        }
    }
}

void WorldObject::getTessArrays(QVector<QVector3D>& vertices, QVector<QVector3D>& normals) {
    for (Face *f : faces) {
        if (f->val == 4) {
            HalfEdge *current = f->side;
            do {
                vertices.append(current->target->coords);
                normals.append(current->target->normal);
                current = current->next;
            } while (current != f->side);
        }
    }
}

// Always scale before translating
void WorldObject::scale(float s) {
    for (Vertex *v : vertices) {
        v->coords *= s;
    }
}

void WorldObject::translate(QVector3D t) {
    for (Vertex *v : vertices) {
        v->coords += t;
    }
}
