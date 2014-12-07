#include "transportation.h"

int Transportation::idCounter = 0;

Transportation::Transportation(QString name, QVector<bool> opts, int weight, int maxLoad, QWidget *parent) :
    SelectableValueButton(idCounter++, 0, parent)
{
    this->setName(name);
    this->options = opts;
    this->weight = weight;
    this->maxLoad = maxLoad;
}

bool Transportation::getOption(int index)
{
    return this->options.at(index);
}

void Transportation::setOption(int index, bool b)
{
    this->options.replace(index, b);
}

void Transportation::setName(QString name)
{
    this->name = name;
    this->setText(name);
}

void Transportation::setWeight(int weight){
    this->weight = weight;
}

int Transportation::getWeight(){
    return this->weight;
}

void Transportation::setMaxLoad(int maxLoad){
    this->maxLoad = maxLoad;
}

int Transportation::getMaxLoad(){
    return this->maxLoad;
}
