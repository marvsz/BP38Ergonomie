#include "subvariant.h"

SubVariant::SubVariant(QString *desc, int min, int max, const QVector<int> &btnValues, QString* iconPath) :
    btnValues(btnValues)
{
    this->desc = desc;
    this->min = min;
    this->max = max;
    this->controlType = VALUE_CONTROL;
    this->iconPath = iconPath;
}

SubVariant::SubVariant(QString *desc, const QVector<QString> &btnTexts, QString* iconPath):
    btnTexts(btnTexts)
{
    this->desc = desc;
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

const QVector<int> SubVariant::getBtnValues() const{
    return this->btnValues;
}

const QVector<QString> SubVariant::getBtnTexts() const{
    return this->btnTexts;
}

VariantControl SubVariant::getControlType() const{
    return this->controlType;
}

QString* SubVariant::getIconPath() const {
    return this->iconPath;
}
