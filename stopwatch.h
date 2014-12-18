#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QLineEdit>
#include <QStringList>
#include <QPainter>
#include <QPicture>
#include <QScrollArea>

#include <selectablevaluebutton.h>
#include <buttontimelineview.h>


class StopWatch : public QMainWindow
{
    Q_OBJECT
public:
    explicit StopWatch(QWidget *parent = 0);

      ButtonTimelineView *btnView;

private slots:
    void btnStartPauseClicked();
    void btnStopResetClicked();
    void btnSetAVClicked();
    void btnSetLeftClicked();
    void btnSetRightClicked();
    void btnSelAVClicked();
    void btnAVClicked();
    void btnAVLeftClicked();
    void btnAVRightClicked();
    void btnBothAVClicked();
    void btnPlusClicked();
    void btnMinusClicked();
    void btnNextAVClicked();
    void btnPrevAVClicked();
    void updateGraph();
    void updateAVs();
    int getTime(int currentAV);
    int getLeftRightTime(int currentAV, QString leftright);
    void getButtonView();
    void btnMinimizeClicked();
    void btnMaximizeClicked();

protected:
    void timerEvent(QTimerEvent *);

private:
    bool running;
    bool timerStarted;
    bool stopped;
    bool windowMinimized;
    bool leftPressed;
    bool rightPressed;
    bool avPressed;
    bool leftSelected;
    bool rightSelected;
    bool avSelected;

    int totalAV;
    int totalLeftAV;
    int totalRightAV;
    int currentAV;
    int currentLeftAV;
    int currentRightAV;
    int paintX;
    int counter;

    QLabel *timerTitle;
    QLabel *timer;
    QLineEdit *avTime;
    QDateTime startTime;
    QDateTime currentAVTime;
    QStringList *lstAV;
    QStringList *lstLeftAVs;
    QStringList *lstRightAVs;
    QList<int> *lstAVTime;
    QList<int> *lstLeftAVTime;
    QList<int> *lstRightAVTime;
    qint64 totalTime;
    qint64 sessionTime;
    QLabel *graph;
    QPicture picture;
    QPainter painter;
    QScrollArea *graphArea;

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
    QPushButton *btnSetAv;
    QPushButton *btnSetLeft;
    QPushButton *btnSetRight;
    QPushButton *btnBothAV;  
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
    QVBoxLayout *avSetLayout;
    QHBoxLayout *timerBtnLayout2;
    QWidget *main;
    QWidget *mini;

    //QPushButton *btnSaveGraph;

    static const QString qssSelected;
    static const QString qssNotSelected;
};

#endif // STOPWATCH_H
