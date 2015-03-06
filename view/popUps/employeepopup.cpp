#include "employeepopup.h"
#include <detailedlistitem.h>

EmployeePopUp::EmployeePopUp(QWidget *parent):
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Select employee"), parent),
    mainLayout(new QGridLayout)
{
    mainLayout->addWidget(new QLabel("test"), 0, 0, 1, 1, 0);

    setLayout(mainLayout);
}

EmployeePopUp::~EmployeePopUp()
{

}

void EmployeePopUp::onEnter(){
    //addEmployees();
}

void EmployeePopUp::addEmployees(int id, const QString &productNumber){
    DetailedListItem *newListItem = new DetailedListItem(0, "employeeIcon", productNumber);
    newListItem->setID(id);
    newListItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedEmployeeChanged(int)));
    connect(this, SIGNAL(selectedProduct(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    mainLayout->addWidget(newListItem);
}

void EmployeePopUp::selectedEmployeeChanged(int id){
    selectedEmployeeID = id;
    //emit selectedEmployee(id);
}

