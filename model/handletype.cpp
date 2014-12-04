#include "handletype.h"

HandleType::HandleType(string handleType)
{
    this->setHandleType(handleType);
}

HandleType::~HandleType(){

}

string HandleType::getHandleType(){
    return this->handleType;
}

void HandleType::setHandleType(string h){
    this->handleType=h;
}
