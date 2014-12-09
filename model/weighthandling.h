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
    WeightHandling(HandleType* handleType, int* weight, int* way, UsedHand* hand, Transportation* transportation);
    ~WeightHandling();

    void setHandleType(HandleType* ht);
    void setWeight(int* we);
    void setWay(int* wa);
    void setHand(UsedHand* ha);
    void setTransportation(Transportation* t);

    HandleType* getHandleType();
    int* getWeight();
    int* getWay();
    UsedHand* getUsedHand();
    Transportation* getTransportation();

private:
    HandleType* handleType;
    int* weight;
    int* way;
    UsedHand* hand;
    Transportation* transportation;
};

#endif // WEIGHTHANDLING_H
