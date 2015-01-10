#ifndef TIMERVIEWCONTROLLER_H
#define TIMERVIEWCONTROLLER_H

#include <QWidget>
#include <QTime>
#include <QList>
#include "enum.h"
#include "minimizedtimerview.h"
#include "maximizedtimerview.h"
#include "ganttimerview.h"

class TimerViewController : public QWidget
{

    Q_OBJECT
public:
    explicit TimerViewController(QWidget *parent = 0);

signals:
    void showGantView();
    void hideGantView();

    void nextWorkProcess();
    void previousWorkProcess();
    void workProcessTypeChanged(int type);
    void play();
    void pause();
    void stop();
    void reset();
    void leftSet();
    void rightSet();
    void avSet();
    void durationChanged(const QTime &duration);


public slots:
    void setState(TimerState state);
    void setTime(const QTime &time);
    void setSelectedAV(int id);
    void setWorkProcessType(int id, const QString &prefix);

protected:
    void timerEvent(QTimerEvent *event);

private slots:

    void minimizeView();
    void maximizeView();
    void startTimer();
    void pauseTimer();
    void stopTimer();
    void resetTimer();

    void changeLeft(bool b);
    void changeRight(bool b);
    void changeBasic(bool b);

private:
    QList<bool> *listLeftAVs;
    QList<bool> *listRightAVs;
    QList<bool> *listBasicAVs;

    bool isLeftSet;
    bool isRightSet;
    bool isBasicSet;

    int timerID;

    QTime startTimeBasic;
    QTime startTimeLeft;
    QTime startTimeRight;
    QTime currentTime;

    TimerState timerState;
    TimerDisplayState displayState;
    MaximizedTimerView *maxTimerView;
    MinimizedTimerView *minTimerView;

    void syncTimerStates(TimerState state);

};

#endif // TIMERVIEWCONTROLLER_H
