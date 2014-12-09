#include "appliedforce.h"

AppliedForce::AppliedForce(Intensity* intensity, Direction* direction, Organ* organ, UsedHand* hand)
{
    this->direction = direction;
    this->hand = hand;
    this->intensity = intensity;
    this->organ = organ;
}

AppliedForce::~AppliedForce(){

}

Direction* AppliedForce::getDirection(){
    return this->direction;
}

UsedHand* AppliedForce::getHand(){
    return this->hand;
}

Intensity* AppliedForce::getIntensity(){
    return this->intensity;
}

Organ* AppliedForce::getOrgan(){
    return this->organ;
}

void AppliedForce::setDirection(Direction* d){
    this->direction=d;
}

void AppliedForce::setHand(UsedHand* h){
    this->hand=h;
}

void AppliedForce::setIntensity(Intensity* i){
    this->intensity=i;
}

void AppliedForce::setOrgan(Organ* o){
    this->organ=o;
}
