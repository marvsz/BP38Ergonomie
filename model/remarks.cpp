#include "remarks.h"

Remarks::Remarks(QString* problemId, QString* problemDescription, QString* sanctionId, QString* sanctionDescription, QString* factoryPerception)
{
    this->setFactoryPerception(factoryPerception);
    this->setProblemDescription(problemDescription);
    this->setProblemId(problemId);
    this->setSanctionDescription(sanctionDescription);
    this->setSanctionId(sanctionId);
}

Remarks::~Remarks(){

}

QString* Remarks::getFactoryPerception(){
    return this->factoryPerception;
}

QString* Remarks::getProblemDescription(){
    return this->problemDescription;
}

QString* Remarks::getProblemId(){
    return this->problemId;
}

QString*  Remarks::getSanctionDescription(){
    return this->sanctionDescription;
}

QString* Remarks::getSanctionId(){
    return this->sanctionId;
}

void Remarks::setFactoryPerception(QString *fp){
    this->factoryPerception=fp;
}

void Remarks::setProblemDescription(QString *pd){
    this->problemDescription=pd;
}

void Remarks::setProblemId(QString *pi){
    this->problemId=pi;
}

void Remarks::setSanctionDescription(QString *sd){
    this->sanctionDescription=sd;
}

void Remarks::setSanctionId(QString *si){
    this->sanctionId;
}
