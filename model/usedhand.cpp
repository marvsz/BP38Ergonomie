#include "usedhand.h"

UsedHand::UsedHand(string hand)
{
    this->setHand(hand);
}

UsedHand::~UsedHand(){

}

string UsedHand::getHand() const{
    return this->hand;
}

void UsedHand::setHand(string h){
    this->hand = h;
}
