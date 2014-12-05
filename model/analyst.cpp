#include "analyst.h"

Analyst::Analyst(TextField* lastName, TextField* firstName, TextField* employer, TextField* experience)
{
    this->employer=employer;
    this->experience=experience;
    this->firstName=firstName;
    this->lastName=lastName;
}

Analyst::~Analyst(){

}
