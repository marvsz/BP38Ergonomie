#include "utilitylistelement.h"

int UtilityListElement::idCounter = 0;

UtilityListElement::UtilityListElement(QString name, int recoilIntensity, int recoilCount, int vibrationIntensity, int vibrationCount, QWidget* parent):
    SelectableValueButton(idCounter++, 0, parent)
{
    this->setName(name);
    this->recoilIntensity = recoilIntensity;
    this->recoilCount = recoilCount;
    this->vibrationIntensity = vibrationIntensity;
    this->vibrationCount = vibrationCount;
}

QString UtilityListElement::getName(){
    return this->name;
}

int UtilityListElement::getRecoilIntensity(){
    return this->recoilIntensity;
}

int UtilityListElement::getRecoilCount(){
    return this->recoilCount;
}

int UtilityListElement::getVibrationIntensity(){
    return this->vibrationIntensity;
}

int UtilityListElement::getVibrationCount(){
    return this->vibrationCount;
}

void UtilityListElement::setName(QString name){
    this->name = name;
    this->setText(name);
}

void UtilityListElement::setRecoilIntensity(int intensity){
    this->recoilIntensity = intensity;
}

void UtilityListElement::setRecoilCount(int count){
    this->recoilCount = count;
}

void UtilityListElement::setVibrationIntensity(int intensity){
    this->vibrationIntensity = intensity;
}

void UtilityListElement::setVibrationCount(int count){
    this->vibrationCount = count;
}
