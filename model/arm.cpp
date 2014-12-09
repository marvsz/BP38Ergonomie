#include "arm.h"

Arm::Arm(int* upperArmPosition, int* lowerArmPosition, int* upperArmRotation, int* lowerArmRotation, int* upperArmOpening)
{
    this->setLowerArmPosition(lowerArmPosition);
    this->setLowerArmRotation(lowerArmRotation);
    this->setUpperArmOpening(upperArmOpening);
    this->setUpperArmPosition(upperArmPosition);
    this->setUpperArmRotation(upperArmRotation);
}

Arm::~Arm(){

}

int* Arm::getLowerArmPosition(){
    return this->lowerArmPosition;
}

int* Arm::getLowerArmRotation(){
    return this->lowerArmRotation;
}

int* Arm::getUpperArmOpening(){
    return this->upperArmOpening;
}

int* Arm::getUpperArmPosition(){
    return this->upperArmPosition;
}

int* Arm::getUpperArmRotation(){
    return this->upperArmRotation;
}

void Arm::setLowerArmPosition(int* lap){
    this->lowerArmPosition=lap;
}

void Arm::setLowerArmRotation(int* lar){
    this->lowerArmRotation=lar;
}

void Arm::setUpperArmOpening(int* uao){
    this->upperArmOpening=uao;
}

void Arm::setUpperArmPosition(int* uap){
    this->upperArmPosition=uap;
}

void Arm::setUpperArmRotation(int* uar){
    this->upperArmRotation=uar;
}
