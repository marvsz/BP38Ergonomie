#include "body.h"

Body::Body(Head* head, Torso* torso, Arm* rightArm, Arm* leftArm, Leg* rightLeg, Leg* leftLeg)
{
    this->head = head;
    this->torso = torso;
    this->leftArm = leftArm;
    this->rightArm = rightArm;
    this->leftLeg = leftLeg;
    this->rightLeg = rightLeg;
}

Body::~Body(){

}
