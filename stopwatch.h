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


class StopWatch : public QWidget
{
    Q_OBJECT
public:
    explicit StopWatch(QWidget *parent = 0);

private slots:
    void btnStartPauseClicked();
    void btnResetClicked();
    void btnSetAVClicked();
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
    int getTime();


protected:
    void timerEvent(QTimerEvent *);


private:
    bool running;
    bool timerStarted;
    int totalAV;
    int totalLeftAV;
    int totalRightAV;
    int currentAV;
    QLabel *timer;
    QLineEdit *avTime;
    QDateTime startTime;
    QDateTime currentAVTime;
    QStringList *lstAV;
    QList<int> *lstAVTime;
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
    qint64 totalTime;
    qint64 sessionTime;
    QLabel *graph;
    QPicture picture;
    QPainter painter;
    QStringList *lstLeftAVs;
    QStringList *lstRightAVs;

    QScrollArea *graphArea;

    int paintX;
    int counter;
    bool leftPressed;
    bool rightPressed;
    bool avPressed;

    static const QString qssSelected;
    static const QString qssNotSelected;

};

#endif // STOPWATCH_H
