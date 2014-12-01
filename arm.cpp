#include "arm.h"

Arm::Arm(Angle *upperArmPosition, Angle *lowerArmPosition, Angle *upperArmRotation, Angle *lowerArmRotation, Angle *upperArmOpening)
{
    this->upperArmPosition = upperArmPosition;
    this->lowerArmPosition = lowerArmPosition;
    this->upperArmRotation = upperArmRotation;
    this->lowerArmRotation = lowerArmRotation;
    this->upperArmOpening = upperArmOpening;
}

Arm::~Arm(){

}
