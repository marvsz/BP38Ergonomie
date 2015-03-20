#ifndef TIMELINEEDIT_H
#define TIMELINEEDIT_H
#include <QTime>
#include <QRegularExpression>
#include "../enum.h"
#include "textlineedit.h"

class TimeLineEdit : public TextLineEdit
{
    Q_OBJECT
public:
    explicit TimeLineEdit(QWidget *parent = 0, TimeLineType type = TimeLineType::MINUTE_SECOND);

    QTime getTime() const;
    void setTime(const QTime &time);

signals:
    void dayIncreased();
    void dayDecreased();

    void timeChanged();

public slots:
    void increaseHour();
    void decreaseHour();
    void increaseMinute();
    void decreaseMinute();

private slots:
    void updateText();
    void updateTime();

private:

    static const QRegularExpression regExMS;
    static const QRegularExpression regExHM;
    static const QRegularExpression regExHMS;

    QTime currentTime;
    TimeLineType type;
};

#endif // TIMELINEEDIT_H
