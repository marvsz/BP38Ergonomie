#include "way.h"

Way::Way(int* meter)
{
    this->setWay(meter);
}

Way::~Way(){

}

int* Way::getWay(){
    return this->meter;
}

void Way::setWay(int *m){
    this->meter=m;
}
