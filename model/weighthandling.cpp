#include "weighthandling.h"


WeightHandling::WeightHandling(HandleType* handleType, int* weight, int* way, UsedHand* hand, Transportation* transportation)
{
    this->handleType = handleType;
    this->weight = weight;
    this->way = way;
    this->hand = hand;
    this->transportation = transportation;
}
