#include "appliedforce.h"

AppliedForce::AppliedForce(QString *organ, QString *direction)
{
    id = -1;
    setOrgan(organ);
    setDirection(direction);
    setIntensity(0);
}


int AppliedForce::getID() const{
    return id;
}

QString* AppliedForce::getOrgan() const{
    return organ;
}
void AppliedForce::setOrgan(QString *organ){
    this->organ = organ;
}

QString* AppliedForce::getDirection() const{
    return direction;
}
void AppliedForce::setDirection(QString *direction){
    this->direction = direction;
}

int AppliedForce::getIntensity() const{
    return intensity;
}
void AppliedForce::setIntensity(int intensity){
    this->intensity = intensity;
}

