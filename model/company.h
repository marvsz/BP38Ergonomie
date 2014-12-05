#ifndef COMPANY_H
#define COMPANY_H

#include "textfield.h"

class Company
{
public:
    Company(TextField* name);
    ~Company();

private:
    TextField* name;
};

#endif // COMPANY_H
