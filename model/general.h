#ifndef GENERAL_H
#define GENERAL_H

#include <QString>
#include "product.h"

class General
{
public:
    General(QString* description, QString* mtmCode, QString* activity, QString* subActivity, Product* product, int* workingHeight, int* distance, QString* gripType, QString* momentumIntensity, int* momentumCount);
    ~General();

    void setDescription(QString* de);
    void setMtmCode(QString* m);
    void setActivity(QString* a);
    void setSubActivity(QString* s);
    void setProduct(Product* p);
    void setWorkingHeight(int* w);
    void setDistance(int* di);
    void setGripType(QString* g);
    void setMomentumIntensity(QString* mi);
    void setMomentumCount(QString* mc);

    QString getDescription();
    QString getMtmCode();
    QString getActivity();
    QString getSubActivity();
    int getWorkingHeight();
    int getDistance();
    QString getGripType();
    QString getMomentumIntensity();


private:
    QString* description;
    QString* mtmCode;
    QString* activity;
    QString* subActivity;
    Product* product;
    int* workingHeight;
    int* distance;
    QString* gripType;
    QString* momentumIntensity;
    int* momentumCount;
};

#endif // GENERAL_H
