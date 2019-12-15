#include <QVector>
#include <QString>

#include "math.h"
#include "bullet.h"


Bullet::Bullet(QVector3D d, float s)
    : WorldObject(), direction(d), speed(s)
{

}

Bullet::~Bullet() {

}

Bullet* Bullet::copy() {
    Bullet* new_b = (Bullet *)WorldObject::copy();
    new_b->direction = direction;
    new_b->speed = speed;
    return new_b;
}

bool Bullet::update(long long time) {
//    qDebug() << direction << speed << translation << vertices.size();
    double scale = timeSinceLastEdit(time) / 1000000;
    translate(scale * speed * direction);
    return true;
}
