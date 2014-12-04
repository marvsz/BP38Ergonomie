#ifndef HEAD_H
#define HEAD_H

#include "angle.h"
class Head
{
public:
    Head(Angle* rotation, Angle* tilt, Angle* sidewiseTilt);
    ~Head();

private:
    Angle* rotation;
    Angle* tilt;
    Angle* sidewiseTilt;
};

#endif // HEAD_H
