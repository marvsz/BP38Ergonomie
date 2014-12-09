#include "head.h"

Head::Head(int* rotation, int* tilt, int* sidewiseTilt)
{
    this->setRotation(rotation);
    this->setSidewiseTilt(sidewiseTilt);
    this->setTilt(tilt);
}

Head::~Head(){

}

int* Head::getRotation(){
    return this->rotation;
}

int* Head::getSidewiseTilt(){
    return this->sidewiseTilt;
}

int* Head::getTilt(){
    return this->tilt;
}

void Head::setRotation(int* r){
    this->rotation=r;
}

void Head::setSidewiseTilt(int* s){
    this->sidewiseTilt=s;
}

void Head::setTilt(int* t){
    this->tilt=t;
}
