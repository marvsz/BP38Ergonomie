#include "subvariant.h"

SubVariant::SubVariant(QString *desc, int min, int max, QVector<int> *btnValues, QString* iconPath, VariantControl controlType)
{
    this->desc = desc;
    this->min = min;
    this->max = max;
    this->btnValues = btnValues;
    this->controlType = controlType;
    this->iconPath = iconPath;
}

SubVariant::~SubVariant(){

}

QString* SubVariant::getDescription() const{
    return this->desc;
}
int SubVariant::getMin() const{
    return this->min;
}
int SubVariant::getMax() const{
    return this->max;
}
QVector<int> *SubVariant::getBtnValues() const{
    return this->btnValues;
}
VariantControl SubVariant::getControlType() const{
    return this->controlType;
}
QString* SubVariant::getIconPath() const {
    return this->iconPath;
}
