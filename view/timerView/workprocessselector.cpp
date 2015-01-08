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

    btnRight->setFixedSize(50, 50);
    connect(btnRight, SIGNAL(clicked()), this, SIGNAL(nextAV()));

    btnLeft->setFixedSize(50, 50);
    connect(btnLeft, SIGNAL(clicked()), this, SIGNAL(previousAV()));

    this->setMaximumSize(250, 50);
    this->setMinimumSize(200, 50);

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


