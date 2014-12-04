#include "supply.h"

Supply::Supply(TextField* description, TextField* recoilIntensity, NumberField* recoilCount, TextField* vibrationIntensity, NumberField* vibrationCount)
{
    this->description = description;
    this->recoilCount = recoilCount;
    this->recoilIntensity = recoilIntensity;
    this->vibrationCount = vibrationCount;
    this->vibrationIntensity = vibrationIntensity;
}

Supply::~Supply(){

}
