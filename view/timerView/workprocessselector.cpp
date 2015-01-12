#include "workprocessselector.h"
#include <QHBoxLayout>
#include <QIcon>
#include "iconconstants.h"

WorkProcessSelector::WorkProcessSelector(QWidget *parent) : QWidget(parent),
    btnRight(new QPushButton()),
    btnLeft(new QPushButton()),
    lblSelectedAV(new QLabel()),
    prefix(QString(""))
{
    lblSelectedAV->setMinimumSize(110, 45);
    btnRight->setFixedSize(45, 45);
    btnRight->setObjectName("rightIcon");

    btnLeft->setFixedSize(45, 45);
    btnLeft->setObjectName("leftIcon");

    connect(btnRight, SIGNAL(clicked()), this, SIGNAL(nextAV()));
    connect(btnLeft, SIGNAL(clicked()), this, SIGNAL(previousAV()));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(btnLeft, 0, Qt::AlignHCenter);
    mainLayout->addWidget(lblSelectedAV, 0, Qt::AlignHCenter);
    mainLayout->addWidget(btnRight, 0, Qt::AlignHCenter);

    setLayout(mainLayout);
}

WorkProcessSelector::~WorkProcessSelector()
{

}

//PUBLIC SLOTS
void WorkProcessSelector::setSelectedAV(int avNum){
    lblSelectedAV->setText(QString("%1 %2").arg(prefix).arg(avNum));
}

void WorkProcessSelector::setAVPrefix(const QString &pref){
    prefix = pref;
}


