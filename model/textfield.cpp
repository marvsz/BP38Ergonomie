#include "textfield.h"

TextField::TextField(string description)
{
    this->setTextField(description);
}

TextField::~TextField(){

}

string TextField::getTextField(){
    return this->description;
}

void TextField::setTextField(string d){
    this->description=d;
}
