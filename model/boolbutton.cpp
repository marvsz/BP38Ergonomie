#include "boolbutton.h"

BoolButton::BoolButton(bool value)
{
    this->setValue(value);
}

BoolButton::~BoolButton(){

}

bool BoolButton::getValue(){
    return this->value;
}

void BoolButton::setValue(bool b){
    this->value=b;
}
