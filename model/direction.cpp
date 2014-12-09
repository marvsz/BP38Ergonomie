#include "direction.h"

Direction::Direction(QString* direction)
{
    this->setDirection(direction);
}

Direction::~Direction(){

}

QString* Direction::getDirection(){
    return this->direction;
}

void Direction::setDirection(QString* d){
    this->direction=d;
}
