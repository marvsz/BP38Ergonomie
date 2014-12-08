#ifndef ANALYST_H
#define ANALYST_H

#include <QString>

class Analyst
{
public:
    Analyst(QString* lastName, QString* firstName, QString* employer, QString* experience);
    ~Analyst();

private:
    QString* lastName;
    QString* firstName;
    QString* employer;
    QString* experience;
};

#endif // ANALYST_H
