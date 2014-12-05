#ifndef APPLIEDFORCE_H
#define APPLIEDFORCE_H

#include "intensity.h"
#include "direction.h"
#include "organ.h"
#include "usedhand.h"

class AppliedForce
{
public:
    AppliedForce(Intensity* intensity, Direction* direction, Organ* organ, UsedHand* hand);
    ~AppliedForce();

private:
    Intensity* intensity;
    Direction* direction;
    Organ* organ;
    UsedHand* hand;
};

#endif // APPLIEDFORCE_H
