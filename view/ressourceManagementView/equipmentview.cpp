#include "equipmentview.h"
#include <QGridLayout>
#include "flickcharm.h"
#include "separator.h"
#include "detailedlistitem.h"
#include "iconconstants.h"

const QList<QStringList> EquipmentView::equipmentItemScheme = QList<QStringList>() << (QStringList() << tr("recoil count") << tr ("recoil intensity")) << (QStringList() << tr("vibration count") << tr("vibration intensity"));

EquipmentView::EquipmentView(QWidget *parent) :
    QWidget(parent),
    scEquipment(new QScrollArea),
    lblAddEquipment(new QLabel(tr("Add Equipment"))),
    lblViewName(new QLabel(tr("Equipment"))),
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
    btnBack(new QPushButton()),
    btnAdd(new QPushButton()),
    equipmentListLayout(new QVBoxLayout)
{
    btnBack->setObjectName("leftIcon");
    btnBack->setFixedSize(45, 45);
    btnAdd->setObjectName("plusIcon");
    btnAdd->setFixedSize(45, 45);
    connect(btnBack, SIGNAL(clicked()), this, SIGNAL(back()));
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));

    lblAddEquipment->setObjectName("lblHeader");
    txtBxName->setPlaceholderText(tr("name of the equipment"));
    numBxRecoilCount->setPlaceholderText(tr("recoil count"));
    numBxRecoilIntensity->setPlaceholderText(tr("recoil intensity"));
    numBxVibrationCount->setPlaceholderText(tr("vibration count"));
    numBxVibrationIntensity->setPlaceholderText(tr("vibration intensity"));

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, Qt::AlignRight);

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
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(equipmentDataLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addWidget(scEquipment);

    setLayout(mainLayout);
}

EquipmentView::~EquipmentView(){
}

// PUBLIC SLOTS
void EquipmentView::setEquipment(const QString &name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity){
    txtBxName->setText(name);
    numBxRecoilCount->setValue(recoilCount);
    numBxRecoilIntensity->setValue(recoilIntensity);
    numBxVibrationCount->setValue(vibrationCount);
    numBxVibrationIntensity->setValue(vibrationIntensity);
}

void EquipmentView::addEquipment(int id, const QString &name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity){
    DetailedListItem *newListItem = new DetailedListItem(0, IconConstants::ICON_EQUIPMENT, name, equipmentItemScheme, true, false, false);
    newListItem->setID(id);
    QList<QStringList> values = QList<QStringList>() << (QStringList() << QString::number(recoilCount) << QString::number(recoilIntensity)) << (QStringList() << QString::number(vibrationCount) << QString::number(vibrationIntensity));
    newListItem->setValues(values);
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteEquipment(int)));
    equipmentListLayout->addWidget(newListItem);
}

void EquipmentView::clear(){
    QLayoutItem *item;
    while((item = equipmentListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

// PRIVATE SLOTS

void EquipmentView::btnAddClicked(){
    emit saveEquipment();
    txtBxName->clear();
    numBxRecoilCount->clear();
    numBxRecoilIntensity->clear();
    numBxVibrationCount->clear();
    numBxVibrationIntensity->clear();
}

// GETTER

QString EquipmentView::getName() const{
    return txtBxName->text();
}

int EquipmentView::getRecoilCount() const{
    return numBxRecoilCount->getValue();
}

int EquipmentView::getRecoilIntensity() const{
    return numBxRecoilIntensity->getValue();
}

int EquipmentView::getVibrationCount() const{
    return numBxVibrationCount->getValue();
}

int EquipmentView::getVibrationIntensity() const{
    return numBxVibrationIntensity->getValue();
}
