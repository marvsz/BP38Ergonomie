#include "settingsview.h"
#include "separator.h"
#include <QGridLayout>
#include <QVBoxLayout>

SettingsView::SettingsView(QWidget *parent) :
    QWidget(parent),
    lblViewName(new QLabel(tr("Settings"))),
    btnBack(new QPushButton())
{
    btnBack->setObjectName("leftIcon");
    btnBack->setFixedSize(45, 45);
    connect(btnBack, SIGNAL(clicked()), this, SIGNAL(back()));

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(mainLayout);
}
