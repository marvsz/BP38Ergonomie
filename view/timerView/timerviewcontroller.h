#ifndef TIMERVIEWCONTROLLER_H
#define TIMERVIEWCONTROLLER_H

#include <QWidget>
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

private slots:
    void minimizeView();
    void maximizeView();

private:
    MaximizedTimerView *maxTimerView;
    MinimizedTimerView *minTimerView;
};

#endif // TIMERVIEWCONTROLLER_H
