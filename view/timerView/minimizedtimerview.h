#ifndef MINIMIZEDTIMERVIEW_H
#define MINIMIZEDTIMERVIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTime>
#include "optionselectioncontrol.h"
#include "workprocessselector.h"
#include "enum.h"

class MinimizedTimerView : public QWidget
{
    Q_OBJECT
public:
    explicit MinimizedTimerView(TimerState state = TimerState::IDLE, QWidget *parent = 0);
    ~MinimizedTimerView();

signals:
    void nextWorkProcess();
    void previousWorkProcess();
    void workProcessTypeChanged(int type);
    void maximize();
    void play();
    void pause();

public slots:
    void setState(TimerState state);
    void setTime(const QTime &time);
    void setSelectedAV(int id);
    void setWorkProcessType(int id, const QString &prefix);

private slots:
    void btnPlayPausedClicked();

private:
    TimerState state;

    QLabel *lblTime;

    QPushButton *btnMaximized;
    QPushButton *btnPlayPaused;

    WorkProcessSelector *wpSelector;

    static const QVector<QString> wpTypes;
    QIcon playIcon;
    QIcon recordIcon;
    QIcon pauseIcon;
    QIcon maximizedIcon;

    OptionSelectionControl *oscWorkProcessType;
};

#endif // MINIMIZEDTIMERVIEW_H
