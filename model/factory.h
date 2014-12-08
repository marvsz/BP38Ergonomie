#ifndef FACTORY_H
#define FACTORY_H

#include <QString>


class Factory
{
public:
    Factory(QString* factory, QString* street, QString* city, int* plz, QString* country, QString* contact, int* employees);
    ~Factory();

    void setFactory(QString* f);
    void setStreet(QString* s);
    void setCity(QString* cit);
    void setPlz(int* p);
    void setCountry(QString* cou);
    void setContact(QString* con);
    void setEmployees(int* e);

    QString getFactory();
    QString getStreet();
    QString getCity();
    int getPlz();
    QString setCountry();
    QString setContact();
    int getEmployees();

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
