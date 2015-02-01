#include "ressourcemanagementview.h"
#include <QIcon>
#include <QVBoxLayout>
#include <QGridLayout>
#include "separator.h"
#include "iconconstants.h"

RessourceManagementView::RessourceManagementView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Ressource Management"), parent),
    btnEquipmentView(new QPushButton(tr("Equipment"))),
    btnProductView(new QPushButton(tr("Products"))),
    btnTransportationView(new QPushButton(tr("Transportations")))
{
    btnEquipmentView->setMinimumSize(300, 60);
    btnProductView->setMinimumSize(300, 60);
    btnTransportationView->setMinimumSize(300, 60);

    connect(btnEquipmentView, SIGNAL(clicked()), this, SLOT(btnEquipmentClicked()));
    connect(btnProductView, SIGNAL(clicked()), this, SLOT(btnProductClicked()));
    connect(btnTransportationView, SIGNAL(clicked()), this, SLOT(btnTransportationClicked()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Expanding, QSizePolicy::Expanding));
    mainLayout->addWidget(btnEquipmentView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnProductView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnTransportationView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Expanding));

    setLayout(mainLayout);
}

void RessourceManagementView::btnEquipmentClicked(){
    emit show(ViewType::EQUIPMENT_VIEW);
}

void RessourceManagementView::btnProductClicked(){
    emit show(ViewType::PROCUCT_VIEW);
}

void RessourceManagementView::btnTransportationClicked(){
    emit show(ViewType::TRANSPORTATION_VIEW);
}
