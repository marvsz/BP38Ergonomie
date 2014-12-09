#ifndef COMPANY_H
#define COMPANY_H

#include <QString>

class Company
{
public:
    Company(QString* name);
    ~Company();

    void setName(QString* n);
    QString* getName();

private:
    QString* name;

};

#endif // COMPANY_H
