#include "resetpopup.h"
#include <QGridLayout>
#include "separator.h"

ResetPopUp::ResetPopUp(QWidget *parent):
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Select entries to reset"), parent),
    headData(new DetailedListItem(this, "commentIcon", tr("Head Data"), QList<QStringList>(), false, true, false, false, false)),
    workplaces(new DetailedListItem(this, "workplaceIcon", tr("Workplaces"), QList<QStringList>(), false, true, false, false, false)),
    equipment(new DetailedListItem(this, "equipmentIcon", tr("Equipment"), QList<QStringList>(), false, true, false, false, false)),
    products(new DetailedListItem(this, "productIcon", tr("Products"), QList<QStringList>(), false, true, false, false, false)),
    transportation(new DetailedListItem(this, "transportationIcon", tr("Transportation"), QList<QStringList>(), false, true, false, false, false)),
    employee(new DetailedListItem(this, "employeeIcon", tr("Employee"), QList<QStringList>(), false, true, false, false, false)),
    shiftData(new DetailedListItem(this, "calendarIcon", tr("Shift Data"),QList<QStringList>(), false, true, false, false, false)),
    bHeadData(false),
    bWorklpaces(false),
    bEquipment(false),
    bProducts(false),
    bTransportation(false),
    bEmployee(false),
    bShiftData(false)
{

    connect(headData, SIGNAL(clicked()), this, SLOT(headDataClicked()));
    connect(workplaces, SIGNAL(clicked()), this, SLOT(workplacesClicked()));
    connect(equipment, SIGNAL(clicked()), this, SLOT(equipmentClicked()));
    connect(products, SIGNAL(clicked()), this, SLOT(productsClicked()));
    connect(transportation, SIGNAL(clicked()), this, SLOT(transportationClicked()));
    connect(employee, SIGNAL(clicked()), this, SLOT(employeeClicked()));
    connect(shiftData, SIGNAL(clicked()), this, SLOT(shiftDataClicked()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(headData, 0, 0, 1, 1, 0);
    mainLayout->addWidget(workplaces, 1, 0, 1, 1, 0);
    mainLayout->addWidget(equipment, 2, 0, 1, 1, 0);
    mainLayout->addWidget(products, 3, 0, 1, 1, 0);
    mainLayout->addWidget(transportation, 4, 0, 1, 1, 0);
    mainLayout->addWidget(employee, 5, 0, 1, 1, 0);
    mainLayout->addWidget(shiftData, 6, 0, 1, 1, 0);

    setLayout(mainLayout);
}
ResetPopUp::~ResetPopUp()
{

}

void ResetPopUp::onEnter(){
    headData->deselect();
    workplaces->deselect();
    equipment->deselect();
    products->deselect();
    transportation->deselect();
    employee->deselect();
    shiftData->deselect();
    bHeadData = false;
    bWorklpaces = false;
    bEquipment = false;
    bProducts = false;
    bTransportation = false;
    bEmployee = false;
    bShiftData = false;
}

//PUBLIC METHODS
bool ResetPopUp::headDataSelected() const{
    return bHeadData;
}

bool ResetPopUp::workplacesSelected() const{
    return bWorklpaces;
}

bool ResetPopUp::equipmentSelected() const{
    return bEquipment;
}

bool ResetPopUp::productsSelected() const{
    return bProducts;
}

bool ResetPopUp::transportationSelected() const{
    return bTransportation;
}

bool ResetPopUp::employeeSelected() const{
    return bEmployee;
}

bool ResetPopUp::shiftDataSelected() const{
    return bShiftData;
}

//PRIVATE SLOTS
void ResetPopUp::headDataClicked(){
    bHeadData = !bHeadData;
}

void ResetPopUp::workplacesClicked(){
    bWorklpaces = !bWorklpaces;
}

void ResetPopUp::equipmentClicked(){
    bEquipment = !bEquipment;
}

void ResetPopUp::productsClicked(){
    bProducts = !bProducts;
}

void ResetPopUp::transportationClicked(){
    bTransportation = !bTransportation;
}

void ResetPopUp::employeeClicked(){
    bEmployee = !bEmployee;
}

void ResetPopUp::shiftDataClicked(){
    bShiftData = !bShiftData;
}
