#include "mainmenu.h"
#include "viewcontroller.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QWidget>

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent)
{
    QVBoxLayout *groupLayout = new QVBoxLayout;
    QWidget *mainWidget = new QWidget;

    metaDataViewBtn = new QPushButton(this);
    metaDataViewBtn->setText("Kopfdaten");
    metaDataViewBtn->setMinimumSize(300, 60);
    connect(metaDataViewBtn, SIGNAL(clicked()), this, SLOT(openMetaDataView()));

    newWorkplaceBtn = new QPushButton(this);
    newWorkplaceBtn->setText("Neuer Arbeitsplatz");
    newWorkplaceBtn->setMinimumSize(300, 60);
    connect(newWorkplaceBtn, SIGNAL(clicked()), this, SLOT(openNewWorkplaceView()));

    newRecordingBtn = new QPushButton(this);
    newRecordingBtn->setText("Neue Aufnahme");
    newRecordingBtn->setMinimumSize(300, 60);
    connect(newRecordingBtn, SIGNAL(clicked()), this, SLOT(openNewRecordingView()));

    groupLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    groupLayout->addWidget(metaDataViewBtn, 0, Qt::AlignCenter);
    groupLayout->addSpacerItem(new QSpacerItem(0,60, QSizePolicy::Minimum, QSizePolicy::Fixed));
    groupLayout->addWidget(newWorkplaceBtn, 0, Qt::AlignCenter);
    groupLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    groupLayout->addWidget(newRecordingBtn, 0, Qt::AlignCenter);
    groupLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Expanding));

    mainWidget->setLayout(groupLayout);
    this->setCentralWidget(mainWidget);
}

void MainMenu::openMetaDataView(){
    emit metaDataViewSelected();
}

void MainMenu::openNewWorkplaceView(){
    emit newWorkplaceViewSelected();
}

void MainMenu::openNewRecordingView(){
    emit newRecordingViewSelected();
}
