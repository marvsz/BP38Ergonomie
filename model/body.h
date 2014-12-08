#ifndef BODY_H
#define BODY_H

#include "arm.h"
#include "torso.h"
#include "leg.h"
#include "head.h"
class Body
{
public:
    Body(Head* head, Torso* torso, Arm* rightArm, Arm* leftArm, Leg* rightLeg, Leg* leftLeg);
    ~Body();

    void setHead(Head* h);
    void setTorso(Torso* t);
    void setRightArm(Arm* ra);
    void setLeftArm(Arm* la);
    void setRightLeg(Leg* rl);
    void setLeftLeg(Leg* ll);

private:
    Head* head;
    Torso* torso;
    Arm* rightArm;
    Arm* leftArm;
    Leg* rightLeg;
    Leg* leftLeg;
};

#endif // BODY_H
