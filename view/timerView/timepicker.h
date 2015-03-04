#ifndef TIMEPICKER_H
#define TIMEPICKER_H

#include <QWidget>
#include <QTime>
#include <QPushButton>
#include "../timelineedit.h"

class TimePicker : public QWidget
{
    Q_OBJECT
public:
    explicit TimePicker(QWidget *parent = 0);
    ~TimePicker();

    QTime getTime() const;
    void setTime(const QTime &time);

signals:
    void timeChanged(const QTime &time);

private slots:
    void increaseTime();
    void decreaseTime();
    void emitTimeChanged();

private:
    TimeLineEdit *timeBxTime;
    QPushButton *btnIncreaseTime;
    QPushButton *btnDecreaseTime;

};

#endif // TIMEPICKER_H
