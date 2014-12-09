#include "general.h"

General::General(QString* description, QString* mtmCode, QString* activity, QString* subActivity, Product* product, int* workingHeight, int* distance, QString* gripType, QString* momentumIntensity, int* momentumCount)
{
    this->setActivity(activity);
    this->setDescription(description);
    this->setDistance(distance);
    this->setGripType(gripType);
    this->setMomentumCount(momentumCount);
    this->setMomentumIntensity(momentumIntensity);
    this->setMtmCode(mtmCode);
    this->setProduct(product);
    this->setSubActivity(subActivity);
    this->setWorkingHeight(workingHeight);
}

General::~General(){

}

QString* General::getActivity(){
    return this->activity;
}

QString* General::getDescription(){
    return this->description;
}

int* General::getDistance(){
    return this->distance;
}

QString* General::getGripType(){
    return this->gripType;
}

int* General::getMomentumCount(){
    return this->momentumCount;
}

QString* General::getMomentumIntensity(){
    return this->momentumIntensity;
}

QString* General::getMtmCode(){
    return this->mtmCode;
}

Product* General::getProduct(){
    return this->product;
}

QString* General::getSubActivity(){
    return this->subActivity;
}

int* General::getWorkingHeight(){
    return this->workingHeight;
}

void General::setActivity(QString* a){
    this->activity=a;
}

void General::setDescription(QString* de){
    this->description=de;
}

void General::setDistance(int* di){
    this->distance=di;
}

void General::setGripType(QString* g){
    this->gripType=g;
}

void General::setMomentumCount(int* mc){
    this->momentumCount=mc;
}

void General::setMomentumIntensity(QString* mi){
    this->momentumIntensity=mi;
}

void General::setMtmCode(QString* m){
    this->mtmCode=m;
}

void General::setProduct(Product* p){
    this->product=p;
}

void General::setSubActivity(QString* s){
    this->subActivity=s;
}

void General::setWorkingHeight(int* w){
    this->workingHeight=w;
}
