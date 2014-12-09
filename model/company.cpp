#include "company.h"

Company::Company(QString* name)
{
    this->setName(name);
}
Company::~Company(){

}

QString* Company::getName(){
    return this->name;
}

void Company::setName(QString* n){
    this->name=n;
}
