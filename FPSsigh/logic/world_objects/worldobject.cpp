#include <QMatrix4x4>

#include "worldobject.h"
#include "common_functions.h"


WorldObject::WorldObject()
    : name(QString("")), vertices(QVector<Vertex *>()), normals(QVector<QVector3D *>()),
      faces(QVector<Face *>()), halfedges(QVector<HalfEdge *>()),
      timeLastEdited(0), translation(QVector3D()), mode(0),
      phase(0), phaseType(0), phaseSpeed(1), phaseStrength(1)
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
        v_new->isEdge = v_orig->isEdge;

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
        f_new->tessValid = f_orig->tessValid;

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
    obj_new->timeLastEdited = timeLastEdited;
    obj_new->translation = translation;
    obj_new->rotation = rotation;
    obj_new->phase = phase;
    obj_new->phaseSpeed = phaseSpeed;
    obj_new->name = name + "_c";
    qDebug() << "Copied over" << obj_new->name;
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
    double scale = timeSinceLastEdit(time) / 10000;
    phase = fmod(phase + (phaseSpeed * scale), 1);
    return false;
}

QVector<QVector3D> WorldObject::getSimpleVertices() {
    QVector<QVector3D> vertices = QVector<QVector3D>();
    for (Face *f : faces) {
        if (!f->tessValid) {
            HalfEdge *current = f->side->next;
            do {
                vertices.append(f->side->target->coords);
                vertices.append(current->target->coords);
                current = current->next;
                vertices.append(current->target->coords);
            } while (current->next != f->side);
        }
    }
    return vertices;
}

QVector<QVector3D> WorldObject::getSimpleNormals() {
    QVector<QVector3D> normals = QVector<QVector3D>();
    for (Face *f : faces) {
        if (!f->tessValid) {
            HalfEdge *current = f->side->next;
            do {
                normals.append(f->side->target->normal);
                normals.append(current->target->normal);
                current = current->next;
                normals.append(current->target->normal);
            } while (current->next != f->side);
        }
    }
    return normals;
}

QVector<QVector3D> WorldObject::getTessVertices() {
    QVector<QVector3D> vertices = QVector<QVector3D>();
    for (Face *f : faces) {
        if (f->tessValid) {
            HalfEdge *current = f->side;
            do {
                vertices.append(current->target->coords);
                current = current->next;
            } while (current != f->side);
        }
    }
    return vertices;
}

QVector<QVector3D> WorldObject::getTessNormals() {
    QVector<QVector3D> normals = QVector<QVector3D>();
    for (Face *f : faces) {
        if (f->tessValid) {
            HalfEdge *current = f->side;
            do {
                normals.append(current->target->normal);
                current = current->next;
            } while (current != f->side);
        }
    }
    return normals;
}

QVector<QVector3D> WorldObject::getNormals() {
    QVector<QVector3D> normal_coords = QVector<QVector3D>();
    for (Vertex* v : vertices) {
        normal_coords.append(v->coords);
        normal_coords.append(v->coords + v->normal);
    }
    return normal_coords;
}


// Always scale and rotate before translating
void WorldObject::scale(float s) {
    for (Vertex *v : vertices) {
        v->coords *= s;
    }
}

void WorldObject::rotate(float x, float y, float z) {
    if (vertices.size() > 100) { return; }
    rotation = CommonFunctions::rotateVectorByAngles(rotation, x, y);
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
//    for (Vertex *v : vertices) {
//        v->coords += t;
//    }
}

bool isRegularMeshVertex(Vertex v) {
    HalfEdge *start = v.out, *current = v.out;
    do {
        if (current->polygon->val != 4) { return false; }
        current = current->twin->next;
    } while (current != start);
    return true;
}

// Return average of all vertices of a face
QVector3D calcFacePoint(HalfEdge* current) {
    HalfEdge* h = current;
    QVector3D f = QVector3D();
    do {
        f += current->target->coords;
        h = h->next;
    } while (h != current);
    f /= current->polygon->val;
    return f;
}

void WorldObject::toLimitPositions() {
    QVector<QVector3D> newVertexCoords = QVector<QVector3D>();


    // Calculate new position for each vertex
    for (int i = 0; i < vertices.size(); i++) {
        Vertex* currentVertex = vertices[i];

        // Branch boundaries, regular meshpoints and other
        if (currentVertex->isEdge) {
            newVertexCoords.append(currentVertex->coords);
        } else { // Irregular, non-boundary meshpoint == N-gon
            float n = currentVertex->val;
            QVector3D s = QVector3D();
            HalfEdge* current = currentVertex->out;
            do {
                s += ((current->target->coords + currentVertex->coords) / 2);
                s += calcFacePoint(current);
                // Loop index
                current = current->twin->next;
            } while (current != currentVertex->out);

            newVertexCoords.append((n-3)/(n+5) * currentVertex->coords + (4 / (n*(n+5)) * s));
        }
    }

    // Set vertices new coords
    for (int i = 0; i < newVertexCoords.size(); i++) {
        vertices[i]->coords = newVertexCoords[i];
    }

    // Update normals
    for (Vertex *v : vertices) {
        v->normal = QVector3D();
        HalfEdge *c = v->out;
        do {
            v->normal += c->target->coords;
            c = c->twin->next;
        } while (c != v->out);
    }
}
