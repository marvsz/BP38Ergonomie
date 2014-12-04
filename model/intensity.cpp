#include "intensity.h"

Intensity::Intensity(int newton)
{
    this->setIntensity(newton);
}

Intensity::~Intensity(){

}

int Intensity::getIntensity() const{
    return this->newton;
}

void Intensity::setIntensity(int i){
    this->newton = i;
}


