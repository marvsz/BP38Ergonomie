#include "stopwatch.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QTimerEvent>
#include <QDebug>
#include <QScrollArea>
#include <QScroller>
#include <QScrollBar>


StopWatch::StopWatch(QWidget *parent) : QWidget(parent)
  , running(false)
  , timerStarted(false)
  , totalAV(0)
  , totalLeftAV(0)
  , totalRightAV(0)
  , currentAV(0)
  , startTime()
  , currentAVTime()
  , timer(new QLabel("00:00"))
  , avTime(new QLineEdit("00:00"))
  , totalTime(0)
  , lstAV(new QStringList)
  , lstAVTime(new QList<int>)
  , btnAV(new QPushButton("leer"))
  , btnAVLeft(new QPushButton("Left"))
  , btnAVRight(new QPushButton("Right"))
  , btnPlus(new QPushButton("+"))
  , btnMinus(new QPushButton("-"))
  , btnNextAV(new QPushButton(">"))
  , btnPrevAV(new QPushButton("<"))
  , btnStartPause(new QPushButton())
  , btnStopReset(new QPushButton())
  , btnSetAv(new QPushButton("AV"))
  , btnSetLeft(new QPushButton("L"))
  , btnSetRight(new QPushButton("R"))
  , graph(new QLabel(""))
  , picture()
  , painter()
  , paintX(10)
  , counter(0)
  , leftPressed(false)
  , rightPressed(false)
  , lstLeftAVs(new QStringList)
  , lstRightAVs(new QStringList)
  , avPressed(false)
  , graphArea(new QScrollArea)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *mainTimerLayout = new QVBoxLayout();
    QHBoxLayout *timerBtnLayout = new QHBoxLayout();
    QVBoxLayout *mainAVLayout = new QVBoxLayout();
    QHBoxLayout *avSelLayout = new QHBoxLayout();
    QHBoxLayout *avTimeLayout = new QHBoxLayout();
    QHBoxLayout *avLeftRightLayout = new QHBoxLayout();
    QVBoxLayout *avSetLayout = new QVBoxLayout();

    QScroller::grabGesture(graphArea->viewport(), QScroller::LeftMouseButtonGesture);

    graphArea->setMaximumHeight(210);
    graphArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphArea->setWidget(graph);

    avLeftRightLayout->addWidget(btnAVLeft);
    avLeftRightLayout->addWidget(btnAVRight);
    avSelLayout->addWidget(btnPrevAV);
    avSelLayout->addWidget(btnAV);
    avSelLayout->addWidget(btnNextAV);
    avTimeLayout->addWidget(btnMinus);
    avTimeLayout->addWidget(avTime);
    avTimeLayout->addWidget(btnPlus);
    mainAVLayout->addLayout(avLeftRightLayout);
    mainAVLayout->addLayout(avSelLayout);
    mainAVLayout->addLayout(avTimeLayout);

    avSetLayout->addWidget(btnSetLeft);
    avSetLayout->addWidget(btnSetRight);
    avSetLayout->addWidget(btnSetAv);

    timerBtnLayout->addWidget(btnStartPause);
    timerBtnLayout->addWidget(btnStopReset);
    mainTimerLayout->addLayout(timerBtnLayout);
    mainTimerLayout->addWidget(timer);
    mainTimerLayout->setAlignment(timer, Qt::AlignCenter);

    mainLayout->addLayout(mainAVLayout);
    mainLayout->addWidget(graphArea);
    mainLayout->addLayout(avSetLayout);
    mainLayout->addLayout(mainTimerLayout);

    this->setMaximumHeight(225);

    btnPlus->setFixedSize(60,60);
    btnMinus->setFixedSize(60,60);
    btnNextAV->setFixedSize(60,60);
    btnPrevAV->setFixedSize(60,60);
    btnStartPause->setFixedSize(80,60);
    btnStopReset->setFixedSize(80,60);
    btnSetAv->setFixedSize(80,60);
    btnSetLeft->setFixedSize(80,60);
    btnSetRight->setFixedSize(80,60);
    btnAVLeft->setFixedSize(120, 60);
    btnAVRight->setFixedSize(120, 60);
    btnAV->setFixedSize(160, 60);
    avTime->setFixedSize(140,60);
    avTime->setInputMask("00:99");

    btnStartPause->setIcon(QIcon(":/timer/icons/Timer/start.png"));
    btnStartPause->setIconSize(QSize(40,40));
    btnStartPause->setToolTip("Start");
    btnStopReset->setIcon(QIcon(":/timer/icons/Timer/reset.png"));
    btnStopReset->setIconSize(QSize(40,40));
    btnStopReset->setToolTip("Reset");

    graph->setFixedHeight(200);

    timer->setStyleSheet("font: 36pt");

    startTimer(0);
    lstAV->clear();
    lstLeftAVs->clear();
    lstRightAVs->clear();
    btnStartPause->setEnabled(true);
    btnStopReset->setEnabled(false);
    btnSetAv->setEnabled(false);
    btnAV->setEnabled(false);
    btnAVLeft->setEnabled(false);
    btnAVRight->setEnabled(false);
    avTime->setEnabled(false);
    btnPlus->setEnabled(false);
    btnMinus->setEnabled(false);
    btnNextAV->setEnabled(false);
    btnPrevAV->setEnabled(false);


    connect(btnStartPause, SIGNAL(clicked()), SLOT(btnStartPauseClicked()));
    connect(btnStopReset, SIGNAL(clicked()), SLOT(btnResetClicked()));
    connect(btnSetAv, SIGNAL(clicked()), SLOT(btnSetAVClicked()));
    connect(btnAV, SIGNAL(clicked()), SLOT(btnAVClicked()));
    connect(btnAVLeft, SIGNAL(clicked()), SLOT(btnAVLeftClicked()));
    connect(btnAVRight, SIGNAL(clicked()), SLOT(btnAVRightClicked()));
    connect(btnPlus, SIGNAL(clicked()), SLOT(btnPlusClicked()));
    connect(btnMinus, SIGNAL(clicked()), SLOT(btnMinusClicked()));
    connect(btnNextAV, SIGNAL(clicked()), SLOT(btnNextAVClicked()));
    connect(btnPrevAV, SIGNAL(clicked()), SLOT(btnPrevAVClicked()));
    connect(btnSetLeft, SIGNAL(clicked()), SLOT(btnSetLeftClicked()));
    connect(btnSetRight, SIGNAL(clicked()), SLOT(btnSetRightClicked()));

}
    const QString StopWatch::qssSelected = "QPushButton {font: 100 26px \"Serif\";color: #FFFFFF; border: 2px solid #007aff; border-radius: 10px; background-color: #007aff;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
    const QString StopWatch::qssNotSelected = "QPushButton {font: 100 26px \"Serif\";color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f5f5;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";


    void StopWatch::btnStartPauseClicked(){
        if(btnStartPause->toolTip() != "Pause"){
            startTime = QDateTime::currentDateTime();
            running = true;
            timerStarted = true;
            btnStartPause->setIcon(QIcon(":/timer/icons/Timer/pause.png"));
            btnStartPause->setToolTip("Pause");
            btnStopReset->setIcon(QIcon(":/timer/icons/Timer/stop.png"));
            btnStopReset->setToolTip("Stop");
            btnStopReset->setEnabled(true);
            btnSetAv->setEnabled(true);
        }
        else {
            running = false;
            btnStartPause->setIcon(QIcon(":/timer/icons/Timer/start.png"));
            btnStartPause->setToolTip("Start");
            timerEvent(new QTimerEvent(0));
            totalTime += sessionTime;
        }
        if(timerStarted)
            currentAVTime = startTime;
    }

    void StopWatch::btnResetClicked(){
        running = false;
        btnStartPause->setIcon(QIcon(":/timer/icons/Timer/start.png"));
        btnStartPause->setToolTip("Start");

        if(btnStopReset->toolTip() != "Reset"){
            btnStopReset->setIcon(QIcon(":/timer/icons/Timer/reset.png"));
            btnStopReset->setToolTip("Reset");
            btnStartPause->setEnabled(false);
        }
        else {
            btnStopReset->setEnabled(false);
            btnSetAv->setEnabled(false);
            btnStartPause->setEnabled(true);
            totalTime = 0;
            sessionTime = 0;
            timer->setText("00:00");
            lstAV->clear();
            lstLeftAVs->clear();
            lstRightAVs->clear();
            updateGraph();
        }


    }

    void StopWatch::btnSetAVClicked(){
        totalAV++;
        currentAV = totalAV;


        QString str;
        str.append(QString("%1").arg(currentAV));
        btnAV->setText("AV " + str);

        lstAVTime->append(getTime());

        int t = lstAVTime->at(currentAV -1);

        unsigned int m = (t/ 60);
        unsigned int s = (t - 60*m);
        const QString diff = QString("%1:%2")
        .arg(m, 2, 10, QChar('0'))
        .arg(s, 2, 10, QChar('0'));
        avTime->setText(diff);

        btnAV->setEnabled(true);
        btnAVLeft->setEnabled(true);
        btnAVRight->setEnabled(true);
        avTime->setEnabled(true);
        btnPlus->setEnabled(true);
        btnMinus->setEnabled(true);

        if(totalAV > 1)
            btnPrevAV->setEnabled(true);
        btnNextAV->setEnabled(false);

        avPressed = true;
        leftPressed = false;
        btnSetLeft->setStyleSheet(this->qssNotSelected);
        rightPressed = false;
        btnSetRight->setStyleSheet(this->qssNotSelected);

    }

    void StopWatch::btnSetLeftClicked(){
        if(leftPressed){
            leftPressed = false;
            btnSetLeft->setStyleSheet(this->qssNotSelected);

        }
        else {
            leftPressed = true;
            btnSetLeft->setStyleSheet(this->qssSelected);
        }
    }

    void StopWatch::btnSetRightClicked(){
        if(rightPressed){
            rightPressed = false;
            btnSetRight->setStyleSheet(this->qssNotSelected);
        }
        else {
            rightPressed = true;
            btnSetRight->setStyleSheet(this->qssSelected);
        }
    }

    void StopWatch::btnAVClicked(){
        btnAV->setStyleSheet(this->qssSelected);
        btnAVLeft->setStyleSheet(this->qssNotSelected);
        btnAVRight->setStyleSheet(this->qssNotSelected);
    }

    void StopWatch::btnAVLeftClicked(){
        btnAV->setStyleSheet(this->qssNotSelected);
        btnAVLeft->setStyleSheet(this->qssSelected);
        btnAVRight->setStyleSheet(this->qssNotSelected);
    }

    void StopWatch::btnAVRightClicked(){
        btnAV->setStyleSheet(this->qssNotSelected);
        btnAVLeft->setStyleSheet(this->qssNotSelected);
        btnAVRight->setStyleSheet(this->qssSelected);
    }


    void StopWatch::btnPlusClicked(){
        int o = lstAVTime->at(currentAV -1) +1;
        lstAVTime->replace(currentAV -1, o);


        int t = lstAVTime->at(currentAV -1);

        unsigned int m = (t/ 60);
        unsigned int s = (t - 60*m);
        const QString diff = QString("%1:%2")
        .arg(m, 2, 10, QChar('0'))
        .arg(s, 2, 10, QChar('0'));
        avTime->setText(diff);
    }

    void StopWatch::btnMinusClicked(){
        int o = lstAVTime->at(currentAV -1) -1;
        lstAVTime->replace(currentAV -1, o);


        int t = lstAVTime->at(currentAV -1);

        unsigned int m = (t/ 60);
        unsigned int s = (t - 60*m);
        const QString diff = QString("%1:%2")
        .arg(m, 2, 10, QChar('0'))
        .arg(s, 2, 10, QChar('0'));
        avTime->setText(diff);
    }

    void StopWatch::btnNextAVClicked(){
        currentAV++;
        QString str;
        str.append(QString("%1").arg(currentAV));
        btnAV->setText("AV " + str);
        btnPrevAV->setEnabled(true);
        if(currentAV  == totalAV)
            btnNextAV->setEnabled(false);

        int t = lstAVTime->at(currentAV -1);

        unsigned int m = (t/ 60);
        unsigned int s = (t - 60*m);
        const QString diff = QString("%1:%2")
        .arg(m, 2, 10, QChar('0'))
        .arg(s, 2, 10, QChar('0'));
        avTime->setText(diff);
    }

    void StopWatch::btnPrevAVClicked(){
        currentAV--;
        QString str;
        str.append(QString("%1").arg(currentAV));
        btnAV->setText("AV " + str);
        btnNextAV->setEnabled(true);
        if(currentAV == 1)
            btnPrevAV->setEnabled(false);

        int t = lstAVTime->at(currentAV -1);

        unsigned int m = (t/ 60);
        unsigned int s = (t - 60*m);
        const QString diff = QString("%1:%2")
        .arg(m, 2, 10, QChar('0'))
        .arg(s, 2, 10, QChar('0'));
        avTime->setText(diff);
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
            if(counter != s){
                updateAVs();
                updateGraph();
            }
            counter = s;
        }
    }

    void StopWatch::updateAVs(){
        if(avPressed){
            lstAV->append("true");
            avPressed = false;
        }
        else
            lstAV->append("false");

        if(leftPressed)
            lstLeftAVs->append("true");
        else
            lstLeftAVs->append("false");
        if(rightPressed)
            lstRightAVs->append("true");
        else
            lstRightAVs->append("false");
    }

    void StopWatch::updateGraph(){
        painter.begin(&picture);
        painter.setRenderHint(QPainter::Antialiasing);

        paintX = 10;
        //painter.drawLine(-20, 85, -20, -85);
        for(int i = 0; i < lstLeftAVs->count(); ++i){
            QString s = lstLeftAVs->at(i);

            painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap));
            if(s == "true"){
                if(i > 0 && lstLeftAVs->at(i -1) == "false"){
                    totalLeftAV++;
                    painter.drawLine(paintX -10, -60, paintX -10, -80);
                    painter.drawLine(paintX -10, -80, paintX, -80);
                }
                painter.drawLine(paintX -10, -80, paintX, -80);
            }
            else {
                if(i > 0 && lstLeftAVs->at(i -1) == "true"){
                    painter.drawLine(paintX -10, -80, paintX -10, -60);
                    painter.drawLine(paintX -10, -60, paintX, -60);
                }
                painter.drawLine(paintX -10, -60, paintX, -60);
            }
            paintX = paintX +10;

        }

        paintX = 10;
        for(int i = 0; i < lstRightAVs->count(); ++i){
            QString s = lstRightAVs->at(i);

            painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap));
            if(s == "true"){
                if(i > 0 && lstRightAVs->at(i -1) == "false"){
                    totalRightAV++;
                    painter.drawLine(paintX -10, 0, paintX -10, -20);
                    painter.drawLine(paintX -10, -20, paintX, -20);
                }
                painter.drawLine(paintX -10, -20, paintX, -20);
            }
            else {
                if(i > 0 && lstRightAVs->at(i -1) == "true"){
                    painter.drawLine(paintX -10, -20, paintX -10, 0);
                    painter.drawLine(paintX -10, 0, paintX, 0);
                }
                painter.drawLine(paintX -10, 0, paintX, 0);
            }
            paintX = paintX +10;

        }

        paintX = 10;
        if(lstAV->empty()== false){
            for(int i = 0; i < (lstAV->count() + 5); ++i){
                painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
                if(i%5 == 0){
                    painter.drawLine(paintX -10, 70, paintX -10, 80);
                    unsigned int m = (i/ 60);
                    unsigned int s = (i - 60*m);
                    const QString diff = QString("%1:%2")
                    .arg(m, 2, 10, QChar('0'))
                    .arg(s, 2, 10, QChar('0'));
                    QFont font=painter.font() ;
                    font.setPointSize(7);
                    painter.setFont(font);
                    painter.drawText(QPoint(paintX -26, 93), diff);
                }
                else
                    painter.drawLine(paintX -10, 74, paintX -10, 78);
                paintX = paintX +10;
            }
        }

        paintX = 10;
        for(int i = 0; i < lstAV->count(); ++i){
            QString s = lstAV->at(i);

            painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
            if(s == "true"){
                painter.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap));
                painter.drawLine(paintX -10, 85, paintX -10, -85);
                painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
                painter.drawLine(paintX - 10, 50, paintX, 50);
            }
            else
                painter.drawLine(paintX - 10, 50, paintX, 50);
            paintX = paintX +10;
        }


        painter.end();

        graph->setPicture(picture);
        graph->adjustSize();

        graphArea->horizontalScrollBar()->setValue(graphArea->horizontalScrollBar()->maximum());

    }

    int StopWatch::getTime(){
        int avCount = 0;
        int secs = 0;
        for(int i = 1; i < lstAV->count(); ++i){
           QString s = lstAV->at(i);
           if(avCount == (currentAV -1)){
               if(s == "true"){
                  avCount++;
               }
               else
                   secs++;

           }
           else {
              if(s == "true")
                  avCount++;
           }
        }
        return secs +1;
    }
