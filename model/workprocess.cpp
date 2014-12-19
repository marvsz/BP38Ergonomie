#include "workprocess.h"

WorkProcess::WorkProcess(int id, QTime *begin, int specification)
{
    this->id = id;
    this->specification = specification;
    this->begin = begin;
    this->description = new QString("");
    this->end = new QTime();
    this->mtmCode = new QString("");
    this->graspingType = new QString("");
    this->frequency = -1;
    this->impulseCount = -1;
    this->impulseIntensity = -1;
    this->workingHeight = -1;
    this->distance = -1;
    this->bodyPosture = new BodyPosture();
    this->transportation = new Transportation();
    this->equipment = new Equipment();
    this->workCondition = new WorkCondition();
}

int WorkProcess::getDuration(){
    return QTimeToSeconds(end) - QTimeToSeconds(begin);
}

int WorkProcess::QTimeToSeconds(QTime* time){
    return time->hour()*3600 + time->minute()*60 + time->second();
}

int WorkProcess::getID() const{
    return id;
}

QString* WorkProcess::getDescription()const{
    return description;
}
void WorkProcess::setDescription(QString* description){
    this->description = description;
}

int WorkProcess::getSpecification() const{
    return specification;
}

QTime* WorkProcess::getBegin() const{
    return begin;
}
void WorkProcess::setBegin(QTime *begin){
    this->begin = begin;
}

QTime* WorkProcess::getEnd() const{
    return end;
}
void WorkProcess::setEnd(QTime *end){
    this->end = end;
}

QString* WorkProcess::getMTMCode() const{
    return mtmCode;
}
void WorkProcess::setMTMCode(QString *code){
    mtmCode = code;
}

QString* WorkProcess::getGraspingType() const{
    return graspingType;
}
void WorkProcess::setGraspingType(QString* type){
    this->graspingType = type;
}

int WorkProcess::getFrequency() const{
    return frequency;
}
void WorkProcess::setFrequency(int frequency){
    this->frequency = frequency;
}

int WorkProcess::getImpulseIntensity() const{
    return impulseIntensity;
}
void WorkProcess::setImpulseIntensity(int intensity){
    impulseIntensity = intensity;
}

int WorkProcess::getImpulseCount() const{
    return impulseCount;
}
void WorkProcess::setImpulseCount(int count){
    impulseCount = count;
}

int WorkProcess::getWorkingHeight() const{
    return workingHeight;
}
void WorkProcess::setWorkingHeight(int height){
    workingHeight = height;
}

int WorkProcess::getDistance() const{
    return distance;
}
void WorkProcess::setDistance(int distance){
    this->distance = distance;
}

BodyPosture* WorkProcess::getBodyPosture() const{
    return bodyPosture;
}

Transportation* WorkProcess::getTransportation() const{
    return transportation;
}

Equipment* WorkProcess::getEquipment() const{
    return equipment;
}

WorkCondition* WorkProcess::getWorkCondition() const{
    return workCondition;
}

AppliedForce* WorkProcess::getAppliedForce() const{
    return appliedForce;
}

LoadHandling* WorkProcess::getLoadHandling() const{
    return loadHandling;
}
