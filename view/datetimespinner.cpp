#include "datetimespinner.h"
#include <QDebug>
#include <QLabel>

DateTimeSpinner::DateTimeSpinner(QWidget *parent) :
    QWidget(parent),
    spinnerLayout(new QGridLayout),
    dateBxDate(new DateLineEdit()),
    timeBxTime(new TimeLineEdit(this, TimeLineType::HOUR_MINUTE)),
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

    dateBxDate->setMaximumWidth(120);
    dateBxDate->setAlignment(Qt::AlignCenter);

    timeBxTime->setMaximumWidth(80);
    timeBxTime->setAlignment(Qt::AlignCenter);

    connect(timeBxTime, SIGNAL(dayIncreased()), dateBxDate, SLOT(increaseDay()));
    connect(timeBxTime, SIGNAL(dayDecreased()), dateBxDate, SLOT(decreaseDay()));

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

    spinnerLayout->setContentsMargins(0,0,0,0);
    spinnerLayout->setSpacing(0);

    spinnerLayout->addWidget(new QLabel(tr("Date")),0, 0, 1, 3, Qt::AlignCenter);
    spinnerLayout->addWidget(new QLabel(tr("Time")),0, 4, 1, 2, Qt::AlignCenter);

    spinnerLayout->addWidget(btnDayInc, 1, 0, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMonthInc, 1, 1, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnYearInc, 1, 2, 1, 1, Qt::AlignCenter);
    spinnerLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 3, 1, 1);
    spinnerLayout->addWidget(btnHourInc, 1, 4, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMinuteInc, 1, 5, 1, 1, Qt::AlignCenter);

    spinnerLayout->addWidget(dateBxDate, 2, 0, 1, 3, Qt::AlignCenter);
    spinnerLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 2, 3, 1, 1);
    spinnerLayout->addWidget(timeBxTime, 2, 4, 1, 2, Qt::AlignCenter);

    spinnerLayout->addWidget(btnDayDec, 3, 0, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMonthDec, 3, 1, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnYearDec, 3, 2, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnHourDec, 3, 4, 1, 1, Qt::AlignCenter);
    spinnerLayout->addWidget(btnMinuteDec, 3, 5, 1, 1, Qt::AlignCenter);

    connect(btnDayInc, SIGNAL(clicked()), dateBxDate, SLOT(increaseDay()));
    connect(btnMonthInc, SIGNAL(clicked()), dateBxDate, SLOT(increaseMonth()));
    connect(btnYearInc, SIGNAL(clicked()), dateBxDate, SLOT(increaseYear()));
    connect(btnHourInc, SIGNAL(clicked()), timeBxTime, SLOT(increaseHour()));
    connect(btnMinuteInc, SIGNAL(clicked()), timeBxTime, SLOT(increaseMinute()));

    connect(btnDayDec, SIGNAL(clicked()), dateBxDate, SLOT(decreaseDay()));
    connect(btnMonthDec, SIGNAL(clicked()), dateBxDate, SLOT(decreaseMonth()));
    connect(btnYearDec, SIGNAL(clicked()), dateBxDate, SLOT(decreaseYear()));
    connect(btnHourDec, SIGNAL(clicked()), timeBxTime, SLOT(decreaseHour()));
    connect(btnMinuteDec, SIGNAL(clicked()), timeBxTime, SLOT(decreaseMinute()));

    connect(timeBxTime, SIGNAL(timeChanged()), this, SIGNAL(dateTimechanged()));
    connect(dateBxDate, SIGNAL(dateChanged()), this, SIGNAL(dateTimechanged()));

    this->setLayout(spinnerLayout);
}

// PUBLIC
QDateTime DateTimeSpinner::getDateTime() const{
    return QDateTime(dateBxDate->getDate(), timeBxTime->getTime());
}

void DateTimeSpinner::setDateTime(const QDateTime &time){
    dateBxDate->setDate(time.date());
    timeBxTime->setTime(time.time());
}

