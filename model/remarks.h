#ifndef REMARKS_H
#define REMARKS_H

#include <QString>

class Remarks
{
public:
    Remarks(QString* problemId, QString* problemDescription, QString* sanctionId, QString* sanctionDescription, QString* factoryPerception);
    ~Remarks();

    void setProblemId(QString* pi);
    void setProblemDescription(QString* pd);
    void setSanctionId(QString* si);
    void setSanctionDescription(QString* sd);
    void setFactoryPerception(QString* fp);

    QString getProblemId();
    QString getProblemDescription();
    QString getSanctionId();
    QString getSanctionDescription();
    QString getFactoryPerception();

private:
    QString* problemId;
    QString* problemDescription;
    QString* sanctionId;
    QString* sanctionDescription;
    QString* factoryPerception;
};


#endif // REMARKS_H
