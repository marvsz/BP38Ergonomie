#include "torso.h"

Torso::Torso(int* flextion, int* tilt, int* rotation)
{
    this->flextion = flextion;
    this->rotation = rotation;
    this->tilt = tilt;
}

Torso::~Torso(){

}
