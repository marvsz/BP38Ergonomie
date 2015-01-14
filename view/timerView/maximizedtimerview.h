#ifndef MAXIMIZEDTIMERVIEW_H
#define MAXIMIZEDTIMERVIEW_H

#include <QWidget>
#include <QTime>
#include "../enum.h"

#include "workprocessselector.h"
#include "optionselectioncontrol.h"
#include "graphtimelineview.h"
#include "timepicker.h"
#include "selectablevaluebutton.h"

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

    void leftChanged(bool b);
    void rightChanged(bool b);

public slots:
    void setState(TimerState state);
    void setTime(const QTime &time);
    void setSelectedAV(int id);
    void setWorkProcessType(int id, const QString &prefix);
    void updateGraph(QList<bool> *lstAV, QList<bool> *lstLeftAVs, QList<bool> *lstRightAVs);
    void setWorkProcessLists(QVector<QVariant> *leftWPs, QVector<QVariant> *rightWPs, QVector<QVariant> *basicWPs);

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

    static const QStringList wpTypes;
    OptionSelectionControl *oscWorkProcessType;

    GraphTimelineView *graphTimer;
};

#endif // MAXIMIZEDTIMERVIEW_H
