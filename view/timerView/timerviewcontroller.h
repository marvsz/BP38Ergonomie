#ifndef TIMERVIEWCONTROLLER_H
#define TIMERVIEWCONTROLLER_H

#include <QWidget>
#include <QTime>
#include <QList>
#include "../../enum.h"
#include "../interfaces/iworkprocesscontroller.h"
#include "minimizedtimerview.h"
#include "maximizedtimerview.h"
#include "ganttimerview.h"

class TimerViewController : public QWidget, IWorkProcessController
{
    Q_OBJECT
    Q_INTERFACES(IWorkProcessController)
public:
    explicit TimerViewController(QWidget *parent = 0);

signals:
    void selectNextWorkProcess();
    void selectPreviousWorkProcess();
    void workProcessTypeChanged(AVType type);
    void workProcessDurationChanged(QTime duration);
    void createWorkProcess(QHash<QString, QVariant> values);
    void resetWorkProcesses();

    void showGantView();
    void hideGantView();
    void changingWorkProcess();

public slots:
    void setSelectedWorkProcess(QHash<QString, QVariant> values);
    void setHasPreviousWorkProcess(bool hasPrevious);
    void setHasNextWorkProcess(bool hasNext);
    void setSelectedWorkProcessType(AVType type);
    void initiliazedWorkProcesses(QList<QHash<QString, QVariant>> values);

    void closeTimerView();
    void gantViewShown();
    void gantViewHidden();

protected:
    void timerEvent(QTimerEvent *);

private slots:
    void setSelectedWorkprocessNone();

    void minimizeView();
    void maximizeView();
    void startTimer();
    void pauseTimer();
    void stopTimer();
    void resetTimer();
    void setTime(const QTime &time);
    void setWorkProcessType(AVType type, const QString &prefix);

    void createLeftWorkProcessRequested();
    void createRightWorkProcessRequested();
    void createBasicWorkProcessRequested();

    void selectPreviousWorkProcessClicked();
    void selectNextWorkProcessClicked();
    void changingWorkProcessTypeClicked(AVType type);

    void changeLeft(bool b);
    void changeRight(bool b);

private:
    bool isLeftSet;
    bool isRightSet;
    bool isBasicSet;

    bool isGantShown;

    int timerID;

    QTime startTimeBasic;
    QTime startTimeLeft;
    QTime startTimeRight;
    QTime currentTime;

    TimerState timerState;
    TimerDisplayState displayState;
    MaximizedTimerView *maxTimerView;
    MinimizedTimerView *minTimerView;

    const QStringList TYPE_PREFIXE = QStringList()<<"L"<<"R"<<"AV";

    void syncTimerStates(TimerState state);
    void syncCurrentTime(const QTime &currentTime);

};

#endif // TIMERVIEWCONTROLLER_H

