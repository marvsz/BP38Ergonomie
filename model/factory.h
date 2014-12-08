#ifndef FACTORY_H
#define FACTORY_H

#include <QString>


class Factory
{
public:
    Factory(QString* factory, QString* street, QString* city, int* plz, QString* country, QString* contact, int* employees);
    ~Factory();

private:
    QString* factory;
    QString* street;
    QString* city;
    int* plz;
    QString* country;
    QString* contact;
    int* employees;
};

#endif // FACTORY_H
