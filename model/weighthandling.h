#ifndef WEIGHTHANDLING_H
#define WEIGHTHANDLING_H

#include "handletype.h"
#include "weight.h"
#include "way.h"
#include "usedhand.h"
#include "transportationlistelement.h"

class WeightHandling
{
public:
    WeightHandling(HandleType* handleType, int* weight, int* way, UsedHand* hand, TransportationListElement* transportation);
    ~WeightHandling();

    void setHandleType(HandleType* ht);
    void setWeight(int* we);
    void setWay(int* wa);
    void setHand(UsedHand* ha);
    void setTransportation(TransportationListElement* t);

    HandleType* getHandleType();
    int* getWeight();
    int* getWay();
    UsedHand* getUsedHand();
    TransportationListElement* getTransportation();

private:
    HandleType* handleType;
    int* weight;
    int* way;
    UsedHand* hand;
    TransportationListElement* transportation;
};

#endif // WEIGHTHANDLING_H
