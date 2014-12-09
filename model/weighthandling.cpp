#include "weighthandling.h"


WeightHandling::WeightHandling(HandleType* handleType, int* weight, int* way, UsedHand* hand, Transportation* transportation)
{
    this->setHand(hand);
    this->setHandleType(handleType);
    this->setTransportation(transportation);
    this->setWay(way);
    this->setWeight(weight);
}

WeightHandling::~WeightHandling(){

}

HandleType* WeightHandling::getHandleType(){
    return this->handleType;
}

Transportation* WeightHandling::getTransportation(){
    return this->transportation;
}

UsedHand* WeightHandling::getUsedHand(){
    return this->hand;
}

int* WeightHandling::getWay(){
    return this->way;
}

int* WeightHandling::getWeight(){
    return this->weight;
}

void WeightHandling::setHand(UsedHand *ha){
    this->hand=ha;
}

void WeightHandling::setHandleType(HandleType *ht){
    this->handleType=ht;
}

void WeightHandling::setTransportation(Transportation *t){
    this->transportation=t;
}

void WeightHandling::setWay(int *wa){
    this->way=wa;
}

void WeightHandling::setWeight(int *we){
    this->weight=we;
}
