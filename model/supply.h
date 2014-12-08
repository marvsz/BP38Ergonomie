#ifndef SUPPLY_H
#define SUPPLY_H

#include <QString>

class Supply
{
public:
    Supply(QString* description, QString* recoilIntensity, int* recoilCount, QString* vibrationIntensity, int* vibrationCount);
    ~Supply();

private:
    QString* description;
    QString* recoilIntensity;
    int* recoilCount;
    QString* vibrationIntensity;
    int* vibrationCount;
};

#endif // SUPPLY_H
