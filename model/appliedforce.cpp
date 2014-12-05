#include "appliedforce.h"

AppliedForce::AppliedForce(Intensity* intensity, Direction* direction, Organ* organ, UsedHand* hand)
{
    this->direction = direction;
    this->hand = hand;
    this->intensity = intensity;
    this->organ = organ;
}
