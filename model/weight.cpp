#include "weight.h"

Weight::Weight(int weight)
{
    this->setWeight(weight);
}

Weight::~Weight(){

}

int Weight::getWeight() const{
    return this->weight;
}

void Weight::setWeight(int w){
    this->weight = w;
}
