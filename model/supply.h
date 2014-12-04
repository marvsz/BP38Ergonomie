#ifndef SUPPLY_H
#define SUPPLY_H

#include "numberfield.h"
#include "textfield.h"

class Supply
{
public:
    Supply(TextField* description, TextField* recoilIntensity, NumberField* recoilCount, TextField* vibrationIntensity, NumberField* vibrationCount);
    ~Supply();

private:
    TextField* description;
    TextField* recoilIntensity;
    NumberField* recoilCount;
    TextField* vibrationIntensity;
    NumberField* vibrationCount;
};

#endif // SUPPLY_H
