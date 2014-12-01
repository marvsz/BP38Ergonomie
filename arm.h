#ifndef ARM_H
#define ARM_H

#include "angle.h"
class Arm
{
public:
    Arm(Angle* upperArmPosition, Angle* lowerArmPosition, Angle* upperArmRotation, Angle* lowerArmRotation, Angle* upperArmOpening);
    ~Arm();

private:
    Angle* upperArmPosition;
    Angle* lowerArmPosition;
    Angle* upperArmRotation;
    Angle* lowerArmRotation;
    Angle* upperArmOpening;
};

#endif // ARM_H
