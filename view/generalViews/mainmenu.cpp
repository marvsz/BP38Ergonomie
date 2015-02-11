#include "mainmenu.h"
#include "separator.h"
#include <QGridLayout>
#include <QVBoxLayout>

MainMenu::MainMenu(QWidget *parent) :
    SimpleNavigateableWidget(tr("Main menu"), parent),
    lblViewName(new QLabel(tr("Ergonomieapp"))),
    btnMetaDataView(new QPushButton(tr("Head Data"))),
    btnWorkplaceList(new QPushButton(tr("Work Stations"))),
    btnRessourceManagement(new QPushButton(tr ("Ressource Management"))),
    btnShift(new QPushButton(tr("Shift Data"))),
    btnSettings(new QPushButton()),
    btnNewRecording(new QPushButton(tr("New recording"))),
    btnSendDatabase(new QPushButton())

{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    btnMetaDataView->setMinimumSize(300, 60);
    btnWorkplaceList->setMinimumSize(300, 60);
    btnRessourceManagement->setMinimumSize(300, 60);
    btnShift->setMinimumSize(300, 60);
    btnNewRecording->setMinimumSize(300, 60);

    btnSettings->setObjectName("settingsIcon");
    btnSettings->setFixedSize(45, 45);

    btnSendDatabase->setObjectName("sendIcon");
    btnSendDatabase->setFixedSize(45, 45);

    connect(btnMetaDataView, SIGNAL(clicked()), this, SLOT(btnMetaDataViewClicked()));
    connect(btnWorkplaceList, SIGNAL(clicked()), this, SLOT(btnWorkplaceListClicked()));
    connect(btnRessourceManagement, SIGNAL(clicked()), this, SLOT(btnRessourceManagementClicked()));
    connect(btnShift, SIGNAL(clicked()), this, SLOT(btnShiftClicked()));
    connect(btnNewRecording, SIGNAL(clicked()), this, SLOT(btnNewRecordingClicked()));
    connect(btnSettings, SIGNAL(clicked()), this, SLOT(btnSettingsClicked()));
    connect(btnSendDatabase, SIGNAL(clicked()), this, SLOT(btnSendDatabaseClicked()));

    lblViewName->setObjectName("lblHeader");

    mainLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    mainLayout->addWidget(btnMetaDataView, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60, QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnWorkplaceList, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnRessourceManagement, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnShift, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnNewRecording, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Minimum, QSizePolicy::Expanding));


    setLayout(mainLayout);

}

//PUBLIC METHODS
QList<QAbstractButton*> * MainMenu::getAdditionalNavigation() const{
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnSettings);
    additions->append(btnSendDatabase);
    return additions;
}

//PRIVATE SLOTS
void MainMenu::btnMetaDataViewClicked(){
    emit showView(ViewType::METADATA_VIEW);
}
void MainMenu::btnSettingsClicked(){
    emit showView(ViewType::SETTINGS_VIEW);
}

void MainMenu::btnWorkplaceListClicked(){
    emit showView(ViewType::WORKPLACELIST_VIEW);
}

void MainMenu::btnRessourceManagementClicked(){
    emit showView(ViewType::RESSOURCE_MANAGMENT_VIEW);
}

void MainMenu::btnShiftClicked(){
    emit showView(ViewType::SHIFT_VIEW);
}

void MainMenu::btnNewRecordingClicked(){
    emit createBlankRecording();
}

void MainMenu::btnSendDatabaseClicked(){
    emit showPopUp(PopUpType::DB_SEND_POPUP);
}
