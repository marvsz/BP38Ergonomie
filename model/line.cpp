#include "line.h"

Line::Line(QString* name, int* workstationQuantity, QString* description)
{
    this->setDescription(description);
    this->setName(name);
    this->setWorkstationQuantity(workstationQuantity);
}

Line::~Line(){

}

QString* Line::getDescription(){
    return this->description;
}

QString* Line::getName(){
    return this->name;
}

int* Line::getWorkstationQuantity(){
    return this->workstationQuantity;
}

void Line::setDescription(QString *d){
   this->description=d;
}

void Line::setName(QString *n){
    this->name=n;
}

void Line::setWorkstationQuantity(int *w){
    this->workstationQuantity=w;
}
