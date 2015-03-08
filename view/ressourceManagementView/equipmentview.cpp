#include "equipmentview.h"
#include <QGridLayout>
#include "../flickcharm.h"
#include "../separator.h"
#include "../detailedlistitem.h"

EquipmentView::EquipmentView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Equipment"), parent),
    scEquipment(new QScrollArea),
    lblAddEquipment(new QLabel(tr("Add Equipment"))),
    lblName(new QLabel(tr("Name:"))),
    lblRecoilCount(new QLabel(tr("Recoil Count:"))),
    lblRecoilIntensity(new QLabel(tr("Recoil Intensity [N]:"))),
    lblVibrationCount(new QLabel(tr("Vibration Count:"))),
    lblVibrationIntensity(new QLabel(tr("Vibration Intensity [N]"))),
    txtBxName(new TextLineEdit()),
    numBxRecoilCount(new NumberLineEdit()),
    numBxRecoilIntensity(new NumberLineEdit()),
    numBxVibrationCount(new NumberLineEdit()),
    numBxVibrationIntensity(new NumberLineEdit()),
    btnAdd(new QPushButton()),
    equipmentListLayout(new QVBoxLayout)
{
    btnAdd->setObjectName("plusIcon");
    btnAdd->setFixedSize(45, 45);
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));

    lblAddEquipment->setObjectName("lblHeader");
    txtBxName->setPlaceholderText(tr("name of the equipment"));
    numBxRecoilCount->setPlaceholderText(tr("recoil count"));
    numBxRecoilIntensity->setPlaceholderText(tr("recoil intensity"));
    numBxVibrationCount->setPlaceholderText(tr("vibration count"));
    numBxVibrationIntensity->setPlaceholderText(tr("vibration intensity"));

    QGridLayout *equipmentDataLayout = new QGridLayout;
    equipmentDataLayout->addWidget(lblAddEquipment, 0, 0, 1, 1, 0);
    equipmentDataLayout->addWidget(lblName, 1, 0, 1, 1, 0);
    equipmentDataLayout->addWidget(txtBxName, 1, 1, 1, 1, 0);
    equipmentDataLayout->addWidget(lblRecoilCount, 2, 0, 1, 1, 0);
    equipmentDataLayout->addWidget(numBxRecoilCount, 2, 1, 1, 1, 0);
    equipmentDataLayout->addWidget(lblRecoilIntensity, 2, 2, 1, 1, 0);
    equipmentDataLayout->addWidget(numBxRecoilIntensity, 2, 3, 1, 1, 0);
    equipmentDataLayout->addWidget(lblVibrationCount, 3, 0, 1, 1, 0);
    equipmentDataLayout->addWidget(numBxVibrationCount, 3, 1, 1, 1, 0);
    equipmentDataLayout->addWidget(lblVibrationIntensity, 3, 2, 1, 1, 0);
    equipmentDataLayout->addWidget(numBxVibrationIntensity, 3, 3, 1, 1, 0);
    equipmentDataLayout->addWidget(btnAdd, 4, 0, 1, 4, Qt::AlignCenter);

    QWidget *listContent = new QWidget;
    listContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scEquipment->setWidget(listContent);
    scEquipment->setWidgetResizable(true);
    listContent->setLayout(equipmentListLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(equipmentDataLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addWidget(scEquipment);

    equipmentListLayout->setAlignment(Qt::AlignTop);

    setLayout(mainLayout);
}

EquipmentView::~EquipmentView(){
}

// PUBLIC SLOTS
void EquipmentView::addEquipment(QHash<QString, QVariant> values){
    DetailedListItem *newListItem = new DetailedListItem(0, "equipmentIcon", values.value(DBConstants::COL_EQUIPMENT_NAME).toString(), equipmentItemScheme, true, false, false);
    newListItem->setID(values.value(DBConstants::COL_EQUIPMENT_ID).toInt());
    QList<QStringList> eqValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_EQUIPMENT_RECOIL_COUNT).toString() << values.value(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY).toString()) << (QStringList() << values.value(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT).toString() << values.value(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY).toString());
    newListItem->setValues(eqValues);
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteEquipment(int)));
    equipmentListLayout->addWidget(newListItem);
}

void EquipmentView::removeEquipment(int id){
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

void EquipmentView::updateEquipment(QHash<QString, QVariant> values){
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

void EquipmentView::clearEquipments(){
    QLayoutItem *item;
    while((item = equipmentListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

// PRIVATE SLOTS
void EquipmentView::btnAddClicked(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_EQUIPMENT_NAME, txtBxName->text());
    values.insert(DBConstants::COL_EQUIPMENT_RECOIL_COUNT, numBxRecoilCount->getValue());
    values.insert(DBConstants::COL_EQUIPMENT_RECOIL_INTENSITY, numBxRecoilIntensity->getValue());
    values.insert(DBConstants::COL_EQUIPMENT_VIBRATION_COUNT, numBxVibrationCount->getValue());
    values.insert(DBConstants::COL_EQUIPMENT_VIBRATION_INTENSITY, numBxVibrationIntensity->getValue());
    emit createEquipment(values);
    txtBxName->clear();
    numBxRecoilCount->clear();
    numBxRecoilIntensity->clear();
    numBxVibrationCount->clear();
    numBxVibrationIntensity->clear();
}

