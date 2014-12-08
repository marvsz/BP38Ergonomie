#include "workerdata.h"

WorkerData::WorkerData(QString* gender, int* age, int* height, QString* remarks, int* personalID)
{
    this->age=age;
    this->gender=gender;
    this->height=height;
    this->personalID=personalID;
    this->remarks=remarks;
}
