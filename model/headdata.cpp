#include "headdata.h"

HeadData::HeadData(Analyst* analyst, Factory* factory, Company* company, QDate* begin, QDate* end)
{
    this->setAnalyst(analyst);
    this->setBegin(begin);
    this->setCompany(company);
    this->setEnd(end);
    this->setFacotry(factory);
}

HeadData::~HeadData(){

}

Analyst* HeadData::getAnalyst(){
    return this->analyst;
}

Company* HeadData::getCompany(){
    return this->company;
}

Factory* HeadData::getFactory(){
    return this->factory;
}

QDate* HeadData::getBegin(){
    return this->begin;
}

QDate* HeadData::getEnd(){
    return this->end;
}

void HeadData::setAnalyst(Analyst* a){
    this->analyst=a;
}

void HeadData::setBegin(QDate* b){
    this->begin=b;
}

void HeadData::setCompany(Company* c){
    this->company=c;
}

void HeadData::setEnd(QDate* e){
    this->end=e;
}

void HeadData::setFacotry(Factory* f){
    this->factory=f;
}
