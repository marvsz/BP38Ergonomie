#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>

#include <selectablevaluebutton.h>
#include <buttontimelineview.h>
#include <avrecordcontrol.h>
#include <separator.h>

class StopWatch : public QMainWindow
{
    Q_OBJECT
public:
    explicit StopWatch(QWidget *parent = 0);

      ButtonTimelineView *btnView;

private slots:
    void btnStartPauseClicked();
    void btnStopResetClicked();
    void getButtonView();
    void btnMinimizeClicked();
    void btnMaximizeClicked();

protected:
    void timerEvent(QTimerEvent *);

private:
    bool running;
    bool timerStarted;
    bool standardView;
    int counter;
    int currentLeftAV;
    int currentRightAV;
    int currentLeftTime;
    int currentRightTime;

    QLabel *timerTitle;
    QLabel *timer;
    QDateTime startTime;
    QDateTime currentAVTime;
    qint64 totalTime;
    qint64 sessionTime;

    AVRecordControl *avControl;

    QPushButton *btnStartPause;
    QPushButton *btnStopReset;
    QPushButton *btnMinimize;
    QPushButton *btnMaximize;

    QVector<SelectableValueButton*> *leftAVButtons;
    QVector<SelectableValueButton*> *rightAVButtons;
    QVector<SelectableValueButton*> *avButtons;

    QHBoxLayout *minimizedLayout;
    QVBoxLayout *mainVLayout;
    QHBoxLayout *mainHLayout;
    QVBoxLayout *mainTimerLayout;
    QVBoxLayout *timerBtnLayout;
    QVBoxLayout *mainAVLayout;
    QHBoxLayout *avSelLayout;
    QHBoxLayout *avTimeLayout;
    QHBoxLayout *avLeftRightLayout;
    QHBoxLayout *timerBtnLayout2;
    QVBoxLayout *sizeLayout;
    Separator *separator;

    QWidget *main;
    QWidget *mini;

    static const QString qssSelected;
    static const QString qssNotSelected;
};

#endif // STOPWATCH_H
