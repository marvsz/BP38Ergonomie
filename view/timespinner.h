#ifndef TIMESPINNER_H
#define TIMESPINNER_H

#include <QWidget>
#include <QTime>
#include <QGridLayout>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "numberlineedit.h"
#include "timelineedit.h"

class TimeSpinner : public QWidget
{
    Q_OBJECT
public:
    explicit TimeSpinner(QWidget *parent = 0);

    QTime getTime() const;
    void setTime(const QTime &time);

private:
    QGridLayout *spinnerLayout;

    TimeLineEdit *timeBxTime;

    QPushButton *btnHourInc;
    QPushButton *btnHourDec;
    QPushButton *btnMinuteInc;
    QPushButton *btnMinuteDec;

    QTime currentTime;

    void update();

};

#endif // TIMESPINNER_H
