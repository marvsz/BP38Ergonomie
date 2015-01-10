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
    void durationChanged(const QTime &duration);
    void createWorkProcess(int type, const QTime &startTime, const QTime &endTime);
    void resetWorkProcesses();

public slots:
    void setSelectedAV(int id);

protected:
    void timerEvent(QTimerEvent *event);

private slots:

    void minimizeView();
    void maximizeView();
    void startTimer();
    void pauseTimer();
    void stopTimer();
    void resetTimer();
    void setTime(const QTime &time);
    void setWorkProcessType(int id, const QString &prefix);

    void createLeftWorkProcessRequested();
    void createRightWorkProcessRequested();
    void createBasicWorkProcessRequested();

    void changeLeft(bool b);
    void changeRight(bool b);

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
