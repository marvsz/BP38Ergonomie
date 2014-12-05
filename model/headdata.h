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

private:
    Analyst* analyst;
    Factory* factory;
    Company* company;
    QDate* begin;
    QDate* end;
};

#endif // HEADDATA_H
