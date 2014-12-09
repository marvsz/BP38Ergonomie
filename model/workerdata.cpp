#include "workerdata.h"

WorkerData::WorkerData(QString* gender, int* age, int* height, QString* remarks, int* personalID)
{
    this->setAge(age);
    this->setGender(gender);
    this->setHeight(height);
    this->setPersonalId(personalID);
    this->setRemarks(remarks);
}

WorkerData::~WorkerData(){

}

void WorkerData::setGender(QString* g){
    this->gender=g;
}

void WorkerData::setAge(int* a){
    this->age=a;
}

void WorkerData::setHeight(int* h){
    this->height=h;
}

void WorkerData::setRemarks(QString* r){
    this->remarks=r;
}

void WorkerData::setPersonalId(int* p){
    this->personalID=p;
}

QString* WorkerData::getGender(){
    return this->gender;
}

int* WorkerData::getAge(){
    return this->age;
}

int* WorkerData::getHeight(){
    return this->height;
}

QString* WorkerData::getRemarks(){
    return this->remarks;
}

int* WorkerData::getPersonalId(){
    return this->personalID;
}
