#include "supply.h"

Supply::Supply(QString* description, QString* recoilIntensity, int* recoilCount, QString* vibrationIntensity, int* vibrationCount)
{
    this->setDescription(description);
    this->setRecoilCount(recoilCount);
    this->setRecoilIntensity(recoilIntensity);
    this->setVibrationCount(vibrationCount);
    this->setViprationIntensity(vibrationIntensity);
}

Supply::~Supply(){

}

QString* Supply::getDescription(){
    return this->description;
}

int* Supply::getRecoilCount(){
    return this->recoilCount;
}

QString* Supply::getRecoilIntensity(){
    return this->recoilIntensity;
}

int* Supply::getVibrationCount(){
    return this->vibrationCount;
}

QString* Supply::getVibrationIntensity(){
    return this->vibrationIntensity;
}

void Supply::setDescription(QString* d){
    this->description=d;
}

void Supply::setRecoilCount(int* rc){
    this->recoilCount=rc;
}

void Supply::setRecoilIntensity(QString* ri){
    this->recoilIntensity=ri;
}

void Supply::setVibrationCount(int* vc){
    this->vibrationCount=vc;
}

void Supply::setViprationIntensity(QString* vi){
    this->vibrationIntensity=vi;
}
