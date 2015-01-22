#include "mainmenu.h"
#include "viewcontroller.h"
#include "separator.h"
#include <QGridLayout>
#include <QVBoxLayout>

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    lblViewName(new QLabel(tr("Ergonomieapp"))),
    btnMetaDataView(new QPushButton(tr("Head Data"))),
    btnWorkplaceList(new QPushButton(tr("Work Stations"))),
    btnRessourceManagement(new QPushButton(tr ("Ressource Management"))),
    //btnNewRecording(new QPushButton(tr("New Recording")))
    btnSettings(new QPushButton(tr("")))

{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    btnMetaDataView->setMinimumSize(300, 60);
    btnWorkplaceList->setMinimumSize(300, 60);
    //btnNewRecording->setMinimumSize(300, 60);
    btnRessourceManagement->setMinimumSize(300, 60);
    //btnSettings->setMinimumSize(300, 60);

    btnSettings->setObjectName("settingsIcon");
    btnSettings->setFixedSize(45, 45);

    connect(btnMetaDataView, SIGNAL(clicked()), this, SIGNAL(showMetaDataView()));
    connect(btnWorkplaceList, SIGNAL(clicked()), this, SIGNAL(showWorkplaceListView()));
    connect(btnRessourceManagement, SIGNAL(clicked()), this, SIGNAL(showRessourceManagementView()));
    //connect(btnNewRecording, SIGNAL(clicked()), this, SIGNAL(showNewRecordingView()));
    connect(btnSettings, SIGNAL(clicked()), this, SIGNAL(showSettingsView()));

    lblViewName->setObjectName("lblHeader");

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(new QLabel(), 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(btnSettings, 0, 2, 1, 1, Qt::AlignRight);

    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    mainLayout->addWidget(btnMetaDataView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60, QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnWorkplaceList, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnRessourceManagement, 0, Qt::AlignCenter);
    //mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    //mainLayout->addWidget(btnNewRecording, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Expanding));
    /*mainLayout->addWidget(btnSettings, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Expanding));*/

    setLayout(mainLayout);
}
