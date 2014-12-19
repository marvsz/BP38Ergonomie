#include "stopwatch.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QTimerEvent>
#include <QStackedWidget>
#include <QDebug>

StopWatch::StopWatch(QWidget *parent) : QMainWindow(parent)
  , running(false)
  , timerStarted(false)
  , standardView(true)
  , startTime()
  , currentAVTime()
  , timerTitle(new QLabel("Gesamtlaufzeit:"))
  , timer(new QLabel("00:00"))
  , totalTime(0)
  , btnStartPause(new QPushButton())
  , btnStopReset(new QPushButton())
  , btnMinimize(new QPushButton())
  , btnMaximize(new QPushButton())
  , counter(0)
  , currentLeftAV(0)
  , currentRightAV(0)
  , currentLeftTime(0)
  , currentRightTime(0)
  , leftAVButtons(new QVector<SelectableValueButton*>)
  , rightAVButtons(new QVector<SelectableValueButton*>)
  , avButtons(new QVector<SelectableValueButton*>)
  , btnView(new ButtonTimelineView(this))
  , avControl(new AVRecordControl(this))
{
    main = new QWidget();

    mainVLayout = new QVBoxLayout();
    mainHLayout = new QHBoxLayout();
    mainTimerLayout = new QVBoxLayout();
    timerBtnLayout = new QVBoxLayout();
    mainAVLayout = new QVBoxLayout();
    avSelLayout = new QHBoxLayout();
    avTimeLayout = new QHBoxLayout();
    avLeftRightLayout = new QHBoxLayout();
    timerBtnLayout2 = new QHBoxLayout();
    sizeLayout = new QVBoxLayout();
    separator = new Separator(Qt::Horizontal, 3, this);

    sizeLayout->addWidget(btnMaximize);
    sizeLayout->addWidget(btnMinimize);

    avLeftRightLayout->addWidget(avControl->btnAVLeft);
    avLeftRightLayout->addWidget(avControl->btnAVRight);
    avLeftRightLayout->addWidget(avControl->btnAV);
    avSelLayout->addWidget(avControl->btnPrevAV);
    avSelLayout->addWidget(avControl->btnSelAV);
    avSelLayout->addWidget(avControl->btnNextAV);
    avTimeLayout->addWidget(avControl->btnMinus);
    avTimeLayout->addWidget(avControl->avTime);
    avTimeLayout->addWidget(avControl->btnPlus);
    mainAVLayout->addLayout(avLeftRightLayout);
    mainAVLayout->addLayout(avSelLayout);
    mainAVLayout->addLayout(avTimeLayout);

    timerBtnLayout->addWidget(btnStartPause);
    timerBtnLayout->addWidget(btnStopReset);

    timerBtnLayout2->addWidget(avControl->btnSetLeftRight);
    timerBtnLayout2->addLayout(timerBtnLayout);
    mainTimerLayout->addLayout(timerBtnLayout2);
    mainTimerLayout->addWidget(timerTitle);
    mainTimerLayout->addWidget(timer);
    mainTimerLayout->setAlignment(timer, Qt::AlignCenter);

    mainHLayout->addLayout(sizeLayout);
    mainHLayout->addLayout(mainAVLayout);
    mainHLayout->addWidget(avControl);
    mainHLayout->addLayout(mainTimerLayout);
    mainHLayout->setAlignment(mainTimerLayout, Qt::AlignRight);

    mainVLayout->addWidget(btnView);
    mainVLayout->addWidget(separator);
    mainVLayout->addLayout(mainHLayout);

    btnView->setVisible(false);
    separator->setVisible(false);

    this->setMaximumHeight(175);

    main->setLayout(mainVLayout);
    this->setCentralWidget(main);

    btnMinimize->setFixedSize(45,45);
    btnMaximize->setFixedSize(45,45);

    btnStartPause->setFixedSize(45,45);
    btnStopReset->setFixedSize(45,45);

    btnStartPause->setIcon(QIcon(":/timer/icons/Timer/start.png"));
    btnStartPause->setObjectName("btnStartPause");
    btnStartPause->setIconSize(QSize(45,45));
    btnStartPause->setToolTip("Start");
    btnStopReset->setIcon(QIcon(":/timer/icons/Timer/reset.png"));
    btnStopReset->setObjectName("btnStopReset");
    btnStopReset->setIconSize(QSize(45,45));
    btnStopReset->setToolTip("Reset");
    btnMinimize->setIcon(QIcon(":/timer/icons/Timer/minimize.png"));
    btnMinimize->setIconSize(QSize(45,45));
    btnMaximize->setIcon(QIcon(":/timer/icons/Timer/maximize.png"));
    btnMaximize->setIconSize(QSize(45,45));

    timerTitle->setStyleSheet("font: 12px");
    timer->setStyleSheet("font: 15pt");

    startTimer(0);
    btnStartPause->setEnabled(true);
    btnStopReset->setEnabled(false);

    btnView->btnPlus->setEnabled(false);
    btnView->btnMinus->setEnabled(false);

    connect(btnStartPause, SIGNAL(clicked()), SLOT(btnStartPauseClicked()));
    connect(btnStopReset, SIGNAL(clicked()), SLOT(btnStopResetClicked()));
    connect(btnMinimize, SIGNAL(clicked()), SLOT(btnMinimizeClicked()));
    connect(btnMaximize, SIGNAL(clicked()), SLOT(btnMaximizeClicked()));
}
    const QString StopWatch::qssSelected = "QPushButton {font: 100 20px \"Serif\";color: #FFFFFF; border: 2px solid #007aff; border-radius: 10px; background-color: #007aff;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
    const QString StopWatch::qssNotSelected = "QPushButton {font: 100 20px \"Serif\";color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f5f5;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";

    /**
     * @brief logic of the Start/Pause button
     */
    void StopWatch::btnStartPauseClicked(){
        if(btnStartPause->toolTip() != "Pause"){
            startTime = QDateTime::currentDateTime();
            running = true;
            timerStarted = true;
            btnStartPause->setIcon(QIcon(":/timer/icons/Timer/pause.png"));
            btnStartPause->setToolTip("Pause");
            if(!avControl->windowMinimized){
                btnStopReset->setIcon(QIcon(":/timer/icons/Timer/stop.png"));
                btnStopReset->setToolTip("Stop");
                btnStopReset->setEnabled(true);
                avControl->btnSetAv->setEnabled(true);
            }
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

    /**
     * @brief logic of the Stop/Reset Button
     */
    void StopWatch::btnStopResetClicked(){
        running = false;
        btnStartPause->setIcon(QIcon(":/timer/icons/Timer/start.png"));
        btnStartPause->setToolTip("Start");

        if(btnStopReset->toolTip() != "Reset"){
            btnStopReset->setIcon(QIcon(":/timer/icons/Timer/reset.png"));
            btnStopReset->setToolTip("Reset");
            btnStartPause->setEnabled(false);
            avControl->stopped = true;
            avControl->lstAV->append("true");
            avControl->lstLeftAVs->append("false");
            avControl->lstRightAVs->append("false");
        }
        else {
            btnStopReset->setEnabled(false);
            avControl->btnSetAv->setEnabled(false);
            btnStartPause->setEnabled(true);
            avControl->stopped = false;
            totalTime = 0;
            sessionTime = 0;
            timer->setText("00:00");
            avControl->lstAV->clear();
            avControl->lstLeftAVs->clear();
            avControl->lstRightAVs->clear();
            avControl->lstAVTime->clear();
            avControl->lstLeftAVTime->clear();
            avControl->lstRightAVTime->clear();
            avControl->updateGraph();
            avControl->avTime->setText("00:00");
            avControl->btnSelAV->setText("leer");
            avControl->btnSelAV->setEnabled(false);
            avControl->btnAV->setEnabled(false);
            avControl->btnAVLeft->setEnabled(false);
            avControl->btnAVRight->setEnabled(false);
            avControl->btnPlus->setEnabled(false);
            avControl->btnMinus->setEnabled(false);
            avControl->btnNextAV->setEnabled(false);
            avControl->btnPrevAV->setEnabled(false);
            avControl->totalAV = 0;
            avControl->currentAV = 0;
            avControl->currentLeftAV = 0;
            avControl->currentRightAV = 0;
            avControl->totalLeftAV = 0;
            avControl->totalRightAV = 0;
            counter = 0;
            avControl->btnSetLeft->setStyleSheet(this->qssNotSelected);
            avControl->btnSetRight->setStyleSheet(this->qssNotSelected);
            avControl->btnSetLeftRight->setStyleSheet(this->qssNotSelected);
            avControl->btnSelAV->setStyleSheet(this->qssNotSelected);
            avControl->btnAVLeft->setStyleSheet(this->qssNotSelected);
            avControl->btnAVRight->setStyleSheet(this->qssNotSelected);
            avControl->btnAV->setStyleSheet(this->qssNotSelected);
        }
    }

    /**
     * @brief logic of the Stopwatch, updates stopwatch time
     */
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
                avControl->updateAVs();
                if(!avControl->windowMinimized)
                    avControl->updateGraph();
                getButtonView();
            }
            counter = s;
        }
    }

    /**
     * @brief updates the button view, adds new buttons if necessary, otherwise, resizes existing buttons
     */
    void StopWatch::getButtonView(){
        btnView->btnPlus->setEnabled(true);
        btnView->btnMinus->setEnabled(true);

        int i = avControl->lstLeftAVs->count() -1;
                if(i > 0 && avControl->lstLeftAVs->at(i) == false && avControl->lstLeftAVs->at(i -1) == true && currentLeftAV < avControl->totalLeftAV){
                    currentLeftAV++;
                    QString btn = "R ";
                    btn.append(QString("%1: %2s").arg(currentLeftAV).arg(currentLeftTime));
                    leftAVButtons->append((new SelectableValueButton(currentLeftAV, currentLeftTime)));
                    leftAVButtons->at(currentLeftAV -1)->setFixedSize(currentLeftTime*100, 60);
                    leftAVButtons->at(currentLeftAV -1)->setText(btn);
                    btnView->leftButtonLayout->addWidget(leftAVButtons->at(currentLeftAV -1));
                    btnView->leftButtonLayout->addItem(new QSpacerItem(100, 60));
                }
                else if(avControl->lstLeftAVs->at(i) == false)
                        btnView->leftButtonLayout->addItem(new QSpacerItem(100, 60));
                else if(i > 0 && avControl->lstLeftAVs->at(i -1) == false)
                        currentLeftTime = 1;
                else
                        currentLeftTime++;

        i = avControl->lstRightAVs->count() -1;
                if(i > 0 && avControl->lstRightAVs->at(i) == false && avControl->lstRightAVs->at(i -1) == true && currentRightAV < avControl->totalRightAV){
                    currentRightAV++;
                    QString btn = "R ";
                    btn.append(QString("%1: %2s").arg(currentRightAV).arg(currentRightTime));
                    rightAVButtons->append((new SelectableValueButton(currentRightAV, currentLeftTime)));
                    rightAVButtons->at(currentRightAV -1)->setFixedSize(currentRightTime*100, 60);
                    rightAVButtons->at(currentRightAV -1)->setText(btn);
                    btnView->rightButtonLayout->addWidget(rightAVButtons->at(currentRightAV -1));
                    btnView->rightButtonLayout->addItem(new QSpacerItem(100, 60));
                }
                else if(avControl->lstRightAVs->at(i) == false)
                        btnView->rightButtonLayout->addItem(new QSpacerItem(100, 60));
                else if(i > 0 && avControl->lstRightAVs->at(i -1) == false)
                        currentRightTime = 1;
                else
                        currentRightTime++;


        for(int i = 1; i <= avControl->totalAV; ++i){
            if(btnView->avButtonLayout->itemAt(i) == 0){
                QString btn = "Av_";
                int time = avControl->getTime(i);
                btn.append(QString("%1: %2s").arg(i).arg(time));
                avButtons->append(new SelectableValueButton(i, time));
                avButtons->at(i -1)->setFixedSize(time*100,60);
                avButtons->at(i -1)->setText(btn);
                btnView->avButtonLayout->addWidget(avButtons->at(i -1));
            }
        }
    }

    /**
     * @brief creates and shows layout of the minimized view
     */
    void StopWatch::btnMinimizeClicked(){
        if(standardView){
            standardView = false;
            avControl->windowMinimized = true;

            mini = new QWidget();
            minimizedLayout = new QHBoxLayout();

            minimizedLayout->addWidget(btnMaximize);
            minimizedLayout->addItem(new QSpacerItem(70, 45));
            minimizedLayout->addWidget(avControl->btnAVLeft);
            minimizedLayout->addWidget(avControl->btnAVRight);
            minimizedLayout->addWidget(avControl->btnAV);
            minimizedLayout->addItem(new QSpacerItem(70, 45));
            minimizedLayout->addWidget(avControl->btnPrevAV);
            minimizedLayout->addWidget(avControl->btnSelAV);
            minimizedLayout->addWidget(avControl->btnNextAV);
            minimizedLayout->addWidget(timer);
            minimizedLayout->addWidget(btnStartPause);

            minimizedLayout->setAlignment(timer, Qt::AlignRight);
            minimizedLayout->setAlignment(btnStartPause, Qt::AlignRight);

            minimizedLayout->addWidget(avControl->btnMinus);
            minimizedLayout->addWidget(avControl->btnPlus);
            minimizedLayout->addWidget(avControl->avTime);
            minimizedLayout->addWidget(avControl);
            minimizedLayout->addWidget(btnStopReset);
            minimizedLayout->addWidget(avControl->btnSetLeftRight);
            minimizedLayout->addWidget(timerTitle);
            minimizedLayout->addWidget(btnMinimize);
            minimizedLayout->addWidget(btnView);
            minimizedLayout->addWidget(separator);

            btnMaximize->setVisible(true);
            avControl->btnMinus->setVisible(false);
            avControl->btnPlus->setVisible(false);
            avControl->avTime->setVisible(false);
            avControl->setVisible(false);
            btnStopReset->setVisible(false);
            avControl->btnSetLeftRight->setVisible(false);
            timerTitle->setVisible(false);
            btnMinimize->setVisible(false);
            btnView->setVisible(false);
            separator->setVisible(false);

            mini->setLayout(minimizedLayout);
            this->setCentralWidget(mini);
            this->setMaximumHeight(65);
        }
        else {
            standardView = true;
            btnMaximize->setVisible(true);
            btnView->setVisible(false);
            separator->setVisible(false);
            this->parentWidget()->findChild<QStackedWidget*>()->setVisible(true);
            this->setMaximumHeight(175);
        }
    }

    /**
     * @brief creates and shows layout of the maximized view
     */
    void StopWatch::btnMaximizeClicked(){
        if(standardView){
            standardView = false;
            btnView->setVisible(true);
            separator->setVisible(true);
            btnMaximize->setVisible(false);
            this->parentWidget()->findChild<QStackedWidget*>()->setVisible(false);
            this->setMaximumHeight(2000);
        }
        else {
            standardView = true;
            avControl->windowMinimized = false;

            main = new QWidget();
            mainVLayout = new QVBoxLayout();
            mainHLayout = new QHBoxLayout();
            mainTimerLayout = new QVBoxLayout();
            timerBtnLayout = new QVBoxLayout();
            mainAVLayout = new QVBoxLayout();
            avSelLayout = new QHBoxLayout();
            avTimeLayout = new QHBoxLayout();
            avLeftRightLayout = new QHBoxLayout();
            timerBtnLayout2 = new QHBoxLayout();
            sizeLayout = new QVBoxLayout();

            sizeLayout->addWidget(btnMaximize);
            sizeLayout->addWidget(btnMinimize);

            avLeftRightLayout->addWidget(avControl->btnAVLeft);
            avLeftRightLayout->addWidget(avControl->btnAVRight);
            avLeftRightLayout->addWidget(avControl->btnAV);
            avSelLayout->addWidget(avControl->btnPrevAV);
            avSelLayout->addWidget(avControl->btnSelAV);
            avSelLayout->addWidget(avControl->btnNextAV);
            avTimeLayout->addWidget(avControl->btnMinus);
            avTimeLayout->addWidget(avControl->avTime);
            avTimeLayout->addWidget(avControl->btnPlus);
            mainAVLayout->addLayout(avLeftRightLayout);
            mainAVLayout->addLayout(avSelLayout);
            mainAVLayout->addLayout(avTimeLayout);

            timerBtnLayout->addWidget(btnStartPause);
            timerBtnLayout->addWidget(btnStopReset);

            timerBtnLayout2->addWidget(avControl->btnSetLeftRight);
            timerBtnLayout2->addLayout(timerBtnLayout);
            mainTimerLayout->addLayout(timerBtnLayout2);
            mainTimerLayout->addWidget(timerTitle);
            mainTimerLayout->addWidget(timer);
            mainTimerLayout->setAlignment(timer, Qt::AlignCenter);

            avControl->btnMinus->setVisible(true);
            avControl->btnPlus->setVisible(true);
            avControl->avTime->setVisible(true);
            avControl->setVisible(true);
            btnStopReset->setVisible(true);
            avControl->btnSetLeftRight->setVisible(true);
            timerTitle->setVisible(true);
            btnMinimize->setVisible(true);

            mainHLayout->addLayout(sizeLayout);
            mainHLayout->addLayout(mainAVLayout);
            mainHLayout->addWidget(avControl);
            mainHLayout->addLayout(mainTimerLayout);
            mainHLayout->setAlignment(mainTimerLayout, Qt::AlignRight);

            mainVLayout->addWidget(btnView);
            mainVLayout->addWidget(separator);
            mainVLayout->addLayout(mainHLayout);

            btnView->setVisible(false);
            separator->setVisible(false);

            main->setLayout(mainVLayout);
            this->setCentralWidget(main);
            this->setMaximumHeight(175);
        }
    }
