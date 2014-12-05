#ifndef ANALYST_H
#define ANALYST_H

#include "textfield.h"

class Analyst
{
public:
    Analyst(TextField* lastName, TextField* firstName, TextField* employer, TextField* experience);
    ~Analyst();

private:
    TextField* lastName;
    TextField* firstName;
    TextField* employer;
    TextField* experience;
};

#endif // ANALYST_H
