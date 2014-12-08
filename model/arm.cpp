#include "arm.h"

Arm::Arm(int* upperArmPosition, int* lowerArmPosition, int* upperArmRotation, int* lowerArmRotation, int* upperArmOpening)
{
    this->upperArmPosition = upperArmPosition;
    this->lowerArmPosition = lowerArmPosition;
    this->upperArmRotation = upperArmRotation;
    this->lowerArmRotation = lowerArmRotation;
    this->upperArmOpening = upperArmOpening;
}

Arm::~Arm(){

}

