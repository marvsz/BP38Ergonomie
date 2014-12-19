#include "leg.h"

Leg::Leg()
{
    setHipAngle(0);
    setKneeAngle(0);
    setAnkleAngle(0);
}


int Leg::getHipAngle() const{
    return hipAngle;
}
void Leg::setHipAngle(int angle){
    hipAngle = angle;
}

int Leg::getKneeAngle() const{
    return kneeAngle;
}
void Leg::setKneeAngle(int angle){
    kneeAngle = angle;
}

int Leg::getAnkleAngle() const{
    return ankleAngle;
}
void Leg::setAnkleAngle(int angle){
    ankleAngle = angle;
}
