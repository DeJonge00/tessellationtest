#include <QMatrix4x4>

#include "worldobject.h"
#include "common_functions.h"


WorldObject::WorldObject()
    : name(QString("")), vertices(QVector<Vertex *>()), normals(QVector<QVector3D *>()),
      faces(QVector<Face *>()), halfedges(QVector<HalfEdge *>()),
      timeLastEdited(0), translation(QVector3D()), mode(0)
{

}

WorldObject* WorldObject::copy() {
    WorldObject* obj_new = new WorldObject();
    copyOver(obj_new);
    return obj_new;
}

void WorldObject::copyOver(WorldObject* obj_new) {
    std::map<unsigned int, HalfEdge *> halfEdgeMap = std::map<unsigned int, HalfEdge *>();
    std::map<unsigned int, Vertex *> vertexMap = std::map<unsigned int, Vertex *>();
    std::map<unsigned int, Face *> faceMap = std::map<unsigned int, Face *>();

    for (HalfEdge *he_orig : halfedges) {
        HalfEdge *he_new = new HalfEdge();
        he_new->index = obj_new->halfedges.size();
        he_new->sharpness = he_orig->sharpness;

        obj_new->halfedges.append(he_new);
        halfEdgeMap[he_orig->index] = he_new;

        // Temp, so index can be found later
        he_new->target = he_orig->target;
        he_new->next = he_orig->next;
        he_new->prev = he_orig->prev;
        he_new->twin = he_orig->twin;
        he_new->polygon = he_orig->polygon;
    }
//    qDebug() << "Copied halfedges";
    for (Vertex *v_orig : vertices) {
        Vertex *v_new = new Vertex();
        v_new->coords = v_orig->coords;
        v_new->out = halfEdgeMap[v_orig->out->index];
        v_new->val = v_orig->val;
        v_new->index = obj_new->vertices.size();
        v_new->sharpness = v_orig->sharpness;
        v_new->normal = v_orig->normal;

        obj_new->normals.append(&v_new->normal);
        obj_new->vertices.append(v_new);
        vertexMap[v_orig->index] = v_new;
    }
//    qDebug() << "Copied vertices";
    for (Face *f_orig : faces) {
        Face *f_new = new Face();
        f_new->side = halfEdgeMap[f_orig->side->index];
        f_new->val = f_orig->val;
        f_new->index = obj_new->faces.size();
        f_new->normal = f_orig->normal;

        obj_new->faces.append(f_new);
        faceMap[f_orig->index] = f_new;
    }
//    qDebug() << "Copied faces";
    for (HalfEdge *he_new : obj_new->halfedges) {
        he_new->target = vertexMap[he_new->target->index];
        he_new->next = halfEdgeMap[he_new->next->index];
        he_new->prev = halfEdgeMap[he_new->prev->index];
        he_new->twin = halfEdgeMap[he_new->twin->index];
        he_new->polygon = faceMap[he_new->polygon->index];
    }
    qDebug() << "Solved halfedges";
    obj_new->timeLastEdited = timeLastEdited;
    obj_new->translation = translation;
    obj_new->name = name + "_c";
}

double WorldObject::timeSinceLastEdit(long long time) {
    // Never edited before
    if (timeLastEdited == 0) {
        timeLastEdited = time;
        return 0;
    }
    float dt = time - timeLastEdited;
    timeLastEdited = time;
    return dt;
}

// Returns true if (big) move happens, so the chunk can be updated
bool WorldObject::update(long long time) {
    double t = timeSinceLastEdit(time);
    return false;
}

void WorldObject::getSimpleArrays(QVector<QVector3D>& vertices, QVector<QVector3D>& normals, QVector<unsigned int>& renderMode) {
    for (Face *f : faces) {
        if (f->val == 3) {
            HalfEdge *current = f->side;
            do {
                vertices.append(current->target->coords);
                normals.append(current->target->normal);
                renderMode.append(mode);
                current = current->next;
            } while (current != f->side);
        }
    }
}

void WorldObject::getTessArrays(QVector<QVector3D>& vertices, QVector<QVector3D>& normals, QVector<unsigned int>& renderMode) {
//    qDebug() << "Starting getTessArrays";
    for (Face *f : faces) {
        if (f->val == 4) {
            HalfEdge *current = f->side;
            do {
//                qDebug() << "::" << current->target->coords << current->target->normal << mode;
                vertices.append(current->target->coords);
                normals.append(current->target->normal);
                renderMode.append(mode);
                current = current->next;
            } while (current != f->side);
        }
    }
}

// Always scale and rotate before translating
void WorldObject::scale(float s) {
    for (Vertex *v : vertices) {
        v->coords *= s;
    }
}

void WorldObject::rotate(float x, float y, float z) {
    if (vertices.size() > 100) { return; }
    for (Vertex *v : vertices) {
        QVector3D t = translation;
        translate(-t);
        v->coords = CommonFunctions::rotateVectorByAngles(v->coords, x, y);
        v->normal = CommonFunctions::rotateVectorByAngles(v->normal, x, y);
        translate(t);
    }
}

void WorldObject::translate(QVector3D t) {
    translation += t;
    for (Vertex *v : vertices) {
        v->coords += t;
    }
}
