#include "utilitylistcontrol.h"
#include <QLabel>
UtilityListControl::UtilityListControl(QString name, QWidget *parent) :
    QGroupBox(parent)
{
    mainLayout = new QVBoxLayout;
    listLayout = new QVBoxLayout;
    optionLayout = new QFormLayout;
    buttonLayout = new QHBoxLayout;

    this->nameLabel = new QLabel();
    this->nameLabel->setText(name);

    this->utilites = new QList<UtilityListElement*>;

    this->currentUtilityId = -1;
    this->currentName = "";
    this->currentRecoilCount = 0;
    this->currentRecoilIntensity = 0;
    this->currentVibrationCount = 0;
    this->currentVibrationIntensity = 0;

    this->addBtn = new SelectableValueButton(-1, 0, this);
    this->addBtn->setText("Betriebsmittel hinzufügen");
    connect(this->addBtn, SIGNAL(clicked()), this, SLOT(addUtility()));
    this->remBtn = new SelectableValueButton(-2, 0, this);
    this->remBtn->setText("Betriebsmittel entfernen");
    connect(this->remBtn, SIGNAL(pressedWithID(int)), this, SLOT(removeUtility()));

    listLayout->addWidget(nameLabel, 0, Qt::AlignCenter);
    buttonLayout->addWidget(addBtn, 0, Qt::AlignLeft);
    buttonLayout->addWidget(remBtn, 0, Qt::AlignRight);

    this->utilityName = new UtilityOption(new QString("Bezeichnung"), TEXT_OPTION, this);
    this->utilityName->setPlaceholder("Bezeichnung des Betriebsmittels");
    connect(this->utilityName, SIGNAL(valueChanged(QString)), this, SLOT(disableSelection()));

    this->recoilIntensity = new UtilityOption(new QString("Rückschlagintensität"), VALUE_OPTION, this);
    this->recoilIntensity->setPlaceholder("Rückschlagintensität");
    connect(this->recoilIntensity, SIGNAL(valueChanged(int)), this, SLOT(recoilIntensityChanged(int)));


    this->recoilCount = new UtilityOption(new QString("Rückschlaganzahl"), VALUE_OPTION, this);
    this->recoilCount->setPlaceholder("Rückschlaganzahl");
    connect(this->recoilCount, SIGNAL(valueChanged(int)), this, SLOT(recoilCountChanged(int)));

    this->vibrationIntensity = new UtilityOption(new QString("Vibrationsintensität"), VALUE_OPTION, this);
    this->vibrationIntensity->setPlaceholder("Vibrationsintensität");
    connect(this->vibrationIntensity, SIGNAL(valueChanged(int)), this, SLOT(vibrationIntensityChanged(int)));

    this->vibrationCount = new UtilityOption(new QString("Vibrationsanzahl"), VALUE_OPTION, this);
    this->vibrationCount->setPlaceholder("Vibrationsanzahl");
    connect(this->vibrationCount, SIGNAL(valueChanged(int)), this, SLOT(vibrationCountChanged(int)));

    optionLayout->addRow(this->recoilIntensity);
    optionLayout->addRow(this->recoilCount);
    optionLayout->addRow(this->vibrationIntensity);
    optionLayout->addRow(this->vibrationCount);

    mainLayout->addLayout(listLayout);
    mainLayout->addWidget(utilityName);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(optionLayout);
    this->setLayout(mainLayout);
}

// private slots
void UtilityListControl::setCurrentUtilityId(int id){
    if(currentUtilityId > -1 && utilityWithId(currentUtilityId) != NULL)
        utilityWithId(currentUtilityId)->setSelected(false);
    currentUtilityId = id;
    if(currentUtilityId > -1  && utilityWithId(currentUtilityId) != NULL)
        utilityWithId(currentUtilityId)->setSelected(true);
}

void UtilityListControl::addUtility(){
    if(utilityName->getTextValue() != ""){
        UtilityListElement* u = new UtilityListElement(utilityName->getTextValue(), recoilIntensity->getIntValue(), recoilCount->getIntValue(), vibrationIntensity->getIntValue(), vibrationCount->getIntValue(), this);
        u->setMinimumSize(100, 60);
        utilites->append(u);
        connect(u, SIGNAL(pressedWithID(int)), this, SLOT(utilityChanged(int)));
        this->listLayout->addWidget(u);

        disableSelection();
        clearValues();
    }
}

void UtilityListControl::removeUtility(){
    if(!utilites->isEmpty() && currentUtilityId > -1){
        int indexToRemove = utilityIndex(currentUtilityId);
        delete utilityWithId(currentUtilityId);
        utilites->removeAt(indexToRemove);
    }

    setCurrentUtilityId(-1);
    clearValues();
}

void UtilityListControl::utilityChanged(int id){
    setCurrentUtilityId(id);
    UtilityListElement* u = utilityWithId(currentUtilityId);

    recoilIntensity->setValue(u->getRecoilIntensity());
    recoilCount->setValue(u->getRecoilCount());
    vibrationIntensity->setValue(u->getVibrationIntensity());
    vibrationCount->setValue(u->getVibrationCount());

}

void UtilityListControl::disableSelection(){
    if(currentUtilityId > -1 && !utilites->isEmpty() && utilityName->getTextValue() != ""){
        utilityWithId(currentUtilityId)->setSelected(false);
        currentUtilityId = -1;
        clearValues();
    }
}

void UtilityListControl::recoilIntensityChanged(int rI){
    currentRecoilIntensity = rI;
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setRecoilIntensity(rI);
}

void UtilityListControl::recoilCountChanged(int rC){
    currentRecoilIntensity = rC;
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setRecoilCount(rC);
}

void UtilityListControl::vibrationIntensityChanged(int vI){
    currentVibrationIntensity = vI;
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setVibrationIntensity(vI);
}

void UtilityListControl::vibrationCountChanged(int vC){
    currentVibrationIntensity = vC;
    if(currentUtilityId > -1)
        utilityWithId(currentUtilityId)->setVibrationCount(vC);
}

// private
UtilityListElement* UtilityListControl::utilityWithId(int id){
    for(int i = 0; i < utilites->length(); i++)
        if(utilites->at(i)->getID() == id)
            return utilites->at(i);
    return NULL;
}

int UtilityListControl::utilityIndex(int utilityId){
    for(int i = 0; i < utilites->length(); i++)
        if(utilites->at(i)->getID() == utilityId)
            return i;
    return -1;
}

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
