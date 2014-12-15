#include "transportationlistelement.h"

/**
 * @brief The id counter for providing unique ids for different TransportationListElement.
 * The idCounter starts with 0 and increases its value after creating a new TransportationListElement.
 */
int TransportationListElement::idCounter = 0;

/**
 * @brief Constructs a new TransportationListElement
 * @param name The name of the TransportationListElement to display.
 * @param opts The initial options of the TransportationListElement.
 * @param weight The initial weight of the TransportationListElement.
 * @param maxLoad the initial max load of the TransportationListElement.
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
TransportationListElement::TransportationListElement(QString name, QVector<bool> opts, int weight, int maxLoad, QWidget *parent) :
    SelectableValueButton(idCounter++, 0, parent)
{
    this->setName(name);
    this->options = opts;
    this->weight = weight;
    this->maxLoad = maxLoad;
}

/**
 * @brief Getter for a certain option of a TransportationListElement
 * @param index The index of the desired option.
 * @return The value of the desired option, either true or false.
 */
bool TransportationListElement::getOption(int index)
{
    return this->options.at(index);
}

/**
 * @brief Setter for a certain option of a TransportationListElement.
 * @param index The index of the option to be changed.
 * @param b The new value of the desired option, either true or false.
 */
void TransportationListElement::setOption(int index, bool b)
{
    this->options.replace(index, b);
}

/**
 * @brief Sets a new name of a TransportationListElement.
 * The name is displayed on the button and saved internally.
 * @param name The new name of the TransportationListElement.
 */
void TransportationListElement::setName(QString name)
{
    this->name = name;
    this->setText(name);
}

/**
 * @brief Sets the weight of a TransportationListElement to a new value.
 * @param weight The new value of the weight.
 */
void TransportationListElement::setWeight(int weight){
    this->weight = weight;
}

/**
 * @brief Getter for the weight of a TransportationListElement.
 * @return The weight stored for the TransportationListElement.
 */
int TransportationListElement::getWeight(){
    return this->weight;
}

/**
 * @brief Sets the max load of a TransportationListElement to a new value.
 * @param maxLoad The new value of the max load.
 */
void TransportationListElement::setMaxLoad(int maxLoad){
    this->maxLoad = maxLoad;
}

/**
 * @brief Getter for the max load of a TransportationListElement.
 * @return The max load stored for the TransportationListElement.
 */
int TransportationListElement::getMaxLoad(){
    return this->maxLoad;
}
