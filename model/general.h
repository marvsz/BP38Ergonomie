#ifndef GENERAL_H
#define GENERAL_H

#include "textfield.h"
#include "numberfield.h"
#include "product.h"

class General
{
public:
    General(TextField* description, TextField* mtmCode, TextField* activity, TextField* subActivity, Product* product, NumberField* workingHeight, NumberField* distance, TextField* gripType, TextField* momentumIntensity, NumberField* momentumCount);
    ~General();

private:
    TextField* description;
    TextField* mtmCode;
    TextField* activity;
    TextField* subActivity;
    Product* product;
    NumberField* workingHeight;
    NumberField* distance;
    TextField* gripType;
    TextField* momentumIntensity;
    NumberField* momentumCount;
};

#endif // GENERAL_H
