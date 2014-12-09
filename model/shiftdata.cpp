#include "shiftdata.h"

ShiftData::ShiftData(Shift* shift, TargetTime* targetTime, Pause* pause)
{
    this->setPause(pause);
    this->setShift(shift);
    this->setTargetTime(targetTime);
}

ShiftData::~ShiftData(){

}

Pause* ShiftData::getPause(){
    return this->pause;
}

Shift* ShiftData::getShift(){
    return this->shift;
}

TargetTime* ShiftData::getTargetTime(){
    return this->targetTime;
}

void ShiftData::setPause(Pause* p){
    this->pause=p;
}

void ShiftData::setShift(Shift* s){
    this->shift=s;
}

void ShiftData::setTargetTime(TargetTime* t){
    this->targetTime=t;
}
