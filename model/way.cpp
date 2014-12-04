#include "way.h"

Way::Way(int meter)
{
    this->setMeter(meter);
}

Way::~Way(){

}

int Way::getMeter() const{
    return this->meter;
}

void Way::setMeter(int m){
    this->meter = m;
}
