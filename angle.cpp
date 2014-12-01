#include "angle.h"

Angle::Angle(int degree)
{
    this->degree = degree;
}

Angle::~Angle(){

}

int Angle::getDegree() const{
    return this->degree;
}

void Angle::setDegree(int degree) const{
    this->degree = degree;
}
