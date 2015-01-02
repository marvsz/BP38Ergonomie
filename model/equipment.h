#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>

class Equipment
{
public:
    Equipment();
    Equipment(QString *name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity);

    int getID() const;

    QString* getName() const;
    void setName(QString* name);

    int getRecoilCount() const;
    void setRecoilCount(int count);

    int getRecoilIntensity () const;
    void setRecoilIntensity(int intensity);

    int getVibrationCount() const;
    void setVibrationCount(int count);

    int getVibrationIntensity() const;
    void setVibrationIntensity(int intensity);

private:
    int id;
    QString *name;
    int recoilCount;
    int recoilIntensity;
    int vibrationCount;
    int vibrationIntensity;
};

#endif // EQUIPMENT_H
