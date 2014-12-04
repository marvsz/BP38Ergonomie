#include "actingforce.h"

ActingForce::ActingForce(Intensity* intensity, Direction* direction, Organ* organ, UsedHand* hand)
{
    this->direction = direction;
    this->hand = hand;
    this->intensity = intensity;
    this->organ = organ;
}
