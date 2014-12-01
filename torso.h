#ifndef TORSO_H
#define TORSO_H

#include "angle.h"
class Torso
{
public:
    Torso(Angle flextion, Angle tilt, Angle rotation);
    ~Torso();

private:
    Angle flextion;
    Angle tilt;
    Angle rotation;
};

#endif // TORSO_H
