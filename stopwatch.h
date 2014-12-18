#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QLineEdit>

#include <selectablevaluebutton.h>
#include <buttontimelineview.h>
#include <graphtimelineview.h>
#include <avrecordcontrol.h>


class StopWatch : public QMainWindow
{
    Q_OBJECT
public:
    explicit StopWatch(QWidget *parent = 0);

      ButtonTimelineView *btnView;

private slots:
    void btnStartPauseClicked();
    void btnStopResetClicked();
    void btnSelAVClicked();
    void btnAVClicked();
    void btnAVLeftClicked();
    void btnAVRightClicked();
    void btnPlusClicked();
    void btnMinusClicked();
    void btnNextAVClicked();
    void btnPrevAVClicked();
    void getButtonView();
    void btnMinimizeClicked();
    void btnMaximizeClicked();

protected:
    void timerEvent(QTimerEvent *);

private:
    bool running;
    bool timerStarted;
    bool windowMinimized;
    int counter;

    QLabel *timerTitle;
    QLabel *timer;
    QLineEdit *avTime;
    QDateTime startTime;
    QDateTime currentAVTime;
    qint64 totalTime;
    qint64 sessionTime;

    GraphTimelineView *graphView;
    AVRecordControl *avControl;

    QPushButton *btnSelAV;
    QPushButton *btnAV;
    QPushButton *btnAVLeft;
    QPushButton *btnAVRight;
    QPushButton *btnPlus;
    QPushButton *btnMinus;
    QPushButton *btnNextAV;
    QPushButton *btnPrevAV;
    QPushButton *btnStartPause;
    QPushButton *btnStopReset;
    QPushButton *btnMinimize;
    QPushButton *btnMaximize;

    QVector<SelectableValueButton*> *leftAVButtons;
    QVector<SelectableValueButton*> *rightAVButtons;
    QVector<SelectableValueButton*> *avButtons;

    QHBoxLayout *minimizedLayout;
    QHBoxLayout *mainLayout;
    QVBoxLayout *mainTimerLayout;
    QVBoxLayout *timerBtnLayout;
    QVBoxLayout *mainAVLayout;
    QHBoxLayout *avSelLayout;
    QHBoxLayout *avTimeLayout;
    QHBoxLayout *avLeftRightLayout;
    QHBoxLayout *timerBtnLayout2;
    QWidget *main;
    QWidget *mini;

    static const QString qssSelected;
    static const QString qssNotSelected;
};

#endif // STOPWATCH_H
