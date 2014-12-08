#ifndef ANALYST_H
#define ANALYST_H

#include <QString>

class Analyst
{
public:
    Analyst(QString* lastName, QString* firstName, QString* employer, QString* experience);
    ~Analyst();

    void setLastName(QString* lN);
    void setFirstName(QString* fN);
    void setEmployer(QString* em);
    void setExperience(QString* ex);

    QString* getLastName();
    QString* getFirstName();
    QString* getEmployer();
    QString* getExperience();

private:
    QString* lastName;
    QString* firstName;
    QString* employer;
    QString* experience;
};

#endif // ANALYST_H
