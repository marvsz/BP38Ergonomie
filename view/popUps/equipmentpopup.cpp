#include "equipmentpopup.h"
#include <QGridLayout>
#include <QLabel>

EquipmentPopUp::EquipmentPopUp(QWidget *parent):
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Create Equipment"), parent),
    txtBxName(new TextLineEdit()),
    numBxRecoilCount(new NumberLineEdit()),
    numBxRecoilIntensity(new NumberLineEdit()),
    numBxVibrationCount(new NumberLineEdit()),
    numBxVibrationIntensity(new NumberLineEdit())
{
    txtBxName->setPlaceholderText(tr("Name"));
    numBxRecoilCount->setPlaceholderText(tr("Recoil count"));
    numBxRecoilIntensity->setPlaceholderText(tr("Recoil intensity"));
    numBxVibrationCount->setPlaceholderText(tr("Vibration count"));
    numBxVibrationIntensity->setPlaceholderText(tr("Vibration intensity"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel(tr("Name:")), 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxName, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Recoil count:")), 1, 0, 1, 1, 0);
    mainLayout->addWidget(numBxRecoilCount, 1, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Recoil intensity [N]:")), 2, 0, 1, 1, 0);
    mainLayout->addWidget(numBxRecoilIntensity, 2, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Vibration count:")), 3, 0, 1, 1, 0);
    mainLayout->addWidget(numBxVibrationCount, 3, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Vibration intensity [N]:")), 4, 0, 1, 1, 0);
    mainLayout->addWidget(numBxVibrationIntensity, 4, 1, 1, 1, 0);

    setLayout(mainLayout);
}

EquipmentPopUp::~EquipmentPopUp()
{

}

//PUBLIC SLOTS
void EquipmentPopUp::onEnter(){
    txtBxName->clear();
    numBxRecoilCount->clear();
    numBxRecoilIntensity->clear();
    numBxVibrationCount->clear();
    numBxVibrationIntensity->clear();
}

//GETTER
QString EquipmentPopUp::getName() const{
    return txtBxName->text();
}
int EquipmentPopUp::getRecoilCount() const{
    return numBxRecoilCount->getValue();
}
int EquipmentPopUp::getRecoilIntensity() const{
    return numBxRecoilIntensity->getValue();
}
int EquipmentPopUp::getVibrationCount() const{
    return numBxVibrationCount->getValue();
}
int EquipmentPopUp::getVibrationIntensity() const{
    return numBxVibrationIntensity->getValue();
}
