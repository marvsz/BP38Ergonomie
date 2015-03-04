#ifndef MINIMIZEDTIMERVIEW_H
#define MINIMIZEDTIMERVIEW_H

#include <QWidget>

#include <QLabel>
#include <QPushButton>
#include <QTime>
#include "workprocesstypepicker.h"
#include "workprocessselector.h"
#include "../../enum.h"

class MinimizedTimerView : public QWidget
{
    Q_OBJECT
public:
    explicit MinimizedTimerView(TimerState state = TimerState::IDLE, QWidget *parent = 0);
    ~MinimizedTimerView();

    AVType getWorkprocessType() const;
    TimerState getState() const;
    QTime getTime() const;

signals:
    void nextWorkProcess();
    void previousWorkProcess();
    void workProcessTypeChanged(AVType type);
    void maximize();
    void play();
    void pause();

public slots:
    void setState(TimerState state);
    void setTime(const QTime &time);
    void setSelectedAV(int id);
    void setSelectedAVNone();
    void setHasPreviousAV(bool hasPrevious);
    void setHasNextAV(bool hasNext);
    void setWorkProcessType(AVType type, const QString &prefix);

private slots:

    void btnPlayPausedClicked();

private:
    TimerState state;

    QLabel *lblTime;

    QPushButton *btnMaximized;
    QPushButton *btnPlayPaused;

    WorkProcessSelector *wpSelector;

    WorkProcessTypePicker *wpTypePicker;
};

#endif // MINIMIZEDTIMERVIEW_H
