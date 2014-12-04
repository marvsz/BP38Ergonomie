#include "torso.h"

Torso::Torso(Angle* flextion, Angle* tilt, Angle* rotation)
{
    this->flextion = flextion;
    this->rotation = rotation;
    this->tilt = tilt;
}

Torso::~Torso(){

}
