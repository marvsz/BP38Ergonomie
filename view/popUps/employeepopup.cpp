#include "employeepopup.h"

EmployeePopUp::EmployeePopUp(QWidget *parent):
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Select employee"), parent),
    mainLayout(new QGridLayout)
{
    setLayout(mainLayout);
}

//PUBLIC SLOTS
void EmployeePopUp::addEmployee(QHash<QString, QVariant> values){
    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_EMPLOYEE_STAFF_NUMBER).toString());
    DetailedListItem *newListItem = new DetailedListItem(this, "userIcon", tr("Employee"), employeeCaptions, false, true, false, false, false);
    newListItem->setValues(dliValues);
    newListItem->setID(values.value(DBConstants::COL_EMPLOYEE_ID).toInt());
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedEmployeeChanged(int)));
    connect(this, SIGNAL(selectedEmployee(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    connect(newListItem, SIGNAL(deselected(int)), this, SLOT(deselectedEmployee(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteEmployee(int)));
    mainLayout->addWidget(newListItem);
}

void EmployeePopUp::updateEmployee(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int id = values.value(DBConstants::COL_EMPLOYEE_ID).toInt();
    int i = 0;
    while((item = mainLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_EMPLOYEE_STAFF_NUMBER).toString());
            dli->setValues(dliValues);
            break;
        }
        i++;
    }
}

void EmployeePopUp::removeEmployee(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = mainLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            mainLayout->removeItem(item);
            delete item->widget();
            delete item;
            break;
        }
        i++;
    }
}

void EmployeePopUp::clearEmployees(){
    QLayoutItem *item;
    while((item = mainLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void EmployeePopUp::onLeaving(){
    emit selectEmployee(selectedEmployeeID);
}

void EmployeePopUp::setSelectedEmployee(int id){
    selectedEmployeeChanged(id);
}

//PRIVATE SLOTS
void EmployeePopUp::selectedEmployeeChanged(int id){
    selectedEmployeeID = id;
    emit selectedEmployee(id);
}

void EmployeePopUp::deselectedEmployee(int id){
    if(selectedEmployeeID == id)
        selectedEmployeeID = 0;
}


