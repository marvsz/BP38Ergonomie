#include "utilitylistelement.h"

/**
 * @brief The id counter for providing unique ids for different UtilityListElement.
 * The idCounter starts with 0 and increases its value after creating a new UtilityListElement.
 */
int UtilityListElement::idCounter = 0;

/**
 * @brief Constructs a new UtilityListElement.
 * @param name The name of the UtilityListElement to display.
 * @param recoilIntensity The initial recoil intensity.
 * @param recoilCount The initial recoil count.
 * @param vibrationIntensity The initial vibration intensity.
 * @param vibrationCount The initiaial vibration count.
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
UtilityListElement::UtilityListElement(QString name, int recoilIntensity, int recoilCount, int vibrationIntensity, int vibrationCount, QWidget* parent):
    SelectableValueButton(idCounter++, 0, parent)
{
    this->setName(name);
    this->recoilIntensity = recoilIntensity;
    this->recoilCount = recoilCount;
    this->vibrationIntensity = vibrationIntensity;
    this->vibrationCount = vibrationCount;
}

/**
 * @brief Getter for the name of a UtilityListElement.
 * @return The name as QString of the UtilityListElement.
 */
QString UtilityListElement::getName(){
    return this->name;
}

/**
 * @brief Getter for the recoil intensity of a UtilityListElement.
 * @return The value of the recoil intensity of the UtilityListElement.
 */
int UtilityListElement::getRecoilIntensity(){
    return this->recoilIntensity;
}

/**
 * @brief Getter for the recoil count of a UtilityListElement.
 * @return The value of the recoil count of the UtilityListElement.
 */

int UtilityListElement::getRecoilCount(){
    return this->recoilCount;
}

/**
 * @brief Getter for the vibration intensity of a UtilityListElement.
 * @return The value of the vibration intensity of the UtilityListElement.
 */

int UtilityListElement::getVibrationIntensity(){
    return this->vibrationIntensity;
}

/**
 * @brief Getter for the vibration count of a UtilityListElement.
 * @return The value of the virbation count of the UtilityListElement.
 */
int UtilityListElement::getVibrationCount(){
    return this->vibrationCount;
}

/**
 * @brief Sets a new name of a UtilityListElement.
 * The name is displayed on the button and saved internally.
 * @param name The new name of the UtilityListElement.
 */
void UtilityListElement::setName(QString name){
    this->name = name;
    this->setText(name);
}

/**
 * @brief Sets the recoil intensity of a UtilityListElement to a new value.
 * @param intensity The new value of the recoil intensity.
 */
void UtilityListElement::setRecoilIntensity(int intensity){
    this->recoilIntensity = intensity;
}

/**
 * @brief Sets the recoil count of a UtilityListElement to a new value.
 * @param count The new value of the recoil count.
 */
void UtilityListElement::setRecoilCount(int count){
    this->recoilCount = count;
}

/**
 * @brief Sets the vibration intensity of a UtilityListElement to a new value.
 * @param intensity The new value of the vibration intensity.
 */
void UtilityListElement::setVibrationIntensity(int intensity){
    this->vibrationIntensity = intensity;
}

/**
 * @brief Sets the vibration count of a UtilityListElement to a new value.
 * @param count The new value of the vibration count.
 */
void UtilityListElement::setVibrationCount(int count){
    this->vibrationCount = count;
}
