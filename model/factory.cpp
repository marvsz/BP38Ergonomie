#include "factory.h"

Factory::Factory(TextField* factory, TextField* street, TextField* city, NumberField* plz, TextField* country, TextField* contact, NumberField* employees)
{
    this->city=city;
    this->contact=contact;
    this->country=country;
    this->employees=employees;
    this->factory=factory;
    this->plz=plz;
    this->street=street;
}

Factory::~Factory(){

}
