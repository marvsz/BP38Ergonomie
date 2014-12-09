#include "handletype.h"

HandleType::HandleType(QString* handleType)
{
    this->setHandleType(handleType);
}

HandleType::~HandleType(){

}

QString* HandleType::getHandleType(){
    return this->handleType;
}

void HandleType::setHandleType(QString* h){
    this->handleType=h;
}
