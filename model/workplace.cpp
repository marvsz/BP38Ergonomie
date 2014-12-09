#include "workplace.h"

Workplace::Workplace(QString* name, QString* description, QString* code, QString* population, Line* line, ShiftData* shiftdata, WorkerData* workerdata, Product* product, Remarks* remarks)
{
    this->setCode(code);
    this->setDescription(description);
    this->setLine(line);
    this->setName(name);
    this->setPopulation(population);
    this->setProduct(product);
    this->setRemarks(remarks);
    this->setShiftData(shiftdata);
    this->setWorkerData(workerdata);
}

Workplace::~Workplace(){

}

void Workplace::setName(QString* n){
    this->name=n;
}

void Workplace::setDescription(QString* d){
    this->description=d;
}

void Workplace::setCode(QString* c){
    this->code=c;
}

void Workplace::setPopulation(QString* p){
    this->population=p;
}

void Workplace::setLine(Line* l){
    this->line=l;
}

void Workplace::setShiftData(ShiftData* s){
    this->shiftdata = s;
}

void Workplace::setWorkerData(WorkerData* w){
    this->workerdata=w;
}

void Workplace::setProduct(Product* p){
    this->product=p;
}

void Workplace::setRemarks(Remarks* r){
    this->remarks=r;
}

QString* Workplace::getName(){
    return this->name;
}

QString* Workplace::getDescription(){
    return this->description;
}

QString* Workplace::getCode(){
    return this->code;
}

QString* Workplace::getPopulation(){
    return this->population;
}

Line* Workplace::getLine(){
    return this->line;
}

ShiftData* Workplace::getShiftData(){
    return this->shiftdata;
}

WorkerData* Workplace::getWorkerData(){
    return this->workerdata;
}

Product* Workplace::getProduct(){
    return this->product;
}

Remarks* Workplace::getRemarks(){
    return this->remarks;
}
