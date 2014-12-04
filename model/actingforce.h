#ifndef ACTINGFORCE_H
#define ACTINGFORCE_H

#include "intensity.h"
#include "direction.h"
#include "organ.h"
#include "usedhand.h"

class ActingForce
{
public:
    ActingForce(Intensity* intensity, Direction* direction, Organ* organ, UsedHand* hand);
    ~ActingForce();

private:
    Intensity* intensity;
    Direction* direction;
    Organ* organ;
    UsedHand* hand;
};

#endif // ACTINGFORCE_H
