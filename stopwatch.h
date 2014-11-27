#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QLineEdit>
#include <QStringList>


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
    void btnPlusClicked();
    void btnMinusClicked();
    void btnNextAVClicked();
    void btnPrevAVClicked();


protected:
    void timerEvent(QTimerEvent *);


private:
    bool running;
    bool timerStarted;
    int totalAV;
    int currentAV;
    QLabel *timer;
    QLineEdit *avTime;
    QDateTime startTime;
    QDateTime currentAVTime;
    QStringList *lstAV;
    QPushButton *btnAV;
    QPushButton *btnPlus;
    QPushButton *btnMinus;
    QPushButton *btnNextAV;
    QPushButton *btnPrevAV;
    QPushButton *btnStartPause;
    QPushButton *btnReset;
    QPushButton *btnSetAv;
    qint64 totalTime;
    qint64 sessionTime;
};

#endif // STOPWATCH_H
