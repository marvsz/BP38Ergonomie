#include "arm.h"

Arm::Arm()
{
    setOpeningAngle(0);
    setUpperArmAngle(0);
    setUpperArmTwist(0);
    setForeArmAngle(0);
    setForeArmTwist(0);
    setWristMovement(new QString(""));
}

int Arm::getOpeningAngle() const{
    return openingAngle;
}
void Arm::setOpeningAngle(int angle){
    openingAngle = angle;
}

int Arm::getUpperArmAngle() const{
    return upperArmAngle;
}
void Arm::setUpperArmAngle(int angle){
    upperArmAngle = angle;
}

int Arm::getUpperArmTwist() const{
    return upperArmTwist;
}
void Arm::setUpperArmTwist(int angle){
    upperArmTwist = angle;
}

int Arm::getForeArmAngle() const{
    return foreArmAngle;
}
void Arm::setForeArmAngle(int angle){
    foreArmAngle = angle;
}

int Arm::getForeArmTwist() const{
    return foreArmTwist;
}
void Arm::setForeArmTwist(int angle){
    foreArmTwist = angle;
}

QString* Arm::getWristMovement() const{
    return wristMovement;
}
void Arm::setWristMovement(QString* wristMovement){
    this->wristMovement = wristMovement;
}
