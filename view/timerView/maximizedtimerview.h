#ifndef MAXIMIZEDTIMERVIEW_H
#define MAXIMIZEDTIMERVIEW_H

#include <QWidget>
#include <QTime>
#include "enum.h"
#include "workprocessselector.h"
#include "../optionselectioncontrol.h"
#include "graphtimelineview.h"
#include "timepicker.h"
#include "../selectablevaluebutton.h"
#include "workprocesstypepicker.h"

class MaximizedTimerView : public QWidget
{
    Q_OBJECT
public:
    explicit MaximizedTimerView(TimerState state = TimerState::IDLE, QWidget *parent = 0);
    ~MaximizedTimerView();

    QTime getDuration() const;
    AVType getWorkprocessType() const;
    TimerState getState() const;
    QTime getTime() const;

signals:
    void nextWorkProcess();
    void previousWorkProcess();
    void workProcessTypeChanged(AVType type);
    void durationIncreased();
    void durationDecreased();
    void minimize();
    void maximize();
    void play();
    void pause();
    void stop();
    void reset();
    void leftSet();
    void rightSet();
    void avSet();
    void durationChanged(const QTime &duration);

    void leftChanged(bool b);
    void rightChanged(bool b);

public slots:
    void setState(TimerState state);
    void setTime(const QTime &time);
    void setSelectedAV(int id, const QTime &duration);
    void setWorkProcessType(AVType type, const QString &prefix);
    void setSelectedAVNone();
    void setHasPreviousAV(bool hasPrevious);
    void setHasNextAV(bool hasNext);

    void leftStarted(const QTime &startTime);
    void leftEnded(const QTime &endTime);
    void rightStarted(const QTime &startTime);
    void rightEnded(const QTime &endTime);
    void basicStarted(const QTime &startTime);
    void basicEnded(const QTime &endTime);
    void initialize(QVector<QVariant> *leftWPs, QVector<QVariant> *rightWPs, QVector<QVariant> *basicWPs);
    void updateGraphTimeLine(const QTime &currentTime);
    void leaveTimer();

    void disableMaximize();
    void enableMaximize();

private slots:
    void btnPlayPausedClicked();
    void btnStopResetClicked();
    void emitBothSet();

    void btnLeftClicked();
    void btnRightClicked();
    void btnBothClicked();
    void btnAVClicked();

private:
    TimerState state;

    QLabel *lblTime;

    QPushButton *btnMinimized;
    QPushButton *btnMaximized;
    QPushButton *btnPlayPaused;
    QPushButton *btnStopReset;

    SelectableValueButton *btnSetLeft;
    SelectableValueButton *btnSetRight;
    SelectableValueButton *btnSetBoth;
    QPushButton *btnSetAV;

    TimePicker *timePicker;
    WorkProcessSelector *wpSelector;

    WorkProcessTypePicker *wpTypePicker;

    GraphTimelineView *graphTimer;
};

#endif // MAXIMIZEDTIMERVIEW_H
