#include "equipment.h"

Equipment::Equipment()
{
    id = -1;
    setName(new QString(""));
    setRecoilCount(-1);
    setRecoilIntensity(-1);
    setVibrationCount(-1);
    setVibrationIntensity(-1);
}


int Equipment::getID() const{
    return id;
}

QString* Equipment::getName() const{
    return name;
}
void Equipment::setName(QString* name){
    this->name = name;
}

int Equipment::getRecoilCount() const{
    return recoilCount;
}
void Equipment::setRecoilCount(int count){
    recoilCount = count;
}

int Equipment::getRecoilIntensity () const{
    return recoilIntensity;
}
void Equipment::setRecoilIntensity(int intensity){
    recoilIntensity = intensity;
}

int Equipment::getVibrationCount() const{
    return vibrationCount;
}
void Equipment::setVibrationCount(int count){
    vibrationCount = count;
}

int Equipment::getVibrationIntensity() const{
    return vibrationIntensity;
}
void Equipment::setVibrationIntensity(int intensity){
    vibrationIntensity = intensity;
}
