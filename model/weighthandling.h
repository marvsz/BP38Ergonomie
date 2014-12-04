#ifndef WEIGHTHANDLING_H
#define WEIGHTHANDLING_H

#include "handletype.h"
#include "weight.h"
#include "way.h"
#include "usedhand.h"
#include "tool.h"
class WeightHandling
{
public:
    WeightHandling(HandleType* handleType, Weight* weight, Way* way, UsedHand* hand, Tool* tool);
    ~WeightHandling();

private:
    HandleType* handleType;
    Weight* weight;
    Way* way;
    UsedHand* hand;
    Tool* tool;
};

#endif // WEIGHTHANDLING_H
