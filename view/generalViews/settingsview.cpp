#include "settingsview.h"
#include "separator.h"
#include <QGridLayout>
#include <QVBoxLayout>

SettingsView::SettingsView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Settings"), parent),
    btnResetRecordings(new QPushButton(tr("Reset recordings"))),
    btnReset(new QPushButton(tr("Restore factory settings")))
{
    btnResetRecordings->setMinimumSize(300, 60);
    connect(btnResetRecordings, SIGNAL(clicked()), this, SIGNAL(resetRecordings()));

    btnReset->setMinimumSize(300, 60);
    connect(btnReset, SIGNAL(clicked()), this, SLOT(btnResetClicked()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(btnResetRecordings, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,60,QSizePolicy::Minimum, QSizePolicy::Fixed));
    mainLayout->addWidget(btnReset, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    setLayout(mainLayout);
}

void SettingsView::btnResetClicked(){
    emit resetDatabase();
    emit showView(ViewType::ANALYST_SELECTION_VIEW);
}
