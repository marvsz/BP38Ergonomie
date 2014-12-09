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
    ~Workplace();

    void setName(QString* n);
    void setDescription(QString* d);
    void setCode(QString* c);
    void setPopulation(QString* p);
    void setLine(Line* l);
    void setShiftData(ShiftData* s);
    void setWorkerData(WorkerData* w);
    void setProduct(Product* p);
    void setRemarks(Remarks* r);

    QString* getName();
    QString* getDescription();
    QString* getCode();
    QString* getPopulation();
    Line* getLine();
    ShiftData* getShiftData();
    WorkerData* getWorkerData();
    Product* getProduct();
    Remarks* getRemarks();

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
