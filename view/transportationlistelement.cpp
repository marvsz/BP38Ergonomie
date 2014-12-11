#include "transportationlistelement.h"

int TransportationListElement::idCounter = 0;

TransportationListElement::TransportationListElement(QString name, QVector<bool> opts, int weight, int maxLoad, QWidget *parent) :
    SelectableValueButton(idCounter++, 0, parent)
{
    this->setName(name);
    this->options = opts;
    this->weight = weight;
    this->maxLoad = maxLoad;
}

bool TransportationListElement::getOption(int index)
{
    return this->options.at(index);
}

void TransportationListElement::setOption(int index, bool b)
{
    this->options.replace(index, b);
}

void TransportationListElement::setName(QString name)
{
    this->name = name;
    this->setText(name);
}

void TransportationListElement::setWeight(int weight){
    this->weight = weight;
}

int TransportationListElement::getWeight(){
    return this->weight;
}

void TransportationListElement::setMaxLoad(int maxLoad){
    this->maxLoad = maxLoad;
}

int TransportationListElement::getMaxLoad(){
    return this->maxLoad;
}
