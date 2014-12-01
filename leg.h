#ifndef LEG_H
#define LEG_H

#include "angle.h"
class Leg
{
public:
    Leg(Angle hip, Angle knee, Angle ankle);
    ~Leg();

private:
    Angle hip;
    Angle knee;
    Angle ankle;
};

#endif // LEG_H
