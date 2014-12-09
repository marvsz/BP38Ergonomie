#include "factory.h"

Factory::Factory(QString* factory, QString* street, QString* city, int* plz, QString* country, QString* contact, int* employees)
{
    this->setCity(city);
    this->setContact(contact);
    this->setCountry(country);
    this->setEmployees(employees);
    this->setFactory(factory);
    this->setPlz(plz);
    this->setStreet(street);
}

Factory::~Factory(){

}

QString* Factory::getCity(){
    return this->city;
}

int* Factory::getEmployees(){
    return this->employees;
}

QString* Factory::getFactory(){
    return this->factory;
}

int* Factory::getPlz(){
    return this->plz;
}

QString* Factory::getStreet(){
    return this->street;
}

QString* Factory::getContact(){
    return this->contact;
}

QString* Factory::getCountry(){
    return this->country;
}

void Factory::setCity(QString *cit){
    this->city=cit;
}

void Factory::setContact(QString *con){
    this->contact=con;
}

void Factory::setCountry(QString *cou){
    this->country=cou;
}

void Factory::setEmployees(int *e){
    this->employees=e;
}

void Factory::setFactory(QString *f){
    this->factory=f;
}

void Factory::setPlz(int *p){
    this->plz=p;
}

void Factory::setStreet(QString *s){
    this->street=s;
}
