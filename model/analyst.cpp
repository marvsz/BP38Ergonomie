#include "analyst.h"

Analyst::Analyst(QString* lastName, QString* firstName, QString* employer, QString* experience)
{
    this->employer=employer;
    this->experience=experience;
    this->firstName=firstName;
    this->lastName=lastName;
}

Analyst::~Analyst(){

}
