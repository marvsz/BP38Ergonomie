#include "numberfield.h"

NumberField::NumberField(int number)
{
    this->setNumber(number);
}

NumberField::~NumberField(){

}

int NumberField::getNumber(){
    return this->number;
}

void NumberField::setNumber(int n){
    this->number=n;
}
