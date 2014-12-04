#include "general.h"

General::General(TextField* description, TextField* mtmCode, TextField* activity, TextField* subActivity, Product* product, NumberField* workingHeight, NumberField* distance, TextField* gripType, TextField* momentumIntensity, NumberField* momentumCount)
{
    this->activity=activity;
    this->description=description;
    this->distance=distance;
    this->gripType=gripType;
    this->momentumCount=momentumCount;
    this->momentumIntensity=momentumIntensity;
    this->mtmCode=mtmCode;
    this->product=product;
    this->subActivity=subActivity;
    this->workingHeight=workingHeight;
}

General::~General(){

}
