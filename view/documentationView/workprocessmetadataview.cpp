#include "workprocessmetadataview.h"
#include <QGridLayout>
#include <QScrollArea>
#include <QVBoxLayout>
#include "../separator.h"
#include "../detailedlistitem.h"
#include "../flickcharm.h"


WorkProcessMetaDataView::WorkProcessMetaDataView(QWidget *parent) :
    TitledWidget(tr("Meta data"), parent),
    lblDescription(new QLabel(tr("Description:"))),
    lblWorkingHeight(new QLabel(tr("Working height [cm]:"))),
    lblDistance(new QLabel(tr("Distance [cm]:"))),
    lblImpulseIntensity(new QLabel(tr("Impulse intensity:"))),
    lblImpulseCount(new QLabel(tr("Impulse count:"))),
    lblEquipment(new QLabel(tr("Equipment:"))),
    btnEditEquipment(new QPushButton()),
    txtBxDescription(new TextLineEdit()),
    vcMTMCode(new ValueControl(TEXT)),
    numBxWorkingHeight(new NumberLineEdit()),
    numBxDistance(new NumberLineEdit()),
    oscImpulseIntensity(new OptionSelectionControl()),
    numBxImpulseCount(new NumberLineEdit()),
    equipmentListLayout(new QVBoxLayout),
    selectedEquipment_ID(0)
{
    txtBxDescription->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    txtBxDescription->setPlaceholderText(tr("Description of the working process"));
    numBxWorkingHeight->setPlaceholderText(tr("Working height of the process [cm]"));
    numBxDistance->setPlaceholderText(tr("Distance from produced product [cm]"));
    numBxImpulseCount->setPlaceholderText(tr("Count of impulses"));

    btnEditEquipment->setFixedSize(45, 45);
    btnEditEquipment->setObjectName("editIcon");

    oscImpulseIntensity->setValues(IMPULSE_INTENSITY_TEXTS, IMPULSE_INTENSITY_VALUES);

    vcMTMCode->setText(tr("MTM Code:"));
    vcMTMCode->setTextHint(tr("MTM Code of the process"));
    vcMTMCode->setValues(true, MTM_CODE_TEXTS, MTM_CODE_VALUES, QString(""));

    QWidget *equipmentList = new QWidget;
    equipmentList->setLayout(equipmentListLayout);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(lblDescription, 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxDescription, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3), 1, 0, 1, 2, 0);
    mainLayout->addWidget(vcMTMCode, 2, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3), 3, 0, 1, 2, 0);
    mainLayout->addWidget(lblWorkingHeight, 4, 0, 1, 1, 0);
    mainLayout->addWidget(numBxWorkingHeight, 4, 1, 1, 1, 0);
    mainLayout->addWidget(lblDistance, 5, 0, 1, 1, 0);
    mainLayout->addWidget(numBxDistance, 5, 1, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 6, 0, 1, 2, 0);
    mainLayout->addWidget(lblImpulseIntensity, 7, 0, 1, 1, 0);
    mainLayout->addWidget(oscImpulseIntensity, 7, 1, 1, 1, 0);
    mainLayout->addWidget(lblImpulseCount, 8, 0, 1, 1, 0);
    mainLayout->addWidget(numBxImpulseCount, 8, 1, 1, 1, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3), 9, 0, 1, 2, 0);
    mainLayout->addWidget(lblEquipment, 10, 0, 1, 1, 0);
    mainLayout->addWidget(equipmentList, 11, 0, 1, 3, 0);
    mainLayout->addWidget(btnEditEquipment, 12, 1, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 9, 0, 1, 2, 0);

    QWidget *mainContent = new QWidget();
    mainContent->setLayout(mainLayout);

    QScrollArea *saContent = new QScrollArea();
    saContent->setWidget(mainContent);
    saContent->setWidgetResizable(true);
    FlickCharm *flick = new FlickCharm();
    flick->activateOn(saContent);

    QVBoxLayout *wrapLayout = new QVBoxLayout;
    wrapLayout->addWidget(saContent);

    setLayout(wrapLayout);

    connect(btnEditEquipment, SIGNAL(clicked()), this, SLOT(btnEditEquipmentClicked()));
}

WorkProcessMetaDataView::~WorkProcessMetaDataView()
{

}
//PUBLIC SLOTS
void WorkProcessMetaDataView::setWorkProcessMetaData(const QString &desc, const QString &mtmCode, int workingHeight, int distance, int impulseIntensity, int impulseCount){
    txtBxDescription->setText(desc);
    vcMTMCode->setValue(mtmCode);
    numBxWorkingHeight->setValue(workingHeight);
    numBxDistance->setValue(distance);
    oscImpulseIntensity->setSelectedValue(impulseIntensity);
    numBxImpulseCount->setValue(impulseCount);
}

void WorkProcessMetaDataView::addEquipment(int id, const QString &name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity){
    DetailedListItem *newListItem = new DetailedListItem(0, "", name, equipmentItemScheme, false, true, false);
    newListItem->setID(id);
    QList<QStringList> values = QList<QStringList>() << (QStringList() << QString::number(recoilCount) << QString::number(recoilIntensity)) << (QStringList() << QString::number(vibrationCount) << QString::number(vibrationIntensity));
    newListItem->setValues(values);
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(dliEquipmentClicked(int)));
    connect(this, SIGNAL(selectEquipmentExclusive(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    equipmentListLayout->addWidget(newListItem);
}

void WorkProcessMetaDataView::clearEquipment(){
    QLayoutItem *item;
    while((item = equipmentListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void WorkProcessMetaDataView::setSelectedEquipment(int id){
    dliEquipmentClicked(id);
}

//PRIVATE SLOTS
void WorkProcessMetaDataView::dliEquipmentClicked(int id){
    selectedEquipment_ID = id;
    emit selectEquipmentExclusive(id);
}

void WorkProcessMetaDataView::btnEditEquipmentClicked(){
    emit showPopUp(PopUpType::EQUIPMENT_POPUP);
}

//GETTER
QString WorkProcessMetaDataView::getDescription() const{
    return txtBxDescription->text();
}
QString WorkProcessMetaDataView::getMTMCode() const{
    return vcMTMCode->getTextValue();
}
int WorkProcessMetaDataView::getWorkingHeight() const{
    return numBxWorkingHeight->getValue();
}
int WorkProcessMetaDataView::getDistance() const{
    return numBxDistance->getValue();
}
int WorkProcessMetaDataView::getImpulseIntensity() const{
    return oscImpulseIntensity->getSelectedValue().toInt();
}
int WorkProcessMetaDataView::getImpulseCount() const{
    return numBxImpulseCount->getValue();
}
int WorkProcessMetaDataView::getSelectedEquipment() const{
    return selectedEquipment_ID;
}

