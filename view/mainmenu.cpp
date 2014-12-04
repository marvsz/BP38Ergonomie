#include "mainmenu.h"
#include "viewcontroller.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QWidget>

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent)
{
    QGroupBox *buttonGroup = new QGroupBox(this);
    QVBoxLayout *groupLayout = new QVBoxLayout;

    angleView = new QPushButton(this);
    angleView->setText("Körperhaltung");
    angleView->setMinimumSize(300, 100);
    connect(angleView, SIGNAL(clicked()), this, SLOT(openAngleView()));

    toolView = new QPushButton(this);
    toolView->setText("Lastenhandhabung");
    toolView->setMinimumSize(300, 100);
    connect(toolView, SIGNAL(clicked()), this, SLOT(openTransportView()));

    actionForceView = new QPushButton(this);
    actionForceView->setText("Aktionskraft");
    actionForceView->setMinimumSize(300, 100);
    connect(actionForceView, SIGNAL(clicked()), this, SLOT(openActionForceView()));

    groupLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    groupLayout->addWidget(angleView, 0, Qt::AlignCenter);
    groupLayout->addSpacerItem(new QSpacerItem(0,60, QSizePolicy::Minimum, QSizePolicy::Fixed));
    groupLayout->addWidget(toolView, 0, Qt::AlignCenter);
    groupLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    groupLayout->addWidget(actionForceView, 0, Qt::AlignCenter);
    groupLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    buttonGroup->setLayout(groupLayout);
    this->setCentralWidget(buttonGroup);
}

void MainMenu::openAngleView(){
    emit angleViewSelected();
}

void MainMenu::openTransportView(){
    emit toolViewSelected();
}

void MainMenu::openActionForceView(){
    emit actionForceViewSelected();
}
