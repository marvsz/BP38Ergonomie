#include "utilitylistcontrol.h"
#include <QLabel>
#include "separator.h"
/**
 * @brief Constructs a TransportationListControl widget which is a child of parent.
 * The values for recoil and vibration are set to the default values 0.
 * The default selection is none.
 * @param name A QString describing the header of the list.
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
UtilityListControl::UtilityListControl(QWidget *parent) :
    QWidget(parent)
{
    mainLayout = new QGridLayout;
    listLayout = new QVBoxLayout;
    optionLayout = new QGridLayout;

    // INITIALIZE VARIABLES
    this->utilites = new QList<UtilityListElement*>;

    this->currentUtilityId = -1;
    this->currentName = "";
    this->currentRecoilCount = 0;
    this->currentRecoilIntensity = 0;
    this->currentVibrationCount = 0;
    this->currentVibrationIntensity = 0;

    // BUTTONS
    this->addBtn = new SelectableValueButton(-1, 0, this);
    this->addBtn->setText("Betriebsmittel hinzufügen");
    this->addBtn->setMinimumWidth(250);
    connect(this->addBtn, SIGNAL(clicked()), this, SLOT(addUtility()));
    this->remBtn = new SelectableValueButton(-2, 0, this);
    this->remBtn->setText("Betriebsmittel entfernen");
    this->remBtn->setMinimumWidth(250);
    connect(this->remBtn, SIGNAL(pressedWithID(int)), this, SLOT(removeUtility()));

    // OPTIONS
    this->utilityName = new UtilityOption(TEXT_OPTION, this);
    this->utilityName->setMinimumSize(350, 40);
    this->utilityName->setPlaceholder("Bezeichnung des Betriebsmittels");
    connect(this->utilityName, SIGNAL(valueChanged(QString)), this, SLOT(disableSelection()));

    this->recoilIntensity = new UtilityOption(VALUE_OPTION, this);
    this->recoilIntensity->setPlaceholder("Rückschlagintensität");
    this->recoilIntensity->setMinimumWidth(500);
    connect(this->recoilIntensity, SIGNAL(valueChanged(int)), this, SLOT(recoilIntensityChanged(int)));


    this->recoilCount = new UtilityOption(VALUE_OPTION, this);
    this->recoilCount->setPlaceholder("Rückschlaganzahl");
    this->recoilCount->setMinimumWidth(500);
    connect(this->recoilCount, SIGNAL(valueChanged(int)), this, SLOT(recoilCountChanged(int)));

    this->vibrationIntensity = new UtilityOption(VALUE_OPTION, this);
    this->vibrationIntensity->setPlaceholder("Vibrationsintensität");
    this->vibrationIntensity->setMinimumWidth(500);
    connect(this->vibrationIntensity, SIGNAL(valueChanged(int)), this, SLOT(vibrationIntensityChanged(int)));

    this->vibrationCount = new UtilityOption(VALUE_OPTION, this);
    this->vibrationCount->setPlaceholder("Vibrationsanzahl");
    this->vibrationCount->setMinimumWidth(500);
    connect(this->vibrationCount, SIGNAL(valueChanged(int)), this, SLOT(vibrationCountChanged(int)));

    // OPTION LAYOUT
    optionLayout->addWidget(new QLabel("Rückschlagintensität: [N]", this), 0, 0, 1, 1, Qt::AlignLeft);
    optionLayout->addWidget(this->recoilIntensity, 0, 1, 1, 1, Qt::AlignLeft);
    optionLayout->addWidget(new QLabel("Rückschlaganzahl:", this), 1, 0, 1, 1, Qt::AlignLeft);
    optionLayout->addWidget(this->recoilCount, 1, 1, 1, 1, Qt::AlignLeft);
    optionLayout->addWidget(new QLabel("Vibrationsintensität [N]:", this), 2, 0, 1, 1, Qt::AlignLeft);
    optionLayout->addWidget(this->vibrationIntensity, 2, 1, 1, 1, Qt::AlignLeft);
    optionLayout->addWidget(new QLabel("Vibrationsanzahl:", this), 3, 0, 1, 1, Qt::AlignLeft);
    optionLayout->addWidget(this->vibrationCount, 3, 1, 1, 1, Qt::AlignLeft);

    // MAIN LAYOUT
    mainLayout->addWidget(new QLabel("Betriebsmittel"), 0, 0, 1, 3, Qt::AlignCenter);
    mainLayout->addLayout(listLayout, 1, 0, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(new QLabel("Bezeichnung:"), 2, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(utilityName, 2, 0, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(addBtn, 3, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(remBtn, 3, 2, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 4, 0, 1, 3);
    mainLayout->addLayout(optionLayout, 5, 0, 1, 3, Qt::AlignLeft);
    this->setLayout(mainLayout);
}

// private slots
/**
 * @brief A slot that is called to change the current selected utility.
 * If the id is valid (> -1), the before selected utility is unselected and the
 * newly selected utility is set selected. The currentUtilityId is set
 * to the id of the newly selected UtilityListElement.
 * @param id The id of the newly selected UtilityListElement
 */
void UtilityListControl::setCurrentUtilityId(int id){
    if(currentUtilityId > -1 && utilityWithId(currentUtilityId) != NULL)
        utilityWithId(currentUtilityId)->setSelected(false);
    currentUtilityId = id;
    if(currentUtilityId > -1  && utilityWithId(currentUtilityId) != NULL)
        utilityWithId(currentUtilityId)->setSelected(true);
}

