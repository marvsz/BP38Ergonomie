#include "direction.h"

Direction::Direction(string direction)
{
    this->setDirection(direction);
}

Direction::~Direction(){

}

void Direction::setDirection(string d){
    this->direction = d;
}

string Direction::getDirection(){
    return direction;
}
