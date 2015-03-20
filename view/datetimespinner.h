#ifndef DATETIMESPINNER_H
#define DATETIMESPINNER_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QDateTime>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "timelineedit.h"
#include "datelineedit.h"

class DateTimeSpinner : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimeSpinner(QWidget *parent = 0);

    QDateTime getDateTime() const;
    void setDateTime(const QDateTime &time);

signals:
    void dateTimechanged();

private:
    QGridLayout *spinnerLayout;

    DateLineEdit *dateBxDate;
    TimeLineEdit *timeBxTime;

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
};

#endif // DATETIMESPINNER_H
