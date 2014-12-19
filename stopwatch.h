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
#include <graphtimelineview.h>

class StopWatch : public QMainWindow
{
    Q_OBJECT
public:
    explicit StopWatch(ButtonTimelineView *buttonView, QWidget *parent = 0);

      ButtonTimelineView *btnView;

signals:
    void leftAvPressed();
    void rightAvPressed();
    void avPressed();
    void minimizePressed();
    void maximizePressed();

private slots:
    void btnStartPauseClicked();
    void btnStopResetClicked();
    void updateButtonView();
    void btnMinimizeClicked();
    void btnMaximizeClicked();
    void selectLeftAV(int id);
    void selectRightAV(int id);
    void selectAV(int id);

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
    QVBoxLayout *avSetLayout;

    QWidget *main;
    QWidget *mini;

    GraphTimelineView *graphView;

    static const QString qssSelected;
    static const QString qssNotSelected;
};

#endif // STOPWATCH_H
