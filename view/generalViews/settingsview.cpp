#include "settingsview.h"
#include "../separator.h"
#include <QGridLayout>
#include <QVBoxLayout>

SettingsView::SettingsView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Settings"), parent),
    btnImportData(new IconButton(this, "importData", tr("Import Data"))),
    btnResetRecordings(new IconButton(this, "resetIcon", tr("Reset Recordings"))),
    btnRestoreFactory(new IconButton(this, "resetFactoryIcon", tr("Restore Factory Settings"))),
    btnSelectLanguage(new IconButton(this, "germanIcon", tr("Change Language"))),
    btnSelectTheme(new IconButton(this, "blueIcon", tr("Change Theme")))
{
    btnImportData->setMinimumSize(320, 60);
    connect(btnImportData, SIGNAL(clicked()), this, SLOT(btnImportDataClicked()));
    btnResetRecordings->setMinimumSize(320, 60);
    connect(btnResetRecordings, SIGNAL(clicked()), this, SLOT(btnResetRecordingsClicked()));

    btnRestoreFactory->setMinimumSize(320, 60);
    connect(btnRestoreFactory, SIGNAL(clicked()), this, SLOT(btnRestoreFactoryClicked()));

    btnSelectLanguage->setMinimumSize(320, 60);
    connect(btnSelectLanguage, SIGNAL(clicked()), this, SLOT(btnSelectLanguageClicked()));

    btnSelectTheme->setMinimumSize(320, 60);
    connect(btnSelectTheme, SIGNAL(clicked()), this, SLOT(btnSelectThemeClicked()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(btnImportData, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnResetRecordings, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnRestoreFactory, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnSelectLanguage, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnSelectTheme, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    setLayout(mainLayout);
}

void SettingsView::btnImportDataClicked(){
    emit showPopUp(PopUpType::IMPORT_DATA_POPUP);
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
