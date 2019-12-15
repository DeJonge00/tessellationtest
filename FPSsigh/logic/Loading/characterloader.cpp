#include "math.h"
#include "logic/world.h"
#include "logic/world_objects/bullet.h"
#include "common_functions.h"

//void World::addCharacterObjects() {

//}

void World::addBullet(QVector3D location, float angleSide, float angleUp) {
    qDebug() << "Bullet updating";
    Bullet *b = (Bullet *)getLoadedObject("bullet");

    b->direction = CommonFunctions::angleToVector(angleSide, angleUp);
    b->speed = 0.01;
    b->scale(0.1);
    b->rotate(fmod(angleSide + 180, 360), -angleUp, 0);
    b->translate(location);
    worldObjects.append(b);
}
