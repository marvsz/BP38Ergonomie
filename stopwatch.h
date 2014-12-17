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
      //QHBoxLayout *minimizedLayout;
      //QHBoxLayout *mainLayout;

private slots:
    void btnStartPauseClicked();
    void btnStopResetClicked();
    void btnSetAVClicked();
    void btnSelAVClicked();
    void btnAVClicked();
    void btnAVLeftClicked();
    void btnAVRightClicked();
    void btnPlusClicked();
    void btnMinusClicked();
    void btnNextAVClicked();
    void btnPrevAVClicked();
    void updateGraph();
    void updateAVs();
    void btnSetLeftClicked();
    void btnSetRightClicked();
    int getTime(int currentAV);
    int getLeftRightTime(int currentAV, QString leftright);
    void getButtonView();
    void btnBothAVClicked();

    void btnMinimizeClicked();
    void btnMaximizeClicked();


protected:
    void timerEvent(QTimerEvent *);


private:
    bool running;
    bool timerStarted;
    int totalAV;
    int totalLeftAV;
    int totalRightAV;
    int currentAV;
    int currentLeftAV;
    int currentRightAV;
    QLabel *timerTitle;
    QLabel *timer;
    QLineEdit *avTime;
    QDateTime startTime;
    QDateTime currentAVTime;
    QStringList *lstAV;
    QList<int> *lstAVTime;
    QList<int> *lstLeftAVTime;
    QList<int> *lstRightAVTime;
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
    qint64 totalTime;
    qint64 sessionTime;
    QLabel *graph;
    QPicture picture;
    QPainter painter;
    QStringList *lstLeftAVs;
    QStringList *lstRightAVs;

    QScrollArea *graphArea;

    QVector<SelectableValueButton*> *leftAVButtons;
    QVector<SelectableValueButton*> *rightAVButtons;
    QVector<SelectableValueButton*> *avButtons;
    bool stopped;
    bool windowMinimized;

    //QWidget *main;
    //QWidget *mini;

    QPushButton *btnSaveGraph;

    QPushButton *btnMinimize;
    QPushButton *btnMaximize;

    int paintX;
    int counter;
    bool leftPressed;
    bool rightPressed;
    bool avPressed;

    static const QString qssSelected;
    static const QString qssNotSelected;

    bool leftSelected;
    bool rightSelected;
    bool avSelected;

};

#endif // STOPWATCH_H
