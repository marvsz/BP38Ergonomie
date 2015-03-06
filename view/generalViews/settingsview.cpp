#include "settingsview.h"
#include "../separator.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

SettingsView::SettingsView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Settings"), parent),
    btnResetRecordings(new IconButton(this, "resetIcon", tr("Reset Recordings"))),
    btnRestoreFactory(new IconButton(this, "resetFactoryIcon", tr("Restore Factory Settings"))),
    btnSelectLanguage(new IconButton(this, "germanIcon", tr("Change Language"))),
    btnSelectTheme(new IconButton(this, "blueIcon", tr("Change Theme"))),
    dliShowTitles(new DetailedListItem(this, "titleIcon", tr("Show Titles"), QList<QStringList>(), false, true, false, false, false)),
    dliShowNotifications(new DetailedListItem(this, "notificationIcon", tr("Show Notifications"), QList<QStringList>(), false, true, false, false, false))
{
    btnResetRecordings->setMinimumSize(320, 60);
    connect(btnResetRecordings, SIGNAL(clicked()), this, SLOT(btnResetRecordingsClicked()));

    btnRestoreFactory->setMinimumSize(320, 60);
    connect(btnRestoreFactory, SIGNAL(clicked()), this, SLOT(btnRestoreFactoryClicked()));

    btnSelectLanguage->setMinimumSize(320, 60);
    connect(btnSelectLanguage, SIGNAL(clicked()), this, SLOT(btnSelectLanguageClicked()));

    btnSelectTheme->setMinimumSize(320, 60);
    connect(btnSelectTheme, SIGNAL(clicked()), this, SLOT(btnSelectThemeClicked()));

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
    emit resetDatabase();
    emit showView(ViewType::ANALYST_SELECTION_VIEW);
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
