#include "subvariant.h"

SubVariant::SubVariant(QString *desc, int min, int max, QVector<int> *btnValues, QString* iconPath)
{
    this->desc = desc;
    this->min = min;
    this->max = max;
    this->btnValues = btnValues;
    this->controlType = VALUE_CONTROL;
    this->iconPath = iconPath;
}

SubVariant::SubVariant(QString *desc, QVector<QString*> *btnTexts, QString* iconPath){
    this->desc = desc;
    this->btnTexts = btnTexts;
    this->iconPath = iconPath;
    this->controlType = TEXT_CONTROL;
}

SubVariant::~SubVariant(){

}

QString* SubVariant::getDescription() const{
    return this->desc;
}

int SubVariant::getMin() const{
    if(controlType == VALUE_CONTROL)
        return this->min;
    return 0;
}

int SubVariant::getMax() const{
    if(controlType == VALUE_CONTROL)
        return this->max;
    return 0;
}

QVector<int> *SubVariant::getBtnValues() const{
    if(controlType == VALUE_CONTROL)
        return this->btnValues;
    return NULL;
}

QVector<QString*> *SubVariant::getBtnTexts() const{
    if(controlType == TEXT_CONTROL)
        return this->btnTexts;
    return NULL;
}

VariantControl SubVariant::getControlType() const{
    return this->controlType;
}

QString* SubVariant::getIconPath() const {
    return this->iconPath;
}
