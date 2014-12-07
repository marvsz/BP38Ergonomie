#include "workerdata.h"

WorkerData::WorkerData(TextField* gender, NumberField* age, NumberField* height, TextField* remarks, NumberField* personalID)
{
    this->age=age;
    this->gender=gender;
    this->height=height;
    this->personalID=personalID;
    this->remarks=remarks;
}
