#include "ressourcemanagementview.h"
#include <QIcon>
#include <QVBoxLayout>
#include <QGridLayout>
#include "separator.h"
#include "iconconstants.h"

RessourceManagementView::RessourceManagementView(QWidget *parent) :
    QWidget(parent),
    lblViewName(new QLabel(tr("Ressource Management"))),
    btnBack(new QPushButton()),
    btnEquipmentView(new QPushButton(tr("Equipment"))),
    btnProductView(new QPushButton(tr("Products"))),
    btnTransportationView(new QPushButton(tr("Transportations")))
{
    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, 0);

    btnBack->setFixedSize(45, 45);
    btnBack->setObjectName("leftIcon");

    btnEquipmentView->setMinimumSize(300, 60);
    btnProductView->setMinimumSize(300, 60);
    btnTransportationView->setMinimumSize(300, 60);

    connect(btnBack, SIGNAL(clicked()), this, SIGNAL(back()));
    connect(btnEquipmentView, SIGNAL(clicked()), this, SIGNAL(showEquipmentView()));
    connect(btnProductView, SIGNAL(clicked()), this, SIGNAL(showProductView()));
    connect(btnTransportationView, SIGNAL(clicked()), this, SIGNAL(showTransportationView()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Expanding, QSizePolicy::Expanding));
    mainLayout->addWidget(btnEquipmentView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnProductView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnTransportationView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Expanding));

    setLayout(mainLayout);
}