/**
 * @brief A slot that is called to add a UtilityListElement to the
 * list of utilities. The UtilityListElement is initialized with
 * the current selected values, the default values are 0.
 * The textfield for entering a new name is cleared and all selections are disabled
 * after adding the UtilityListElement.
 */
void UtilityListControl::addUtility(){
    if(utilityName->getTextValue() != ""){
        UtilityListElement* u = new UtilityListElement(utilityName->getTextValue(), recoilIntensity->getIntValue(), recoilCount->getIntValue(), vibrationIntensity->getIntValue(), vibrationCount->getIntValue(), this);
        u->setMinimumSize(300, 50);
        u->setMaximumSize(300, 50);
        utilites->append(u);
        connect(u, SIGNAL(pressedWithID(int)), this, SLOT(utilityChanged(int)));
        this->listLayout->addWidget(u);

        disableSelection();
        clearValues();
    }
}

/**
 * @brief A slot that is called to remove a UtilityListElement from the
 * list of utilities. The UtilityListElement is removed from the list
 * and all values are reset to default values (0).
 * All selections are disabled.
 */
void UtilityListControl::removeUtility(){
    if(!utilites->isEmpty() && currentUtilityId > -1){
        int indexToRemove = utilityIndex(currentUtilityId);
        delete utilityWithId(currentUtilityId);
        utilites->removeAt(indexToRemove);
    }

    setCurrentUtilityId(-1);
    clearValues();
}

/**
 * @brief A slot that is called when the selected utility changed.
 * The slot handles the displaying of the correct values for the selected
 * UtilityListElement (recoil and vibration)
 * @param id The id of the UtilityListElement selected.
 */
void UtilityListControl::utilityChanged(int id){
    setCurrentUtilityId(id);
    UtilityListElement* u = utilityWithId(currentUtilityId);

    recoilIntensity->setValue(u->getRecoilIntensity());
    recoilCount->setValue(u->getRecoilCount());
    vibrationIntensity->setValue(u->getVibrationIntensity());
    vibrationCount->setValue(u->getVibrationCount());

}

/**
 * @brief A slot that is called to unselect all buttons and set the values of
 * all currently saved values to default (0).
 * The currentUtilityId is set to  -1 (no Utility selected).
 */
void UtilityListControl::disableSelection(){
    if(currentUtilityId > -1 && !utilites->isEmpty() && utilityName->getTextValue() != ""){
        utilityWithId(currentUtilityId)->setSelected(false);
        currentUtilityId = -1;
        clearValues();
    }
}

/**
 * @brief A slot that is called when the recoil intensity changed. The
 * current recoil intensity is set to the rI value. The utility with the
 * current selected id is then set to this recoil intensity, if the index is valid (> -1)
 * @param rI The value of the changed recoil intensity
 */
void UtilityListControl::recoilIntensityChanged(int rI){
    currentRecoilIntensity = rI;
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setRecoilIntensity(rI);
}

/**
 * @brief A slot that is called when the recoil count changed. The
 * current recoil count is set to the rC value. The utility with the
 * current selected id is then set to this recoil count, if the index is valid (> -1)
 * @param rC The value of the changed recoil count
 */
void UtilityListControl::recoilCountChanged(int rC){
    currentRecoilIntensity = rC;
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setRecoilCount(rC);
}

/**
 * @brief A slot that is called when the vibration intensity changed. The
 * current vibration intensity is set to the vI value. The utility with the
 * current selected id is then set to this vibration intensity, if the index is valid (> -1)
 * @param vI The value of the changed vibration intensity.
 */
void UtilityListControl::vibrationIntensityChanged(int vI){
    currentVibrationIntensity = vI;
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setVibrationIntensity(vI);
}

/**
 * @brief A slot that is called when the vibration count changed. The
 * current vibration count is set to the vC value. The utility with the
 * current selected id is then set to this vibration count, if the index is valid (> -1)
 * @param vI The value of the changed vibration count.
 */
void UtilityListControl::vibrationCountChanged(int vC){
    currentVibrationIntensity = vC;
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setVibrationCount(vC);
}

// private
/**
 * @brief A function to find the UtilityListElement with a certain id
 * in the list of known utilities.
 * @param id The id of the desired UtilityListElement.
 * @return A pointer to the UtilityListElement with the id. NULL, if
 * the UtilityListElement is not in the list.
 */
UtilityListElement* UtilityListControl::utilityWithId(int id){
    for(int i = 0; i < utilites->length(); i++)
        if(utilites->at(i)->getID() == id)
            return utilites->at(i);
    return NULL;
}

/**
 * @brief A function to find the index of a UtilityListElement in the list
 * of known utilities.
 * @param utilityId The id of the UtilityListElement.
 * @return The index in the list of utilities, -1 (invalid index),
 * if the UtilityListElement is not in the list.
 */
int UtilityListControl::utilityIndex(int utilityId){
    for(int i = 0; i < utilites->length(); i++)
        if(utilites->at(i)->getID() == utilityId)
            return i;
    return -1;
}

/**
 * @brief A function to clear all textfields of the UtilityListControl.
 * The saved values are set to the default values (0), the name field is set to an empty QString.
 */
void UtilityListControl::clearValues(){
    this->utilityName->clear();
    this->currentName = "";
    this->recoilCount->clear();
    this->currentRecoilCount = 0;
    this->recoilIntensity->clear();
    this->currentRecoilIntensity = 0;
    this->vibrationCount->clear();
    this->currentVibrationCount = 0;
    this->vibrationIntensity->clear();
    this->currentVibrationIntensity = 0;
}
