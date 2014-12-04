#include "weighthandling.h"


WeightHandling::WeightHandling(HandleType* handleType, Weight* weight, Way* way, UsedHand* hand, Tool* tool)
{
    this->handleType = handleType;
    this->weight = weight;
    this->way = way;
    this->hand = hand;
    this->tool = tool;
}
