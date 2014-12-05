#ifndef FACTORY_H
#define FACTORY_H

#include "textfield.h"
#include "numberfield.h"

class Factory
{
public:
    Factory(TextField* factory, TextField* street, TextField* city, NumberField* plz, TextField* country, TextField* contact, NumberField* employees);
    ~Factory();

private:
    TextField* factory;
    TextField* street;
    TextField* city;
    NumberField* plz;
    TextField* country;
    TextField* contact;
    NumberField* employees;
};

#endif // FACTORY_H
