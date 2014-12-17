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
    optionLayout = new QFormLayout;
    buttonLayout = new QHBoxLayout;

    // INITIALIZE VARIABLES
    this->utilites = new QList<UtilityListElement*>;

    this->currentUtilityId = -1;
    this->currentName = "";
    this->currentRecoilCount = 0;
    this->currentRecoilIntensity = 0;
    this->currentVibrationCount = 0;
    this->currentVibrationIntensity = 0;

    // BUTTONS
    this->addBtn = new QPushButton(this);
    this->addBtn->setText("Betriebsmittel hinzufügen");
    this->addBtn->setMaximumWidth(300);
    connect(this->addBtn, SIGNAL(clicked()), this, SLOT(addUtility()));

    this->remBtn = new QPushButton(this);
    this->remBtn->setText("Betriebsmittel entfernen");
    this->remBtn->setMaximumWidth(300);
    connect(this->remBtn, SIGNAL(clicked()), this, SLOT(removeUtility()));

    // OPTIONS
    this->utilityName = new QLineEdit(this);
    this->utilityName->setPlaceholderText("Neues Betriebsmittel");
    this->utilityName->setMinimumWidth(300);
    connect(this->utilityName, SIGNAL(textChanged(QString)), this, SLOT(disableSelection()));

    this->recoilIntensity = new NumberLineEdit(this);
    this->recoilIntensity->setPlaceholderText("Rückschlagintensität");
    connect(this->recoilIntensity, SIGNAL(textChanged(QString)), this, SLOT(recoilIntensityChanged(QString)));

    this->recoilCount = new NumberLineEdit(this);
    this->recoilCount->setPlaceholderText("Rückschlaganzahl");
    connect(this->recoilCount, SIGNAL(textChanged(QString)), this, SLOT(recoilCountChanged(QString)));

    this->vibrationIntensity = new NumberLineEdit(this);
    this->vibrationIntensity->setPlaceholderText("Vibrationsintensität");
    connect(this->vibrationIntensity, SIGNAL(textChanged(QString)), this, SLOT(vibrationIntensityChanged(QString)));

    this->vibrationCount = new NumberLineEdit(this);
    this->vibrationCount->setPlaceholderText("Vibrationsanzahl");
    connect(this->vibrationCount, SIGNAL(textChanged(QString)), this, SLOT(vibrationCountChanged(QString)));

    // BUTTON LAYOUT
    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(remBtn);

    // OPTION LAYOUT
    optionLayout->addRow("Rückschlagintensität: [N]", this->recoilIntensity);
    optionLayout->addRow("Rückschlaganzahl:", this->recoilCount);
    optionLayout->addRow("Vibrationsintensität: [N]", this->vibrationIntensity);
    optionLayout->addRow("Vibrationsanzahl", this->vibrationCount);

    // MAIN LAYOUT
    mainLayout->addWidget(new QLabel("Betriebsmittel"), 0, 0, 1, 2, Qt::AlignLeft);
    mainLayout->addLayout(listLayout, 1, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 2, 0, 1, 2, 0);
    mainLayout->addWidget(new QLabel("Beschreibung:"), 3, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(utilityName, 3, 0, 1, 2, Qt::AlignHCenter);
    mainLayout->addLayout(buttonLayout, 4, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 5, 0, 1, 2, 0);
    mainLayout->addLayout(optionLayout, 6, 0, 1, 2, 0);
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
    if(utilityName->text() != ""){
        UtilityListElement* u = new UtilityListElement(utilityName->text(), recoilIntensity->text().toInt(), recoilCount->text().toInt(), vibrationIntensity->text().toInt(), vibrationCount->text().toInt(), this);
        u->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
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

    recoilIntensity->setText(QString::number(u->getRecoilIntensity()));
    recoilCount->setText(QString::number(u->getRecoilCount()));
    vibrationIntensity->setText(QString::number(u->getVibrationIntensity()));
    vibrationCount->setText(QString::number(u->getVibrationCount()));

}

/**
 * @brief A slot that is called to unselect all buttons and set the values of
 * all currently saved values to default (0).
 * The currentUtilityId is set to  -1 (no Utility selected).
 */
void UtilityListControl::disableSelection(){
    if(currentUtilityId > -1 && !utilites->isEmpty() && utilityName->text() != ""){
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
void UtilityListControl::recoilIntensityChanged(QString rI){
    currentRecoilIntensity = rI.toInt();
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setRecoilIntensity(currentRecoilIntensity);
}

/**
 * @brief A slot that is called when the recoil count changed. The
 * current recoil count is set to the rC value. The utility with the
 * current selected id is then set to this recoil count, if the index is valid (> -1)
 * @param rC The value of the changed recoil count
 */
void UtilityListControl::recoilCountChanged(QString rC){
    currentRecoilCount = rC.toInt();
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setRecoilCount(currentRecoilCount);
}

/**
 * @brief A slot that is called when the vibration intensity changed. The
 * current vibration intensity is set to the vI value. The utility with the
 * current selected id is then set to this vibration intensity, if the index is valid (> -1)
 * @param vI The value of the changed vibration intensity.
 */
void UtilityListControl::vibrationIntensityChanged(QString vI){
    currentVibrationIntensity = vI.toInt();
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setVibrationIntensity(currentVibrationIntensity);
}

/**
 * @brief A slot that is called when the vibration count changed. The
 * current vibration count is set to the vC value. The utility with the
 * current selected id is then set to this vibration count, if the index is valid (> -1)
 * @param vI The value of the changed vibration count.
 */
void UtilityListControl::vibrationCountChanged(QString vC){
    currentVibrationCount = vC.toInt();
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setVibrationCount(currentVibrationCount);
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
