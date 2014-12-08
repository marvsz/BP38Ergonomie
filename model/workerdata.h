#ifndef WORKERDATA_H
#define WORKERDATA_H

#include <QString>

class WorkerData
{
public:
    WorkerData(QString* gender, int* age, int* height, QString* remarks, int* personalID);
    ~WorkerData();

private:
    QString* gender;
    int* age;
    int* height;
    QString* remarks;
    int* personalID;
};

#endif // WORKERDATA_H
