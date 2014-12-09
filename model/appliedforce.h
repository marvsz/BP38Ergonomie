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

    void setIntensity(Intensity* i);
    void setDirection(Direction* d);
    void setOrgan(Organ* o);
    void setHand(UsedHand* h);

    Intensity* getIntensity();
    Direction* getDirection();
    Organ* getOrgan();
    UsedHand* getHand();

private:
    Intensity* intensity;
    Direction* direction;
    Organ* organ;
    UsedHand* hand;
};

#endif // APPLIEDFORCE_H
