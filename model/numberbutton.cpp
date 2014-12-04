#include "numberbutton.h"

NumberButton::NumberButton(int number)
{
    this->setNumber(number);
}

NumberButton::~NumberButton(){

}

int NumberButton::getNumber(){
    return this->number;
}

void NumberButton::setNumber(int n){
    this->number=n;
}
