#ifndef GENERAL_H
#define GENERAL_H

#include <QString>
#include "product.h"

class General
{
public:
    General(QString* description, QString* mtmCode, QString* activity, QString* subActivity, Product* product, int* workingHeight, int* distance, QString* gripType, QString* momentumIntensity, int* momentumCount);
    ~General();

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
