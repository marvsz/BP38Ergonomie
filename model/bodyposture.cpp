#include "bodyposture.h"

BodyPosture::BodyPosture()
{
    id = -1;
    legPosture = new QString("");
    setHead(new Head());
    setTorso(new Torso());
    setLeftArm(new Arm());
    setRightArm(new Arm());
    setLeftLeg(new Leg());
    setRightLeg(new Leg());
}


int BodyPosture::getID() const{
    return id;
}

Head* BodyPosture::getHead() const{
    return head;
}
void BodyPosture::setHead(Head *head){
    this->head = head;
}

Torso* BodyPosture::getTorso() const{
    return torso;
}
void BodyPosture::setTorso(Torso *torso){
    this->torso = torso;
}

Arm* BodyPosture::getLeftArm() const{
    return leftArm;
}
void BodyPosture::setLeftArm(Arm *arm){
    leftArm = arm;
}

Arm* BodyPosture::getRightArm() const{
    return rightArm;
}
void BodyPosture::setRightArm(Arm *arm){
    rightArm = arm;
}

Leg* BodyPosture::getLeftLeg() const{
    return leftLeg;
}
void BodyPosture::setLeftLeg(Leg *leg){
    leftLeg = leg;
}

Leg* BodyPosture::getRightLeg() const{
    return rightLeg;
}
void BodyPosture::setRightLeg(Leg *leg){
    rightLeg = leg;
}

QString* BodyPosture::getLegPosture() const{
    return legPosture;
}
void BodyPosture::setLegPosture(QString* legPosture){
    this->legPosture = legPosture;
}
