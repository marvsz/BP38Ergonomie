#ifndef WORKPLACE_H
#define WORKPLACE_H

#include "textfield.h"
#include "line.h"
#include "shiftdata.h"
#include "workerdata.h"
#include "product.h"
#include "remarks.h"


class Workplace
{
public:
    Workplace(TextField* name, TextField* description, TextField* code, TextField* population, Line* line, ShiftData* shiftdata, WorkerData* workerdata, Product* product, Remarks* remarks);


private:
    TextField* name;
    TextField* description;
    TextField* code;
    TextField* population;
    Line* line;
    ShiftData* shiftdata;
    WorkerData* workerdata;
    Product* product;
    Remarks* remarks;
};

#endif // WORKPLACE_H
