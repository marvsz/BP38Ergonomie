#include "leg.h"

Leg::Leg(int* hip, int* knee, int* ankle)
{
    this->setHip(hip);
    this->setKnee(knee);
    this->setAnkle(ankle);
}

Leg::~Leg(){

}

int* Leg::getAnkle(){
    return this->ankle;
}

int* Leg::getHip(){
    return this->hip;
}

int* Leg::getKnee(){
    return this->knee;
}

void Leg::setAnkle(int* a){
    this->ankle=a;
}

void Leg::setHip(int* h){
    this->hip=h;
}

void Leg::setKnee(int* k){
    this->knee=k;
}
