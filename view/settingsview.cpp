#include "settingsview.h"
#include "separator.h"
#include <QGridLayout>
#include <QVBoxLayout>

SettingsView::SettingsView(QWidget *parent) :
    QWidget(parent),
    lblViewName(new QLabel(tr("Settings"))),
    btnBack(new QPushButton()),
    btnReset(new QPushButton(tr("reset database")))
{
    btnBack->setObjectName("leftIcon");
    btnBack->setFixedSize(45, 45);
    connect(btnBack, SIGNAL(clicked()), this, SIGNAL(back()));

    btnReset->setMinimumSize(300, 60);
    connect(btnReset, SIGNAL(clicked()), this, SIGNAL(resetDB()));

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(btnReset, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    setLayout(mainLayout);
}
