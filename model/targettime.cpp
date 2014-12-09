#include "targettime.h"

TargetTime::TargetTime(QTime* basicTime, QTime* setupTime, QTime* restTime, QTime* distributeTime)
{
    this->setBasicTime(basicTime);
    this->setDistributeTime(distributeTime);
    this->setRestTime(restTime);
    this->setSetupTime(setupTime);
}

TargetTime::~TargetTime(){

}

QTime* TargetTime::getBasicTime(){
    return this->basicTime;
}

QTime* TargetTime::getDistributeTime(){
    return this->distributeTime;
}

QTime* TargetTime::getRestTime(){
    return this->restTime;
}

QTime* TargetTime::getSetupTime(){
    return this->setupTime;
}

void TargetTime::setBasicTime(QTime *bt){
    this->basicTime=bt;
}

void TargetTime::setDistributeTime(QTime *dt){
   this->distributeTime=dt;
}

void TargetTime::setRestTime(QTime *rt){
    this->restTime=rt;
}

void TargetTime::setSetupTime(QTime *st){
    this->setupTime=st;
}
