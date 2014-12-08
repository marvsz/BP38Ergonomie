#include "analyst.h"

Analyst::Analyst(QString* lastName, QString* firstName, QString* employer, QString* experience)
{
    this->setEmployer(employer);
    this->setExperience(experience);
    this->setFirstName(firstName);
    this->setLastName(lastName);
}

Analyst::~Analyst(){

}

void Analyst::setEmployer(QString* em){
    this->employer=em;
}

void Analyst::setExperience(QString* ex){
    this->experience=ex;
}

void Analyst::setFirstName(QString* fN){
    this->firstName=fN;
}

void Analyst::setLastName(QString* lN){
    this->lastName=lN;
}

QString* Analyst::getEmployer(){
    return this->employer;
}

QString* Analyst::getExperience(){
    return this->experience;
}

QString* Analyst::getFirstName(){
    return this->firstName;
}

QString* Analyst::getLastName(){
    return this->lastName;
}
