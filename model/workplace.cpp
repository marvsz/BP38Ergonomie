#include "workplace.h"

Workplace::Workplace(QString* name, QString* description, QString* code, QString* population, Line* line, ShiftData* shiftdata, WorkerData* workerdata, Product* product, Remarks* remarks)
{
    this->code=code;
    this->description=description;
    this->line=line;
    this->name=name;
    this->population=population;
    this->product=product;
    this->remarks=remarks;
    this->shiftdata=shiftdata;
    this->workerdata=workerdata;
}
