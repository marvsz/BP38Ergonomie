#include "body.h"

Body::Body(Head* head, Torso* torso, Arm* rightArm, Arm* leftArm, Leg* rightLeg, Leg* leftLeg)
{
    this->setHead(head);
    this->setLeftArm(leftArm);
    this->setLeftLeg(leftLeg);
    this->setRightArm(rightArm);
    this->setRightLeg(rightLeg);
    this->setTorso(torso);
}

Body::~Body(){

}

Head* Body::getHead(){
    return this->head;
}

Torso* Body::getTorso(){
    return this->torso;
}

Arm* Body::getRightArm(){
    return this->rightArm;
}

Arm* Body::getLeftArm(){
    return this->leftArm;
}

Leg* Body::getRightLeg(){
    return this->rightLeg;
}

Leg* Body::getLeftLeg(){
    return this->leftLeg;
}

void Body::setHead(Head *h){
    this->head=h;
}

void Body::setLeftArm(Arm *la){
    this->leftArm=la;
}

void Body::setLeftLeg(Leg *ll){
    this->leftLeg=ll;
}

void Body::setRightArm(Arm *ra){
    this->rightArm=ra;
}

void Body::setRightLeg(Leg *rl){
    this->rightLeg=rl;
}

void Body::setTorso(Torso *t){
    this->torso=t;
}
