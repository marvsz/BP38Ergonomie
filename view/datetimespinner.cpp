#include "datetimespinner.h"
#include <QDebug>

DateTimeSpinner::DateTimeSpinner(QWidget *parent) :
    QWidget(parent),
    spinnerLayout(new QGridLayout),
    numBxDay(new NumberLineEdit()),
    numBxMonth(new NumberLineEdit()),
    numBxYear(new NumberLineEdit()),
    numBxHour(new NumberLineEdit()),
    numBxMinute(new NumberLineEdit()),
    btnDayInc(new QPushButton()),
    btnDayDec(new QPushButton()),
    btnMonthInc(new QPushButton()),
    btnMonthDec(new QPushButton()),
    btnYearInc(new QPushButton()),
    btnYearDec(new QPushButton()),
    btnHourInc(new QPushButton()),
    btnHourDec(new QPushButton()),
    btnMinuteInc(new QPushButton()),
    btnMinuteDec(new QPushButton())
{
    currentTime = QDateTime::currentDateTime();

    btnDayInc->setFixedSize(40, 40);
    btnDayInc->setObjectName("plusIcon");

    btnMonthInc->setFixedSize(40, 40);
    btnMonthInc->setObjectName("plusIcon");

    btnYearInc->setFixedSize(40, 40);
    btnYearInc->setObjectName("plusIcon");

    btnHourInc->setFixedSize(40, 40);
    btnHourInc->setObjectName("plusIcon");

    btnMinuteInc->setFixedSize(40, 40);
    btnMinuteInc->setObjectName("plusIcon");

    numBxDay->setAlignment(Qt::AlignHCenter);
    numBxMonth->setAlignment(Qt::AlignHCenter);
    numBxYear->setAlignment(Qt::AlignHCenter);
    numBxHour->setAlignment(Qt::AlignHCenter);
    numBxMinute->setAlignment(Qt::AlignHCenter);
    numBxDay->setMaximumWidth(40);
    numBxMonth->setMaximumWidth(40);
    numBxYear->setMaximumWidth(60);
    numBxHour->setMaximumWidth(40);
    numBxMinute->setMaximumWidth(40);

    btnDayDec->setFixedSize(40, 40);
    btnDayDec->setObjectName("minusIcon");

    btnMonthDec->setFixedSize(40, 40);
    btnMonthDec->setObjectName("minusIcon");

    btnYearDec->setFixedSize(40, 40);
    btnYearDec->setObjectName("minusIcon");

    btnHourDec->setFixedSize(40, 40);
    btnHourDec->setObjectName("minusIcon");

    btnMinuteDec->setFixedSize(40, 40);
    btnMinuteDec->setObjectName("minusIcon");


    numBxDay->setValue(currentTime.date().day());
    numBxMonth->setValue(currentTime.date().month());
    numBxYear->setValue(currentTime.date().year());
    numBxHour->setValue(currentTime.time().hour());
    numBxMinute->setValue(currentTime.time().minute());

    spinnerLayout->addWidget(btnDayInc, 0, 0, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMonthInc, 0, 1, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnYearInc, 0, 2, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnHourInc, 0, 3, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMinuteInc, 0, 4, 1, 1, Qt::AlignCenter);

    spinnerLayout->addWidget(numBxDay, 1, 0, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(numBxMonth, 1, 1, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(numBxYear, 1, 2, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(numBxHour, 1, 3, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(numBxMinute, 1, 4, 1, 1, Qt::AlignCenter);

    spinnerLayout->addWidget(btnDayDec, 2, 0, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMonthDec, 2, 1, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnYearDec, 2, 2, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnHourDec, 2, 3, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMinuteDec, 2, 4, 1, 1, Qt::AlignCenter);

    connect(numBxDay, SIGNAL(editingFinished()), this, SLOT(setDay()));
    connect(numBxMonth, SIGNAL(editingFinished()), this, SLOT(setMonth()));
    connect(numBxYear, SIGNAL(editingFinished()), this, SLOT(setYear()));
    connect(numBxHour, SIGNAL(editingFinished()), this, SLOT(setHour()));
    connect(numBxMinute, SIGNAL(editingFinished()), this, SLOT(setMinute()));

    connect(btnDayInc, SIGNAL(clicked()), this, SLOT(increaseDay()));
    connect(btnMonthInc, SIGNAL(clicked()), this, SLOT(increaseMonth()));
    connect(btnYearInc, SIGNAL(clicked()), this, SLOT(increaseYear()));
    connect(btnHourInc, SIGNAL(clicked()), this, SLOT(increaseHour()));
    connect(btnMinuteInc, SIGNAL(clicked()), this, SLOT(increaseMinute()));

    connect(btnDayDec, SIGNAL(clicked()), this, SLOT(decreaseDay()));
    connect(btnMonthDec, SIGNAL(clicked()), this, SLOT(decreaseMonth()));
    connect(btnYearDec, SIGNAL(clicked()), this, SLOT(decreaseYear()));
    connect(btnHourDec, SIGNAL(clicked()), this, SLOT(decreaseHour()));
    connect(btnMinuteDec, SIGNAL(clicked()), this, SLOT(decreaseMinute()));

    this->setLayout(spinnerLayout);
    this->setMaximumHeight(150);

}

// PRIVATE SLOTS
void DateTimeSpinner::increaseDay(){
    currentTime = currentTime.addDays(1);
    update();
}

void DateTimeSpinner::decreaseDay(){
    currentTime = currentTime.addDays(-1);
    update();
}

void DateTimeSpinner::increaseMonth(){
    currentTime = currentTime.addMonths(1);
    update();
}

void DateTimeSpinner::decreaseMonth(){
    currentTime = currentTime.addMonths(-1);
    update();
}

void DateTimeSpinner::increaseYear(){
    currentTime = currentTime.addYears(1);
    update();
}

void DateTimeSpinner::decreaseYear(){
    currentTime = currentTime.addYears(-1);
    update();
}

void DateTimeSpinner::increaseHour(){
    currentTime = currentTime.addSecs(3600);
    update();
}

void DateTimeSpinner::decreaseHour(){
    currentTime = currentTime.addSecs(-3600);
    update();
}

void DateTimeSpinner::increaseMinute(){
    currentTime = currentTime.addSecs(60);
    update();
}

void DateTimeSpinner::decreaseMinute(){
    currentTime = currentTime.addSecs(-60);
    update();
}

void DateTimeSpinner::setDay(){
    currentTime.setDate(QDate(currentTime.date().year(), currentTime.date().month(), numBxDay->getValue()));;
    update();
}

void DateTimeSpinner::setMonth(){
    currentTime.setDate(QDate(currentTime.date().year(), numBxMonth->getValue(), currentTime.date().day()));;
    update();
}

void DateTimeSpinner::setYear(){
    currentTime.setDate(QDate(numBxYear->getValue(), currentTime.date().month(), currentTime.date().day()));;
    update();
}

void DateTimeSpinner::setHour(){
    currentTime.setTime(QTime(numBxHour->getValue(), currentTime.time().minute(), currentTime.time().second(), currentTime.time().msec()));
    update();
}

void DateTimeSpinner::setMinute(){
    currentTime.setTime(QTime(currentTime.time().hour(), numBxMinute->getValue(), currentTime.time().second(), currentTime.time().msec()));
    update();
}

// PUBLIC
QDateTime DateTimeSpinner::getDateTime() const{
    return currentTime;
}

void DateTimeSpinner::setDateTime(const QDateTime& time){
    currentTime.setDate(time.date());
    currentTime.setTime(time.time());
    update();
}

void DateTimeSpinner::update(){
    numBxDay->setValue(currentTime.date().day());
    numBxMonth->setValue(currentTime.date().month());
    numBxYear->setValue(currentTime.date().year());
    numBxHour->setValue(currentTime.time().hour());
    numBxMinute->setValue(currentTime.time().minute());
}

