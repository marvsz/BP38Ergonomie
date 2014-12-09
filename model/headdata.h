#ifndef HEADDATA_H
#define HEADDATA_H

#include <QDate>
#include "factory.h"
#include "company.h"
#include "analyst.h"

class HeadData
{
public:
    HeadData(Analyst* analyst, Factory* factory, Company* company, QDate* begin, QDate* end);
    ~HeadData();

    void setAnalyst(Analyst* a);
    void setFacotry(Factory* f);
    void setCompany(Company* c);
    void setBegin(QDate* b);
    void setEnd(QDate* e);

    Analyst* getAnalyst();
    Factory* getFactory();
    Company* getCompany();
    QDate* getBegin();
    QDate* getEnd();

private:
    Analyst* analyst;
    Factory* factory;
    Company* company;
    QDate* begin;
    QDate* end;
};

#endif // HEADDATA_H
