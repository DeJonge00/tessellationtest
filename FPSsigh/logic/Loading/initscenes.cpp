#include <QDir>

#include "logic/world.h"
#include "logic/world_objects/floor.h"
#include "logic/world_objects/rotatingobject.h"

# define RENDERMODE_BLAND 0
# define RENDERMODE_NORMAL 1
# define RENDERMODE_DOT_PLAYER 2

# define PHASETYPE_BLAND 0
# define PHASETYPE_BEATING 1
# define PHASETYPE_HOVER 2


void World::loadScene(QString name) {
//    loadObject(QString("scene1"), QString("tower"));
    QDir directory(objectPath + "/" + name);
    QStringList objects = directory.entryList(QStringList() << "*.obj",QDir::Files);
    for (QString o : objects) {
        o.chop(4);
        loadObject(name, o);
    }
}

void World::initChunks() {
    int chunks_x = 100, chunks_z = 100;
    float width = 10, length = 10;
    float start_x = -50, start_z = -50;
    for (int z = 0; z < chunks_z; z++) {
        for (int x = 0; x < chunks_x; x++) {
            Chunk* c = new Chunk(QVector2D(start_x + x*width, start_z + z*length), width, length);
            chunks.append(c);
            if (z > 0) {
                Chunk* e = chunks[(z-1)*chunks_z + x];
                e->setWestChunk(c);
                c->setEastChunk(e);
            }
            if (x > 0) {
                Chunk* s = chunks[z*chunks_z + x-1];
                s->setNorthChunk(c);
                c->setSouthChunk(s);
            }
        }
    }
}

void World::initDefaultScene() {
    initChunks();
    loadScene("scene1");

    Floor* floor = new Floor(30, 30);
    floor->name = QString("Floor");
    floor->mode = RENDERMODE_BLAND;
    chunks.first()->addObject(floor);

    WorldObject* skybox = getLoadedObject("cube");
    skybox->name = QString("skybox");
    skybox->scale(15);
    skybox->mode = RENDERMODE_NORMAL;
    chunks.first()->addObject(skybox);

//    WorldObject* cube = getLoadedObject("opencube");
//    cube->phaseType = PHASETYPE_BEATING;
//    cube->phaseSpeed = 0.01;
//    cube->phaseStrength = 0.1;
//    cube->scale(1);
//    cube->translate(QVector3D(-4, 2, -2));
//    cube->mode = RENDERMODE_NORMAL;
//    chunks.first()->addObject(cube);

    WorldObject* tower = getLoadedObject("tower");
//    tower->toLimitPositions();
    tower->mode = RENDERMODE_NORMAL;
    tower->translate(QVector3D(1, 3, 0));
    chunks.first()->addObject(tower);

    RotatingObject* tower2 = new RotatingObject();
    getLoadedObject("tower")->copyOver(tower2);
//    WorldObject* tower2 = getLoadedObject("tower");
    tower2->mode = RENDERMODE_NORMAL;
    tower2->translate(QVector3D(-1, 3, 0));
    chunks.first()->addObject(tower2);

    WorldObject* sphere = getLoadedObject("sphere");
    sphere->mode = RENDERMODE_NORMAL;
    sphere->phaseType = PHASETYPE_HOVER;
    sphere->phaseSpeed = 0.001;
    sphere->phaseStrength = 0.1;
    sphere->translate(QVector3D(-1, 1, -1));
    chunks.first()->addObject(sphere);

//    RotatingObject* monkey = new RotatingObject();
//    getLoadedObject("monkey")->copyOver(monkey);
//    WorldObject* monkey = getLoadedObject("monkey");
//    monkey->mode = RENDERMODE_NORMAL;
//    monkey->scale(1.5);
//    monkey->translate(QVector3D(7, 2, 2));
//    chunks.first()->addObject(monkey);
}
