#include "usedhand.h"

UsedHand::UsedHand(QString* hand)
{
    this->setHand(hand);
}

UsedHand::~UsedHand(){

}

QString* UsedHand::getHand(){
    return this->hand;
}

void UsedHand::setHand(QString* h){
    this->hand=h;
}
