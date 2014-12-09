#include "angle.h"

Angle::Angle(int* degree)
{
    this->setDegree(degree);
}

Angle::~Angle(){

}

int* Angle::getDegree() const{
    return this->degree;
}

void Angle::setDegree(int* d) {
    this->degree = d;
}
