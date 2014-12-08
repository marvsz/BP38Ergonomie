#include "supply.h"

Supply::Supply(QString* description, QString* recoilIntensity, int* recoilCount, QString* vibrationIntensity, int* vibrationCount)
{
    this->description = description;
    this->recoilCount = recoilCount;
    this->recoilIntensity = recoilIntensity;
    this->vibrationCount = vibrationCount;
    this->vibrationIntensity = vibrationIntensity;
}

Supply::~Supply(){

}
