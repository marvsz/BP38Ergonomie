#ifndef MAXIMIZEDTIMERVIEW_H
#define MAXIMIZEDTIMERVIEW_H

#include <QWidget>
#include <QTime>
#include "enum.h"
#include "workprocessselector.h"
#include "optionselectioncontrol.h"
#include "graphtimer.h"
#include "timepicker.h"

class MaximizedTimerView : public QWidget
{
    Q_OBJECT
public:
    explicit MaximizedTimerView(TimerState state = TimerState::IDLE, QWidget *parent = 0);
    ~MaximizedTimerView();

    QTime getDuration() const;
    QString getWorkprocessType() const;
    TimerState getState() const;
    QTime getTime() const;

signals:
    void nextWorkProcess();
    void previousWorkProcess();
    void workProcessTypeChanged(int type);
    void durationIncreased();
    void durationDecreased();
    void minimize();
    void maximize();
    void showGantView();
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
    void btnPlayPausedClicked();
    void btnStopResetClicked();
    void emitBothSet();

private:
    TimerState state;

    QLabel *lblTime;

    QPushButton *btnMinimized;
    QPushButton *btnMaximized;
    QPushButton *btnPlayPaused;
    QPushButton *btnStopReset;

    QPushButton *btnSetLeft;
    QPushButton *btnSetRight;
    QPushButton *btnSetBoth;
    QPushButton *btnSetAV;

    TimePicker *timePicker;
    WorkProcessSelector *wpSelector;

    static const QVector<QString> wpTypes;
    OptionSelectionControl *oscWorkProcessType;

    GraphTimer *graphTimer;

    QIcon playIcon;
    QIcon recordIcon;
    QIcon pauseIcon;
    QIcon stopIcon;
    QIcon resetIcon;
    QIcon minimizedIcon;
    QIcon maximizedIcon;

};

#endif // MAXIMIZEDTIMERVIEW_H
