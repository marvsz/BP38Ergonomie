#include "head.h"

Head::Head(Angle* rotation, Angle* tilt, Angle* sidewiseTilt)
{
    this->rotation = rotation;
    this->sidewiseTilt = sidewiseTilt;
    this->tilt = tilt;
}

Head::~Head(){

}
