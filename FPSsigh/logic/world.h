#ifndef WORLD_H
#define WORLD_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLDebugLogger>
#include <QVector>
#include <QVector3D>

#include "logic/world_objects/chunk.h"
#include "logic/world_objects/worldobject.h"
#include "logic/object_structs/vertex.h"
#include "logic/object_structs/halfedge.h"
#include "logic/object_structs/face.h"


class World
{
public:
    World();

    QString objectPath;
    // initscenes
    void loadScene(QString name);
    void initDefaultScene();

    // character
//    void addCharacterObjects();
    void addBullet(QVector3D location, float angleSide, float angleUp);

    void updateWorld(long long time);
    WorldObject* getLoadedObject(QString name);
    void loadObject(QString dir_name, QString name);
    QVector<Chunk *> getChunks() { return chunks; }

private:
    QVector<Chunk *> chunks;
    QVector<WorldObject *> loadedWorldObjects;
    WorldObject* objectLoader(QString fileName, QString name);
    inline WorldObject* objectLoader(QString fileName) { return objectLoader(fileName, "Object"); };
};

#endif // WORLD_H
