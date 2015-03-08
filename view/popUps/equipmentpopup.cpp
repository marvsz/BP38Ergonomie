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
    connect(this, SIGNAL(closePopUp()), this, SLOT(onClose()));
    connect(this, SIGNAL(confirm()), this, SLOT(onConfirm()));

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

//PRIVATE SLOTS
void EquipmentPopUp::onConfirm(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_EQUIPMENT_NAME, txtBxName->text());
    values.insert(DBConstants::COL_EQUIPMENT_RECOIL_COUNT, numBxRecoilCount->getValue());
    values.insert(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY, numBxRecoilIntensity->getValue());
    values.insert(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT, numBxVibrationCount->getValue());
    values.insert(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY, numBxVibrationIntensity->getValue());
    emit saveEquipment(values);
    emit closePopUp();
}

void EquipmentPopUp::onClose(){
    txtBxName->clear();
    numBxRecoilCount->clear();
    numBxRecoilIntensity->clear();
    numBxVibrationCount->clear();
    numBxVibrationIntensity->clear();
}
