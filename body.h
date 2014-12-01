#ifndef BODY_H
#define BODY_H

#include "arm.h"
#include "torso.h"
#include "leg.h"
#include "head.h"
class Body
{
public:
    Body(Head head, Torso torso, Arm rightArm, Arm leftArm, Leg rightLeg, Leg leftLeg);
    ~Body();

private:
    Head head;
    Torso torso;
    Arm rightArm;
    Arm leftArm;
    Leg rightLeg;
    Leg leftLeg;
};

#endif // BODY_H
