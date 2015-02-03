#include "timespinner.h"

TimeSpinner::TimeSpinner(QWidget *parent) :
    QWidget(parent),
    spinnerLayout(new QGridLayout()),
    timeBxTime(new TimeLineEdit(this, TimeLineType::HOUR_MINUTE)),
    btnHourInc(new QPushButton()),
    btnHourDec(new QPushButton()),
    btnMinuteInc(new QPushButton()),
    btnMinuteDec(new QPushButton),
    currentTime(QTime::currentTime())
{
    btnHourInc->setFixedSize(40, 40);
    btnHourInc->setObjectName("plusIcon");

    btnHourDec->setFixedSize(40, 40);
    btnHourDec->setObjectName("minusIcon");

    btnMinuteInc->setFixedSize(40, 40);
    btnMinuteInc->setObjectName("plusIcon");

    btnMinuteDec->setFixedSize(40, 40);
    btnMinuteDec->setObjectName("minusIcon");

    timeBxTime->setAlignment(Qt::AlignCenter);
    timeBxTime->setMaximumWidth(80);

    spinnerLayout->setContentsMargins(0,0,0,0);
    spinnerLayout->setSpacing(0);
    spinnerLayout->addWidget(btnHourInc, 0, 0, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMinuteInc, 0, 1, 1, 1, Qt::AlignCenter);

    spinnerLayout->addWidget(timeBxTime, 1, 0, 1, 2, Qt::AlignCenter);

    spinnerLayout->addWidget(btnHourDec, 2, 0, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMinuteDec, 2, 1, 1, 1, Qt::AlignCenter);

    connect(btnHourInc, SIGNAL(clicked()), timeBxTime, SLOT(increaseHour()));
    connect(btnMinuteInc, SIGNAL(clicked()), timeBxTime, SLOT(increaseMinute()));

    connect(btnHourDec, SIGNAL(clicked()), timeBxTime, SLOT(decreaseHour()));
    connect(btnMinuteDec, SIGNAL(clicked()), timeBxTime, SLOT(decreaseMinute()));

    setLayout(spinnerLayout);

}

// PUBLIC
QTime TimeSpinner::getTime() const {
    return timeBxTime->getTime();
}

void TimeSpinner::setTime(const QTime &time){
    timeBxTime->setTime(time);
}
