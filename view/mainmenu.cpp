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
    metaDataViewBtn->setText(tr("head data"));
    metaDataViewBtn->setMinimumSize(300, 60);
    connect(metaDataViewBtn, SIGNAL(clicked()), this, SLOT(openMetaDataView()));

    workplaceListBtn = new QPushButton(this);
    workplaceListBtn->setText(tr("work stations"));
    workplaceListBtn->setMinimumSize(300, 60);
    connect(workplaceListBtn, SIGNAL(clicked()), this, SLOT(openWorkplaceListView()));

    newRecordingBtn = new QPushButton(this);
    newRecordingBtn->setText(tr("new recording"));
    newRecordingBtn->setMinimumSize(300, 60);
    connect(newRecordingBtn, SIGNAL(clicked()), this, SLOT(openNewRecordingView()));

    groupLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    groupLayout->addWidget(metaDataViewBtn, 0, Qt::AlignCenter);
    groupLayout->addSpacerItem(new QSpacerItem(0,60, QSizePolicy::Minimum, QSizePolicy::Fixed));
    groupLayout->addWidget(workplaceListBtn, 0, Qt::AlignCenter);
    groupLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    groupLayout->addWidget(newRecordingBtn, 0, Qt::AlignCenter);
    groupLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Expanding));

    mainWidget->setLayout(groupLayout);
    this->setCentralWidget(mainWidget);
}

void MainMenu::openMetaDataView(){
    emit metaDataViewSelected();
}

void MainMenu::openWorkplaceListView(){
    emit workplaceListViewSelected();
}

void MainMenu::openNewRecordingView(){
    emit newRecordingViewSelected();
}
