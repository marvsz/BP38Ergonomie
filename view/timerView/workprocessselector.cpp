#include "workprocessselector.h"
#include <QHBoxLayout>

WorkProcessSelector::WorkProcessSelector(QWidget *parent) : QWidget(parent),
    btnRight(new QPushButton(">")),
    btnLeft(new QPushButton("<")),
    lblSelectedAV(new QLabel()),
    prefix(QString(""))
{
    lblSelectedAV->setMaximumWidth(150);
    lblSelectedAV->setMinimumWidth(100);

    btnRight->setFixedSize(40, 40);
    connect(btnRight, SIGNAL(clicked()), this, SIGNAL(nextAV()));

    btnLeft->setFixedSize(40, 40);
    connect(btnLeft, SIGNAL(clicked()), this, SIGNAL(previousAV()));

    this->setMaximumWidth(230);
    this->setMinimumWidth(180);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(btnLeft);
    mainLayout->addWidget(lblSelectedAV);
    mainLayout->addWidget(btnRight);

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


