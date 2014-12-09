#include "organ.h"

Organ::Organ(QString* organ)
{
    this->organ=organ;
}

Organ::~Organ(){

}

QString* Organ::getOrgan(){
    return this->organ;
}

void Organ::setOrgan(QString* o){
    this->organ=o;
}
