#include "math.h"
#include "logic/world.h"
#include "logic/world_objects/bullet.h"
#include "common_functions.h"

//void World::addCharacterObjects() {

//}

void World::addBullet(QVector3D location, float angleSide, float angleUp) {
    Bullet *b = new Bullet(CommonFunctions::angleToVector(angleSide, angleUp), 1);
    getLoadedObject("bullet")->copyOver(b);
    b->toLimitPositions();
    b->scale(0.05);
    b->translate(location);
    b->rotate(fmod(angleSide + 180, 360), -angleUp, 0);
    qDebug() << "Bullet ready";
    worldObjects.append(b);
}
