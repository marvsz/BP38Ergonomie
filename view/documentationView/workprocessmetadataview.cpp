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
    btnCreateEquipment(new QPushButton()),
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

    btnCreateEquipment->setFixedSize(45, 45);
    btnCreateEquipment->setObjectName("editIcon");

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
    mainLayout->addWidget(btnCreateEquipment, 12, 1, 1, 1, 0);
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

    connect(btnCreateEquipment, SIGNAL(clicked()), this, SLOT(btnCreateEquipmentClicked()));
}

WorkProcessMetaDataView::~WorkProcessMetaDataView()
{

}
//PUBLIC SLOTS
void WorkProcessMetaDataView::setWorkProcess(QHash<QString, QVariant> values){
    txtBxDescription->setText(values.value(DBConstants::COL_WORK_PROCESS_DESCRIPTION).toString());
    vcMTMCode->setValue(values.value(DBConstants::COL_WORK_PROCESS_MTM_CODE).toString());
    numBxWorkingHeight->setValue(values.value(DBConstants::COL_WORK_PROCESS_WORKING_HEIGHT).toInt());
    numBxDistance->setValue(values.value(DBConstants::COL_WORK_PROCESS_DISTANCE).toInt());
    oscImpulseIntensity->setSelectedValue(values.value(DBConstants::COL_WORK_PROCESS_IMPULSE_INTENSITY).toInt());
    numBxImpulseCount->setValue(values.value(DBConstants::COL_WORK_PROCESS_IMPULSE_COUNT).toInt());
    dliEquipmentSelected(values.value(DBConstants::COL_WORK_PROCESS_EQUIPMENT_ID).toInt());
}

void WorkProcessMetaDataView::addEquipment(QHash<QString, QVariant> values){
    DetailedListItem *newListItem = new DetailedListItem(0, "equipmentIcon", values.value(DBConstants::COL_EQUIPMENT_NAME).toString(), equipmentItemScheme, false, true, false);
    newListItem->setID(values.value(DBConstants::COL_EQUIPMENT_ID).toInt());
    QList<QStringList> eqValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_EQUIPMENT_RECOIL_COUNT).toString() << values.value(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY).toString()) << (QStringList() << values.value(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT).toString() << values.value(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY).toString());
    newListItem->setValues(eqValues);
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(dliEquipmentSelected(int)));
    connect(newListItem, SIGNAL(deselected(int)), this, SLOT(dliEquipmentDeselect(int)));
    connect(this, SIGNAL(selectEquipmentExclusive(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    equipmentListLayout->addWidget(newListItem);
}

void WorkProcessMetaDataView::removeEquipment(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = equipmentListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            equipmentListLayout->removeItem(item);
            delete item->widget();
            delete item;
            break;
        }
        i++;
    }
}

void WorkProcessMetaDataView::updateEquipment(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int id = values.value(DBConstants::COL_EQUIPMENT_ID).toInt();
    int i = 0;
    while((item = equipmentListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            QList<QStringList> eqValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_EQUIPMENT_RECOIL_COUNT).toString() << values.value(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY).toString()) << (QStringList() << values.value(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT).toString() << values.value(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY).toString());
            dli->setValues(eqValues);
            break;
        }
        i++;
    }
}

void WorkProcessMetaDataView::clearEquipments(){
    QLayoutItem *item;
    while((item = equipmentListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void WorkProcessMetaDataView::onLeaving(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORK_PROCESS_DESCRIPTION, txtBxDescription->text());
    values.insert(DBConstants::COL_WORK_PROCESS_MTM_CODE, vcMTMCode->getTextValue());
    values.insert(DBConstants::COL_WORK_PROCESS_WORKING_HEIGHT, numBxWorkingHeight->getValue());
    values.insert(DBConstants::COL_WORK_PROCESS_DISTANCE, numBxDistance->getValue());
    values.insert(DBConstants::COL_WORK_PROCESS_IMPULSE_INTENSITY, oscImpulseIntensity->getSelectedValue().toInt());
    values.insert(DBConstants::COL_WORK_PROCESS_IMPULSE_COUNT, numBxImpulseCount->getValue());
    values.insert(DBConstants::COL_WORK_PROCESS_EQUIPMENT_ID, selectedEquipment_ID);
    emit saveWorkProcess(values);
}

//PRIVATE SLOTS
void WorkProcessMetaDataView::dliEquipmentSelected(int id){
    selectedEquipment_ID = id;
    emit selectEquipmentExclusive(id);
}

void WorkProcessMetaDataView::dliEquipmentDeselect(int id){
    if(selectedEquipment_ID == id)
        selectedEquipment_ID = 0;
}

void WorkProcessMetaDataView::btnCreateEquipmentClicked(){
    emit showPopUp(PopUpType::EQUIPMENT_POPUP);
}


