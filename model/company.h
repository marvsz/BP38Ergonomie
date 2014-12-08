#ifndef COMPANY_H
#define COMPANY_H

#include <QString>

class Company
{
public:
    Company(QString* name);
    ~Company();

private:
    QString* name;

};

#endif // COMPANY_H
