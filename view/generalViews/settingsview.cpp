#include "settingsview.h"
#include "separator.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include "../view/iconconstants.h"

SettingsView::SettingsView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Settings"), parent),
    btnResetRecordings(new IconButton(this, IconConstants::ICON_RESET, tr("Reset Recordings"))),
    btnReset(new IconButton(this, IconConstants::ICON_RESET_FACTORY, tr("Restore Factory Settings"))),
    btnSelectLanguage(new IconButton(this, IconConstants::ICON_GERMAN, tr("Change Language"))),
    btnSelectTheme(new IconButton(this, IconConstants::ICON_BLUE, tr("Change Theme")))
{
    btnResetRecordings->setMinimumSize(320, 60);
    connect(btnResetRecordings, SIGNAL(clicked()), this, SIGNAL(resetRecordings()));

    btnReset->setMinimumSize(320, 60);
    connect(btnReset, SIGNAL(clicked()), this, SLOT(btnResetClicked()));

    btnSelectLanguage->setMinimumSize(320, 60);
    connect(btnSelectLanguage, SIGNAL(clicked()), this, SLOT(btnSelectLanguageClicked()));

    btnSelectTheme->setMinimumSize(320, 60);
    connect(btnSelectTheme, SIGNAL(clicked()), this, SLOT(btnSelectThemeClicked()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(btnResetRecordings, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnReset, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnSelectLanguage, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnSelectTheme, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    setLayout(mainLayout);
}

void SettingsView::btnResetClicked(){
    emit resetDatabase();
    emit showView(ViewType::ANALYST_SELECTION_VIEW);
}

void SettingsView::btnSelectLanguageClicked(){
    emit showPopUp(PopUpType::LANGUAGE_POPUP);
}

void SettingsView::btnSelectThemeClicked(){
    emit showPopUp(PopUpType::THEME_POPUP);
}

void SettingsView::setCurrentLanguageIcon(const QString &iconPath){
    btnSelectLanguage->setIcon(QIcon(iconPath));
}

void SettingsView::setCurrentThemeIcon(const QString &iconPath){
    btnSelectTheme->setIcon(QIcon(iconPath));
}
