#ifndef DATETIMESPINNER_H
#define DATETIMESPINNER_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDateTime>
#include "numberlineedit.h"

class DateTimeSpinner : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimeSpinner(QWidget *parent = 0);

    QDateTime getDateTime() const;
signals:

public slots:

private slots:

    void increaseDay();
    void decreaseDay();
    void increaseMonth();
    void decreaseMonth();
    void increaseYear();
    void decreaseYear();
    void increaseHour();
    void decreaseHour();
    void increaseMinute();
    void decreaseMinute();

private:
    QGridLayout *spinnerLayout;

    NumberLineEdit *numBxDay;
    NumberLineEdit *numBxMonth;
    NumberLineEdit *numBxYear;
    NumberLineEdit *numBxHour;
    NumberLineEdit *numBxMinute;

    QPushButton *btnDayInc;
    QPushButton *btnDayDec;
    QPushButton *btnMonthInc;
    QPushButton *btnMonthDec;
    QPushButton *btnYearInc;
    QPushButton *btnYearDec;
    QPushButton *btnHourInc;
    QPushButton *btnHourDec;
    QPushButton *btnMinuteInc;
    QPushButton *btnMinuteDec;

    QDateTime currentTime;

    void update();
};

#endif // DATETIMESPINNER_H
