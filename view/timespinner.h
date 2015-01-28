#ifndef TIMESPINNER_H
#define TIMESPINNER_H

#include <QWidget>
#include <QTime>
#include <QGridLayout>
#include <QPushButton>
#include "numberlineedit.h"

class TimeSpinner : public QWidget
{
    Q_OBJECT
public:
    explicit TimeSpinner(QWidget *parent = 0);

    QTime getTime() const;
    void setTime(const QTime &time);

signals:

public slots:

private slots:
    void increaseHour();
    void decreaseHour();
    void increaseMinute();
    void decreaseMinute();

    void setHour();
    void setMinute();

private:
    QGridLayout *spinnerLayout;

    NumberLineEdit *numBxHour;
    NumberLineEdit *numBxMinute;

    QPushButton *btnHourInc;
    QPushButton *btnHourDec;
    QPushButton *btnMinuteInc;
    QPushButton *btnMinuteDec;

    QTime currentTime;

    void update();

};

#endif // TIMESPINNER_H
