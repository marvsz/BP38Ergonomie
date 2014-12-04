#include "organ.h"

Organ::Organ(string organ)
{
    this->setOrgan(organ);
}

Organ::~Organ(){

}

void Organ::setOrgan(string o){
    this->organ = o;
}

string Organ::getOrgan(){
    return organ;
}
