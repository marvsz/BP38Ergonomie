#ifndef WORKERDATA_H
#define WORKERDATA_H

#include <QString>

class WorkerData
{
public:
    WorkerData(QString* gender, int* age, int* height, QString* remarks, int* personalID);
    ~WorkerData();

    void setGender(QString* g);
    void setAge(int* a);
    void setHeight(int* h);
    void setRemarks(QString* r);
    void setPersonalId(int* p);

    QString* getGender();
    int* getAge();
    int* getHeight();
    QString* getRemarks();
    int* getPersonalId();

private:
    QString* gender;
    int* age;
    int* height;
    QString* remarks;
    int* personalID;
};

#endif // WORKERDATA_H
