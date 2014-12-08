#include "general.h"

General::General(QString* description, QString* mtmCode, QString* activity, QString* subActivity, Product* product, int* workingHeight, int* distance, QString* gripType, QString* momentumIntensity, int* momentumCount)
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
