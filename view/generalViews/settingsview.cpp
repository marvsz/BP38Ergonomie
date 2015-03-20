#include "settingsview.h"
#include "../separator.h"
#include "../../standardpaths.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextStream>
#include <QDebug>

SettingsView::SettingsView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Settings"), parent),
    btnResetRecordings(new IconButton(this, "resetIcon", tr("Reset Recordings"))),
    btnRestoreFactory(new IconButton(this, "resetFactoryIcon", tr("Restore Factory Settings"))),
    btnSelectLanguage(new IconButton(this, "germanIcon", tr("Change Language"))),
    btnSelectTheme(new IconButton(this, "blueIcon", tr("Change Theme"))),
    dliShowTitles(new DetailedListItem(this, "titleIcon", tr("Show Titles"), QList<QStringList>(), false, true, false, false, false)),
    dliShowNotifications(new DetailedListItem(this, "notificationIcon", tr("Show Notifications"), QList<QStringList>(), false, true, false, false, false))
{
    QFile file(StandardPaths::configFile());
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line = in.readLine();
    QStringList settings = line.split(',');

    if(settings.at(0) == "english")
        btnSelectLanguage->setIcon("englishIcon");

    if(settings.at(1) == "green")
        btnSelectTheme->setIcon("greenIcon");

    if(settings.at(2) == "nTrue"){
        showNotifications = true;
        dliShowNotifications->select();
    }
    else{
        showNotifications = false;
        dliShowNotifications->deselect();
    }
    if(settings.at(3) == "tTrue"){
        showTitles = true;
        dliShowTitles->select();
    }
    else{
        showTitles = false;
        dliShowTitles->deselect();
    }

    btnResetRecordings->setMinimumSize(400, 60);
    connect(btnResetRecordings, SIGNAL(clicked()), this, SLOT(btnResetRecordingsClicked()));

    btnRestoreFactory->setMinimumSize(400, 60);
    connect(btnRestoreFactory, SIGNAL(clicked()), this, SLOT(btnRestoreFactoryClicked()));

    btnSelectLanguage->setMinimumSize(400, 60);
    connect(btnSelectLanguage, SIGNAL(clicked()), this, SLOT(btnSelectLanguageClicked()));

    btnSelectTheme->setMinimumSize(400, 60);
    connect(btnSelectTheme, SIGNAL(clicked()), this, SLOT(btnSelectThemeClicked()));

    connect(dliShowNotifications, SIGNAL(clicked()), this, SLOT(showNotificationsClicked()));
    connect(dliShowTitles, SIGNAL(clicked()), this, SLOT(showTitlesClicked()));

    QLabel *lblUiSettings = new QLabel(tr("User Interface Settings"));
    QLabel *lblAdvancedSettings = new QLabel(tr("Advanced Settings"));
    lblUiSettings->setObjectName("lblBig");
    lblAdvancedSettings->setObjectName("lblBig");
    QLabel *lblShowTitlesDescription = new QLabel(tr("Disabling this option will cause the the Application not to show titles in the navigation bar."));
    QLabel *lblShowNotificationsDescription = new QLabel(tr("Disabling this option will cause the the Application not to provide notification messages."));
    lblShowTitlesDescription->setWordWrap(true);
    lblShowNotificationsDescription->setWordWrap(true);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->setAlignment(Qt::AlignTop);
    leftLayout->addWidget(lblUiSettings, 0, Qt::AlignCenter);
    leftLayout->addSpacerItem(new QSpacerItem(0,20, QSizePolicy::Minimum, QSizePolicy::Fixed));
    leftLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    leftLayout->addSpacerItem(new QSpacerItem(0,20, QSizePolicy::Minimum, QSizePolicy::Fixed));

    leftLayout->addWidget(dliShowNotifications);
    leftLayout->addWidget(lblShowNotificationsDescription);
    leftLayout->addSpacerItem(new QSpacerItem(0,60, QSizePolicy::Minimum, QSizePolicy::Fixed));
    leftLayout->addWidget(dliShowTitles);
    leftLayout->addWidget(lblShowTitlesDescription);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->setAlignment(Qt::AlignTop);
    rightLayout->addWidget(lblAdvancedSettings, 0, Qt::AlignCenter);
    rightLayout->addSpacerItem(new QSpacerItem(0,20, QSizePolicy::Minimum, QSizePolicy::Fixed));
    rightLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    rightLayout->addSpacerItem(new QSpacerItem(0,20, QSizePolicy::Minimum, QSizePolicy::Fixed));
    rightLayout->addWidget(btnResetRecordings, 0, Qt::AlignCenter);
    rightLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    rightLayout->addWidget(btnRestoreFactory, 0, Qt::AlignCenter);
    rightLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    rightLayout->addWidget(btnSelectLanguage, 0, Qt::AlignCenter);
    rightLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    rightLayout->addWidget(btnSelectTheme, 0, Qt::AlignCenter);
    rightLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Fixed));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    mainLayout->addLayout(leftLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    mainLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    mainLayout->addLayout(rightLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    setLayout(mainLayout);
}

void SettingsView::btnRestoreFactoryClicked(){
    emit showPopUp((PopUpType::FACTORYSETTINGS_POPUP));
}

void SettingsView::btnResetRecordingsClicked(){
    emit showPopUp(PopUpType::RESET_POPUP);
}

void SettingsView::btnSelectLanguageClicked(){
    emit showPopUp(PopUpType::LANGUAGE_POPUP);
}

void SettingsView::btnSelectThemeClicked(){
    emit showPopUp(PopUpType::THEME_POPUP);
}

void SettingsView::setCurrentLanguageIcon(const QString &objectName){
    btnSelectLanguage->setIcon(objectName);
}

void SettingsView::setCurrentThemeIcon(const QString &objectName){
    btnSelectTheme->setIcon(objectName);
}

void SettingsView::showNotificationsClicked(){
    QFile file(StandardPaths::configFile());
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line = in.readLine();
    QStringList settings = line.split(',');
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    if(showNotifications){
        showNotifications = false;
        out<<settings.at(0)<<','<<settings.at(1)<<','<<"nFalse"<<','<<settings.at(3);
    }
    else {
        showNotifications = true;
        out<<settings.at(0)<<','<<settings.at(1)<<','<<"nTrue"<<','<<settings.at(3);
    }
}

void SettingsView::showTitlesClicked(){
    QFile file(StandardPaths::configFile());
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString line = in.readLine();
    QStringList settings = line.split(',');
    file.close();
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    if(showTitles){
        showTitles = false;
        out<<settings.at(0)<<','<<settings.at(1)<<','<<settings.at(2)<<','<<"tFalse";
    }
    else {
        showTitles = true;
        out<<settings.at(0)<<','<<settings.at(1)<<','<<settings.at(2)<<','<<"tTrue";
    }

}
