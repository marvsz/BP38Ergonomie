#include "mainmenu.h"
#include "viewcontroller.h"
#include <QVBoxLayout>

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    btnMetaDataView(new QPushButton(tr("Head Data"))),
    btnWorkplaceList(new QPushButton(tr("Work Stations"))),
    btnRessourceManagement(new QPushButton(tr ("Ressource Management"))),
    btnNewRecording(new QPushButton(tr("New Recording"))),
    btnSettings(new QPushButton(tr("Settings")))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    btnMetaDataView->setMinimumSize(300, 60);
    btnWorkplaceList->setMinimumSize(300, 60);
    btnNewRecording->setMinimumSize(300, 60);
    btnRessourceManagement->setMinimumSize(300, 60);
    btnSettings->setMinimumSize(300, 60);

    connect(btnMetaDataView, SIGNAL(clicked()), this, SIGNAL(showMetaDataView()));
    connect(btnWorkplaceList, SIGNAL(clicked()), this, SIGNAL(showWorkplaceListView()));
    connect(btnRessourceManagement, SIGNAL(clicked()), this, SIGNAL(showRessourceManagementView()));
    connect(btnNewRecording, SIGNAL(clicked()), this, SIGNAL(showNewRecordingView()));
    connect(btnSettings, SIGNAL(clicked()), this, SIGNAL(showSettingsView()));

    mainLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    mainLayout->addWidget(btnMetaDataView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60, QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnWorkplaceList, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnRessourceManagement, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnNewRecording, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(btnSettings, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Expanding));

    setLayout(mainLayout);
}
