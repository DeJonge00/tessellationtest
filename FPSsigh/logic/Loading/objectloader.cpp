#include <QFile>
#include <QRegularExpression>

#include "logic/world.h"

void World::loadObject(QString dir_name, QString name) {
    loadedWorldObjects.append(objectLoader(objectPath + dir_name + "/" + name + ".obj", name));
}

WorldObject* World::getLoadedObject(QString name) {
    for (WorldObject* wo : loadedWorldObjects) {
        if (name.compare(wo->name) == 0) {
            return wo->copy();
        }
    }
    qDebug() << "Object" << name << "could not be copied, returning empty object";
    return new WorldObject();
}

bool tessValid(Face *f) {
    if (f->val != 4) {
        return false;
    }
// If rendering with 16 quads becomes better
//    HalfEdge *he = f->side;
//    do {
//        if (he->target->val != 4) {
//            return false;
//        }
//        he = he->next;
//    } while (he != f->side);
    return true;
}



WorldObject* World::objectLoader(QString fileName, QString name) {
    qDebug() << "Loading object:" << fileName;
    WorldObject *object = new WorldObject();
    object->name = name;

    // Open .obj file
    QFile file(fileName);
    if (!file.exists()) {
        qDebug() << "File" << fileName << "does not exist, empty object returned";
        return object;
    }

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "File" << fileName << "cannot be opened in readonly:text mode";
        return object;
    }

    while (!file.atEnd()) {
        QString line = file.readLine().trimmed();
        QStringList lineParts = line.split(QRegularExpression("\\s+"));

        // if it's a vertex position (v)
        if (lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
        {

            object->vertices.append(new Vertex());
            object->vertices.last()->index = object->vertices.size() - 1;
            object->vertices.last()->normal = QVector3D();
            object->vertices.last()->coords = QVector3D(lineParts.at(1).toFloat(),
                                               lineParts.at(2).toFloat(),
                                                lineParts.at(3).toFloat());
        }

        // if it's a normal (vn)
        else if (lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
        {
            object->normals.append(new QVector3D(lineParts.at(1).toFloat(),
                                        lineParts.at(2).toFloat(),
                                        lineParts.at(3).toFloat()));
        }

        // if it's face data (f)
        else if (lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
        {
            Face *face = new Face();
            QVector<HalfEdge *> ches = QVector<HalfEdge *>();

            for (int i = 1; i < lineParts.size(); i++) {
                QStringList split = lineParts.at(i).split("/");
                ches.append(new HalfEdge());
                ches.last()->target = object->vertices.at(split.at(0).toInt() - 1);
                ches.last()->target->out = ches.last(); // Needs to be updated later
                ches.last()->target->val++;
                ches.last()->target->normal += *object->normals.at(split.at(2).toInt() - 1);
                ches.last()->polygon = face;
                ches.last()->index = i + object->halfedges.size();
            }

            for (int i = 0; i < ches.size(); i++) {
                ches.at(i)->prev = ches.at((i-1+ches.size()) % ches.size());
                ches.at(i)->next = ches.at((i+1) % ches.size());
            }

            // Fill face variables
            face->side = ches.first();
            face->val = ches.size();
            face->normal = QVector3D();
            for (HalfEdge *he : ches) {
                face->normal += he->target->normal;
            }
            face->normal.normalize();
            face->index = object->faces.size();

            // Add face and halfedges
            object->faces.append(face);
            object->halfedges.append(ches);
        }
    }

    // Add halfedge twins
    //  Setup
    QVector<QVector<HalfEdge *>> potentialTwins = QVector<QVector<HalfEdge *>>();
    for (int i = 0; i < object->halfedges.size(); i++) {
        potentialTwins.append(QVector<HalfEdge *>());
    }
    //  Add potentials
    for (HalfEdge *he : object->halfedges) {
        potentialTwins[he->prev->target->index].append(he);
    }
    //  Search twins
    for (HalfEdge *he : object->halfedges) {
        if (he->twin == nullptr) {
            for (HalfEdge *potentialTwin : potentialTwins[he->target->index]) {
                if (potentialTwin->target->index == he->prev->target->index) {
                    he->twin = potentialTwin;
                    he->twin->twin = he;
                    break;
                }
            }
        }
    }

    //  Account for boundaries
    for (HalfEdge *he : object->halfedges) {
        if (he->twin == nullptr) {
            he->twin = new HalfEdge();
            he->twin->target = he->prev->target;
            he->target->val++;
            he->twin->target->isEdge = true;
        }
    }
    //  Search for nexts
    std::map<unsigned int, HalfEdge *> nexts = std::map<unsigned int, HalfEdge *>();
    for (HalfEdge *he : object->halfedges) {
        if (he->next == nullptr) {
            nexts[he->twin->target->index] = he;
        }
    }
    for (HalfEdge *he : object->halfedges) {
        if (he->next == nullptr) {
            he->next = nexts[he->target->index];
            he->next->prev = he;
        }
    }

    // Update vertex normals (unweighted for now) and outs
    for (Vertex *v : object->vertices) {
        v->normal.normalize();
        v->out = v->out->next;
    }

    // Check if faces are tessellation worthy
    for (Face *f : object->faces) {
        f->tessValid = tessValid(f);
//        qDebug() << f->tessValid;
//        f->tessValid = false;
    }

    qDebug() << "Successfully loaded" << object->name << object->faces.size();
    return object;
}












