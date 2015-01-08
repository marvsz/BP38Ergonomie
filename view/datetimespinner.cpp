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
    btnDayInc(new QPushButton("+")),
    btnDayDec(new QPushButton("-")),
    btnMonthInc(new QPushButton("+")),
    btnMonthDec(new QPushButton("-")),
    btnYearInc(new QPushButton("+")),
    btnYearDec(new QPushButton("-")),
    btnHourInc(new QPushButton("+")),
    btnHourDec(new QPushButton("-")),
    btnMinuteInc(new QPushButton("+")),
    btnMinuteDec(new QPushButton("-"))
{
    currentTime = QDateTime::currentDateTime();
    qDebug() << currentTime.toUTC().toString("ddmmyy hhmm");

    numBxDay->setValue(currentTime.date().day());
    numBxMonth->setValue(currentTime.date().month());
    numBxYear->setValue(currentTime.date().year());
    numBxHour->setValue(currentTime.time().hour());
    numBxMinute->setValue(currentTime.time().minute());

    spinnerLayout->addWidget(btnDayInc, 0, 0, 1, 1, 0);
    spinnerLayout->addWidget(btnMonthInc, 0, 1, 1, 1, 0);
    spinnerLayout->addWidget(btnYearInc, 0, 2, 1, 1, 0);
    spinnerLayout->addWidget(btnHourInc, 0, 3, 1, 1, 0);
    spinnerLayout->addWidget(btnMinuteInc, 0, 4, 1, 1, 0);

    spinnerLayout->addWidget(numBxDay, 1, 0, 1, 1, 0);
    spinnerLayout->addWidget(numBxMonth, 1, 1, 1, 1, 0);
    spinnerLayout->addWidget(numBxYear, 1, 2, 1, 1, 0);
    spinnerLayout->addWidget(numBxHour, 1, 3, 1, 1, 0);
    spinnerLayout->addWidget(numBxMinute, 1, 4, 1, 1, 0);

    spinnerLayout->addWidget(btnDayDec, 2, 0, 1, 1, 0);
    spinnerLayout->addWidget(btnMonthDec, 2, 1, 1, 1, 0);
    spinnerLayout->addWidget(btnYearDec, 2, 2, 1, 1, 0);
    spinnerLayout->addWidget(btnHourDec, 2, 3, 1, 1, 0);
    spinnerLayout->addWidget(btnHourDec, 2, 4, 1, 1, 0);

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

}

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
    currentTime = currentTime.addYears(-11);
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

QDateTime DateTimeSpinner::getDateTime() const{
    return currentTime;
}

void DateTimeSpinner::update(){
    numBxDay->setValue(currentTime.date().day());
    numBxMonth->setValue(currentTime.date().month());
    numBxYear->setValue(currentTime.date().year());
    numBxHour->setValue(currentTime.time().hour());
    numBxMinute->setValue(currentTime.time().minute());
}

