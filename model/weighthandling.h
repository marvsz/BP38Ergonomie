#ifndef WEIGHTHANDLING_H
#define WEIGHTHANDLING_H

#include "handletype.h"
#include "weight.h"
#include "way.h"
#include "usedhand.h"
#include "transportation.h"
class WeightHandling
{
public:
    WeightHandling(HandleType* handleType, Weight* weight, Way* way, UsedHand* hand, Transportation* transportation);
    ~WeightHandling();

private:
    HandleType* handleType;
    Weight* weight;
    Way* way;
    UsedHand* hand;
    Transportation* transportation;
};

#endif // WEIGHTHANDLING_H
