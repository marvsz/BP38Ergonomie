#ifndef SUPPLY_H
#define SUPPLY_H

#include <QString>

class Supply
{
public:
    Supply(QString* description, QString* recoilIntensity, int* recoilCount, QString* vibrationIntensity, int* vibrationCount);
    ~Supply();

    void setDescription(QString* d);
    void setRecoilIntensity(QString* ri);
    void setRecoilCount(int* rc);
    void setViprationIntensity(QString* vi);
    void setVibrationCount(int* vc);

    QString* getDescription();
    QString* getRecoilIntensity();
    int* getRecoilCount();
    QString* getVibrationIntensity();
    int* getVibrationCount();

private:
    QString* description;
    QString* recoilIntensity;
    int* recoilCount;
    QString* vibrationIntensity;
    int* vibrationCount;
};

#endif // SUPPLY_H
