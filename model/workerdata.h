#ifndef WORKERDATA_H
#define WORKERDATA_H

#import "textfield.h"
#import "numberfield.h"
#import "boolbutton.h"

class WorkerData
{
public:
    WorkerData(TextField* gender, NumberField* age, NumberField* height, TextField* remarks, NumberField* personalID);
    ~WorkerData();

private:
    TextField* gender;
    NumberField* age;
    NumberField* height;
    TextField* remarks;
    NumberField* personalID;
};

#endif // WORKERDATA_H
