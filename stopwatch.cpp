#include "stopwatch.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QTimerEvent>
#include <QDebug>

StopWatch::StopWatch(QWidget *parent) : QWidget(parent)
  , running(false)
  , timerStarted(false)
  , totalAV(0)
  , currentAV(0)
  , startTime()
  , currentAVTime()
  , timer(new QLabel("00:00"))
  , avTime(new QLineEdit("00:00"))
  , totalTime(0)
  , lstAV(new QStringList)
  , btnAV(new QPushButton("leer"))
  , btnPlus(new QPushButton("+"))
  , btnMinus(new QPushButton("-"))
  , btnNextAV(new QPushButton(">"))
  , btnPrevAV(new QPushButton("<"))
  , btnStartPause(new QPushButton("Start"))
  , btnReset(new QPushButton("Reset"))
  , btnSetAv(new QPushButton("AV setzen"))
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *mainTimerLayout = new QVBoxLayout();
    QHBoxLayout *timerBtnLayout = new QHBoxLayout();
    QVBoxLayout *mainAVLayout = new QVBoxLayout();
    QHBoxLayout *avSelLayout = new QHBoxLayout();
    QHBoxLayout *avTimeLayout = new QHBoxLayout();

    avSelLayout->addWidget(btnPrevAV);
    avSelLayout->addWidget(btnAV);
    avSelLayout->addWidget(btnNextAV);
    avTimeLayout->addWidget(btnMinus);
    avTimeLayout->addWidget(avTime);
    avTimeLayout->addWidget(btnPlus);
    mainAVLayout->addLayout(avSelLayout);
    mainAVLayout->addLayout(avTimeLayout);

    timerBtnLayout->addWidget(btnStartPause);
    timerBtnLayout->addWidget(btnReset);
    mainTimerLayout->addLayout(timerBtnLayout);
    mainTimerLayout->addWidget(timer);
    mainTimerLayout->addWidget(btnSetAv);
    mainTimerLayout->setAlignment(timer, Qt::AlignCenter);

    mainLayout->addLayout(mainAVLayout);
    mainLayout->addLayout(mainTimerLayout);
    mainLayout->setAlignment(mainTimerLayout, Qt::AlignRight);

    btnPlus->setFixedSize(60,60);
    btnMinus->setFixedSize(60,60);
    btnNextAV->setFixedSize(60,60);
    btnPrevAV->setFixedSize(60,60);
    btnStartPause->setFixedSize(200,60);
    btnReset->setFixedSize(200,60);
    btnSetAv->setFixedSize(400,60);
    btnAV->setFixedSize(200,60);


    avTime->setFixedSize(140,60);
    avTime->setInputMask("00:99");


    startTimer(0);
    lstAV->clear();
    btnStartPause->setEnabled(true);
    btnReset->setEnabled(false);
    btnSetAv->setEnabled(false);

    btnAV->setEnabled(false);
    avTime->setEnabled(false);
    btnPlus->setEnabled(false);
    btnMinus->setEnabled(false);
    btnNextAV->setEnabled(false);
    btnPrevAV->setEnabled(false);


    connect(btnStartPause, SIGNAL(clicked()), SLOT(btnStartPauseClicked()));
    connect(btnReset, SIGNAL(clicked()), SLOT(btnResetClicked()));
    connect(btnSetAv, SIGNAL(clicked()), SLOT(btnSetAVClicked()));
    connect(btnAV, SIGNAL(clicked()), SLOT(btnAVClicked()));
    connect(btnPlus, SIGNAL(clicked()), SLOT(btnPlusClicked()));
    connect(btnMinus, SIGNAL(clicked()), SLOT(btnMinusClicked()));
    connect(btnNextAV, SIGNAL(clicked()), SLOT(btnNextAVClicked()));
    connect(btnPrevAV, SIGNAL(clicked()), SLOT(btnPrevAVClicked()));
}

    void StopWatch::btnStartPauseClicked(){
        if(btnStartPause->text() != "Pause"){
            startTime = QDateTime::currentDateTime();
            running = true;
            timerStarted = true;
            btnStartPause->setText("Pause");
            btnReset->setEnabled(true);
            btnSetAv->setEnabled(true);
        }
        else {
            running = false;
            btnStartPause->setText("Weiter");
            timerEvent(new QTimerEvent(0));
            totalTime += sessionTime;
        }
        if(timerStarted)
            currentAVTime = startTime;
    }

    void StopWatch::btnResetClicked(){
        running = false;
        btnStartPause->setText("Start");
        btnReset->setEnabled(false);
        btnSetAv->setEnabled(false);
        totalTime = 0;
        sessionTime = 0;
        timer->setText("00:00");
    }

    void StopWatch::btnSetAVClicked(){
        totalAV++;
        currentAV = totalAV;


        QString str;
        str.append(QString("%1").arg(totalAV));
        btnAV->setText("AV " + str);

        QDateTime c = QDateTime::currentDateTime();
        qint64 t = currentAVTime.msecsTo(c);

        unsigned int h = t / 1000 / 60 / 60;
        unsigned int m = (t / 1000 / 60) - (h * 60);
        unsigned int s = (t / 1000) - ((m + (h * 60))* 60);
        const QString diff = QString("%1:%2")
        .arg(m, 2, 10, QChar('0'))
        .arg(s, 2, 10, QChar('0'));
        avTime->setText(diff);
        currentAVTime = c;

        btnAV->setEnabled(true);
        avTime->setEnabled(true);
        btnPlus->setEnabled(true);
        btnMinus->setEnabled(true);

        if(totalAV > 1)
            btnPrevAV->setEnabled(true);
        btnNextAV->setEnabled(false);

        lstAV->insert(totalAV -1, diff);
        //qDebug() <<lstAV->at(totalAV -1);

    }

    void StopWatch::btnAVClicked(){

    }

    void StopWatch::btnPlusClicked(){

    }

    void StopWatch::btnMinusClicked(){

    }

    void StopWatch::btnNextAVClicked(){
        currentAV++;
        QString s;
        s.append(QString("%1").arg(currentAV));
        btnAV->setText("AV " + s);
        btnPrevAV->setEnabled(true);
        if(currentAV  == totalAV)
            btnNextAV->setEnabled(false);
        avTime->setText(lstAV->at(currentAV -1));
    }

    void StopWatch::btnPrevAVClicked(){
        currentAV--;
        QString s;
        s.append(QString("%1").arg(currentAV));
        btnAV->setText("AV " + s);
        btnNextAV->setEnabled(true);
        if(currentAV == 1)
            btnPrevAV->setEnabled(false);
        avTime->setText(lstAV->at(currentAV -1));
    }


    void StopWatch::timerEvent(QTimerEvent *){
        if(running){
            sessionTime = startTime.msecsTo(QDateTime::currentDateTime());
            qint64 time = totalTime + sessionTime;
            unsigned int h = time / 1000 / 60 / 60;
            unsigned int m = (time / 1000 / 60) - (h * 60);
            unsigned int s = (time / 1000) - ((m + (h * 60))* 60);
            const QString diff = QString("%1:%2")
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
            timer->setText(diff);
        }
    }
