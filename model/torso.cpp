#include "torso.h"

Torso::Torso(int* flextion, int* tilt, int* rotation)
{
    this->setFextion(flextion);
    this->setRotation(rotation);
    this->setTilt(tilt);
}

Torso::~Torso(){

}

int* Torso::getFlextion(){
    return this->flextion;
}

int* Torso::getRotation(){
    return this->rotation;
}

int* Torso::getTilt(){
    return this->tilt;
}

void Torso::setFextion(int *f){
    this->flextion=f;
}

void Torso::setRotation(int *r){
    this->rotation=r;
}

void Torso::setTilt(int *t){
    this->tilt=t;
}
