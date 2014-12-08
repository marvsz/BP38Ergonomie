#include "factory.h"

Factory::Factory(QString* factory, QString* street, QString* city, int* plz, QString* country, QString* contact, int* employees)
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
