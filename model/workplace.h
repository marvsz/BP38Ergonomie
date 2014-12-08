#ifndef WORKPLACE_H
#define WORKPLACE_H

#include "line.h"
#include "shiftdata.h"
#include "workerdata.h"
#include "product.h"
#include "remarks.h"


class Workplace
{
public:
    Workplace(QString* name, QString* description, QString* code, QString* population, Line* line, ShiftData* shiftdata, WorkerData* workerdata, Product* product, Remarks* remarks);


private:
    QString* name;
    QString* description;
    QString* code;
    QString* population;
    Line* line;
    ShiftData* shiftdata;
    WorkerData* workerdata;
    Product* product;
    Remarks* remarks;
};

#endif // WORKPLACE_H
