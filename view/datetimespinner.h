#ifndef DATETIMESPINNER_H
#define DATETIMESPINNER_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDateTime>
#include "numberlineedit.h"
#include "iconconstants.h"
#include <QIcon>

class DateTimeSpinner : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimeSpinner(QWidget *parent = 0);

    QDateTime getDateTime() const;
    void setDateTime(const QDateTime& time);

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

    void setDay();
    void setMonth();
    void setYear();
    void setHour();
    void setMinute();

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

    QIcon iconPlus;
    QIcon iconMinus;

    void update();
};

#endif // DATETIMESPINNER_H
