#include "torso.h"

Torso::Torso()
{
    setTiltAngle(0);
    setTiltSidewaysAngle(0);
    setTwistAngle(0);
}

int Torso::getTiltAngle() const{
    return tiltAngle;
}
void Torso::setTiltAngle(int angle){
    tiltAngle = angle;
}

int Torso::getTiltSidewaysAngle() const{
    return tiltSidewaysAngle;
}
void Torso::setTiltSidewaysAngle(int angle){
    tiltSidewaysAngle = angle;
}

int Torso::getTwistAngle() const{
    return twistAngle;
}
void Torso::setTwistAngle(int angle){
    twistAngle = angle;
}
