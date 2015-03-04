#include "ressourcemanagementview.h"
#include <QIcon>
#include <QVBoxLayout>
#include <QGridLayout>
#include "../separator.h"

RessourceManagementView::RessourceManagementView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Ressource Management"), parent),
    btnEquipmentView(new IconButton(this, "equipmentIcon", tr("Equipment"))),
    btnProductView(new IconButton(this, "productIcon", tr("Products"))),
    btnTransportationView(new IconButton(this, "transportationIcon", tr("Transportations"))),
    btnEmployeeView(new IconButton(this, "userIcon", tr("Employee")))
{
    btnEquipmentView->setMinimumSize(300, 60);
    btnProductView->setMinimumSize(300, 60);
    btnTransportationView->setMinimumSize(300, 60);
    btnEmployeeView->setMinimumSize(300, 60);

    connect(btnEquipmentView, SIGNAL(clicked()), this, SLOT(btnEquipmentClicked()));
    connect(btnProductView, SIGNAL(clicked()), this, SLOT(btnProductClicked()));
    connect(btnTransportationView, SIGNAL(clicked()), this, SLOT(btnTransportationClicked()));
    connect(btnEmployeeView, SIGNAL(clicked()), this, SLOT(btnEmployeeClicked()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Expanding, QSizePolicy::Expanding));
    mainLayout->addWidget(btnEquipmentView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnProductView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnTransportationView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnEmployeeView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Expanding));

    setLayout(mainLayout);
}

void RessourceManagementView::btnEquipmentClicked(){
    emit showView(ViewType::EQUIPMENT_VIEW);
}

void RessourceManagementView::btnProductClicked(){
    emit showView(ViewType::PRODUCT_VIEW);
}

void RessourceManagementView::btnTransportationClicked(){
    emit showView(ViewType::TRANSPORTATION_VIEW);
}

void RessourceManagementView::btnEmployeeClicked(){
    emit showView(ViewType::EMPLOYEE_LIST_VIEW);
}
