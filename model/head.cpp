#include "head.h"

Head::Head(int* rotation, int* tilt, int* sidewiseTilt)
{
    this->rotation = rotation;
    this->sidewiseTilt = sidewiseTilt;
    this->tilt = tilt;
}

Head::~Head(){

}
