#ifndef REMARKS_H
#define REMARKS_H

#include <QString>

class Remarks
{
public:
    Remarks(QString* problemId, QString* problemDescription, QString* sanctionId, QString* sanctionDescription, QString* factoryPerception);
    ~Remarks();

private:
    QString* problemId;
    QString* problemDescription;
    QString* sanctionId;
    QString* sanctionDescription;
    QString* factoryPerception;
};


#endif // REMARKS_H
