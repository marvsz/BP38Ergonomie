#include "timespinner.h"

TimeSpinner::TimeSpinner(QWidget *parent) :
    QWidget(parent),
    spinnerLayout(new QGridLayout()),
    numBxHour(new NumberLineEdit()),
    numBxMinute(new NumberLineEdit()),
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

    numBxHour->setAlignment(Qt::AlignHCenter);
    numBxMinute->setAlignment(Qt::AlignHCenter);
    numBxHour->setMaximumWidth(40);
    numBxMinute->setMaximumWidth(40);

    numBxHour->setValue(currentTime.hour());
    numBxMinute->setValue(currentTime.minute());

    spinnerLayout->setContentsMargins(0,0,0,0);

    spinnerLayout->addWidget(btnHourInc, 0, 0, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMinuteInc, 0, 1, 1, 1, Qt::AlignCenter);

    spinnerLayout->addWidget(numBxHour, 1, 0, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(numBxMinute, 1, 1, 1, 1, Qt::AlignCenter);

    spinnerLayout->addWidget(btnHourDec, 2, 0, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMinuteDec, 2, 1, 1, 1, Qt::AlignCenter);

    connect(numBxHour, SIGNAL(editingFinished()), this, SLOT(setHour()));
    connect(numBxMinute, SIGNAL(editingFinished()), this, SLOT(setMinute()));

    connect(btnHourInc, SIGNAL(clicked()), this, SLOT(increaseHour()));
    connect(btnMinuteInc, SIGNAL(clicked()), this, SLOT(increaseMinute()));

    connect(btnHourDec, SIGNAL(clicked()), this, SLOT(decreaseHour()));
    connect(btnMinuteDec, SIGNAL(clicked()), this, SLOT(decreaseMinute()));

    setLayout(spinnerLayout);

}

// PRIVATE SLOTS

void TimeSpinner::increaseHour(){
    currentTime = currentTime.addSecs(3600);
    update();
}

void TimeSpinner::increaseMinute(){
    currentTime = currentTime.addSecs(60);
    update();
}

void TimeSpinner::decreaseHour(){
    currentTime = currentTime.addSecs(-3600);
    update();
}

void TimeSpinner::decreaseMinute(){
    currentTime = currentTime.addSecs(-60);
    update();
}

void TimeSpinner::setHour(){
    currentTime.setHMS(numBxHour->getValue(), currentTime.minute(), 0, 0);
    update();
}

void TimeSpinner::setMinute(){
    currentTime.setHMS(currentTime.hour(), numBxMinute->getValue(), 0, 0);
}

// PUBLIC
QTime TimeSpinner::getTime() const {
    return currentTime;
}

void TimeSpinner::setTime(const QTime &time){
    currentTime.secsTo(time);
    update();
}

// PRIVATE
void TimeSpinner::update(){
    numBxHour->setValue(currentTime.hour());
    numBxMinute->setValue(currentTime.minute());
}
