#include "stopwatch.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QTimerEvent>
#include <QStackedWidget>
#include <QDebug>

StopWatch::StopWatch(ButtonTimelineView *buttonView, QWidget *parent) : QMainWindow(parent)
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
  , btnView(buttonView)
  , avControl(new AVRecordControl(this))
  , graphView(new GraphTimelineView)
{

    // LAYOUTS
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
    avSetLayout = new QVBoxLayout();

    //  MINIMIZE MAXIMIZE BUTTONS
    sizeLayout->addWidget(btnMaximize);
    sizeLayout->addWidget(btnMinimize);

    // CHOOSE AV/LEFT/RIGHT
    avLeftRightLayout->addWidget(avControl->btnAVLeft);
    avLeftRightLayout->addWidget(avControl->btnAVRight);
    avLeftRightLayout->addWidget(avControl->btnAV);

    // NAVIGATE THROUGH AVS
    avSelLayout->addWidget(avControl->btnPrevAV);
    avSelLayout->addWidget(avControl->btnSelAV);
    avSelLayout->addWidget(avControl->btnNextAV);

    // ADJUST AV TIME
    avTimeLayout->addWidget(avControl->btnMinus);
    avTimeLayout->addWidget(avControl->avTime);
    avTimeLayout->addWidget(avControl->btnPlus);

    // ADD LAYOUTS TO TIMER
    mainAVLayout->addLayout(avLeftRightLayout);
    mainAVLayout->addLayout(avSelLayout);
    mainAVLayout->addLayout(avTimeLayout);

    // START/PAUSE AND STOP RESET BUTTON
    timerBtnLayout->addWidget(btnStartPause);
    timerBtnLayout->addWidget(btnStopReset);
    
    // SET AV AND TOTAL TIME BUTTONS
    timerBtnLayout2->addWidget(avControl->btnSetLeftRight);
    timerBtnLayout2->addLayout(timerBtnLayout);
    mainTimerLayout->addLayout(timerBtnLayout2);
    mainTimerLayout->addWidget(timerTitle);
    mainTimerLayout->addWidget(timer);
    mainTimerLayout->setAlignment(timer, Qt::AlignCenter);

    // SET AV SET BUTTONS
    avSetLayout->addWidget(avControl->btnSetLeft);
    avSetLayout->addWidget(avControl->btnSetRight);
    avSetLayout->addWidget(avControl->btnSetAv);

    // ALIGN ALL LAYOUTS HORIZONTALLY
    mainHLayout->addLayout(sizeLayout);
    mainHLayout->addLayout(mainAVLayout);
    mainHLayout->addWidget(graphView);
    mainHLayout->addLayout(avSetLayout);
    mainHLayout->addLayout(mainTimerLayout);
    mainHLayout->setAlignment(mainTimerLayout, Qt::AlignRight);

    // ADD THE BUTTON VIEW AND THE TIMER LAYOUT TO THE MAIN LAYOUT
    mainVLayout->addLayout(mainHLayout);

    this->setMaximumHeight(175);

    main->setLayout(mainVLayout);
    this->setCentralWidget(main);

    // SET BUTTON SIZES AND ICONS
    btnMinimize->setFixedSize(45,45);
    btnMaximize->setFixedSize(45,45);

    btnStartPause->setFixedSize(45,45);
    btnStopReset->setFixedSize(45,45);

    btnStartPause->setIcon(QIcon(":/timer/icons/Timer/record.png"));
    btnStartPause->setObjectName("btnTimer");
    btnStartPause->setIconSize(QSize(45,45));
    btnStartPause->setToolTip("Start");
    btnStopReset->setIcon(QIcon(":/timer/icons/Timer/reset.png"));
    btnStopReset->setObjectName("btnTimer");
    btnStopReset->setIconSize(QSize(45,45));
    btnStopReset->setToolTip("Reset");
    btnMinimize->setIcon(QIcon(":/timer/icons/Timer/minimize.png"));
    btnMinimize->setObjectName("btnTimer");
    btnMinimize->setIconSize(QSize(45,45));
    btnMaximize->setIcon(QIcon(":/timer/icons/Timer/maximize.png"));
    btnMaximize->setObjectName("btnTimer");
    btnMaximize->setIconSize(QSize(45,45));

    timerTitle->setStyleSheet("font: 12px");
    timer->setStyleSheet("font: 15pt");

    // RESET TIMER ENABLE START/DISABLE STOP BUTTON
    startTimer(1000);
    btnStartPause->setEnabled(true);
    btnStopReset->setEnabled(false);

    // CONNECT BUTTONS TO SLOTS
    connect(btnStartPause, SIGNAL(clicked()), SLOT(btnStartPauseClicked()));
    connect(btnStopReset, SIGNAL(clicked()), SLOT(btnStopResetClicked()));
    connect(btnMinimize, SIGNAL(clicked()), SLOT(btnMinimizeClicked()));
    connect(btnMaximize, SIGNAL(clicked()), SLOT(btnMaximizeClicked()));
}
    const QString StopWatch::qssSelected = "QPushButton {font: 100 20px \"Serif\";color: #FFFFFF; border: 2px solid #007aff; border-radius: 10px; background-color: #007aff;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
    const QString StopWatch::qssNotSelected = "QPushButton {font: 100 20px \"Serif\";color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f5f5;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";

    /**
     * @brief A slot that is called to adapt the view of the start/pause button depending on the
     * current documentation state.
     */
    void StopWatch::btnStartPauseClicked(){
        // if the START BUTTON shows PLAY or RECORD
        if(btnStartPause->toolTip() != "Pause"){
            // get the current time and start running the timer
            startTime = QDateTime::currentDateTime();
            running = true;
            timerStarted = true;
            // let the icon and tooltip show the pause icon now
            btnStartPause->setIcon(QIcon(":/timer/icons/Timer/pause.png"));
            btnStartPause->setToolTip("Pause");
            // if the AV control in standard mode
            if(!avControl->windowMinimized){
                // set the STOP button
                btnStopReset->setIcon(QIcon(":/timer/icons/Timer/stop.png"));
                btnStopReset->setToolTip("Stop");
                btnStopReset->setEnabled(true);
                // enable SET AV button
                avControl->btnSetAv->setEnabled(true);
            }
        }
        // if the START BUTTON shows PAUSE
        else {
            // stop the timer
            running = false;
            // set the icon to PLAY again
            btnStartPause->setIcon(QIcon(":/timer/icons/Timer/start.png"));
            btnStartPause->setToolTip("Start");
            // emit timer event and add session to the total time
            timerEvent(new QTimerEvent(0));
            totalTime += sessionTime;
        }
        // if that timer has started
        if(timerStarted)
            // the current AV time is the start time
            currentAVTime = startTime;
    }

    /**
     * @brief A slot that is called to adapt the view of the stop/reset button depending on the
     * current documentation state.
     */
    void StopWatch::btnStopResetClicked(){
        // stop the timer and set the start button back to the record icon
        running = false;
        btnStartPause->setIcon(QIcon(":/timer/icons/Timer/record.png"));
        btnStartPause->setToolTip("Start");

        // if the button shows the STOP icon
        if(btnStopReset->toolTip() != "Reset"){
            // set the button to the RESET state and disable the start button
            btnStopReset->setIcon(QIcon(":/timer/icons/Timer/reset.png"));
            btnStopReset->setToolTip("Reset");
            btnStartPause->setEnabled(false);
            // stop the av control
            avControl->stopped = true;
            // append a new AV to the av controls list
            avControl->lstAV->append("true");
            // state that the left and right AVs were not running
            avControl->lstLeftAVs->append("false");
            avControl->lstRightAVs->append("false");
        }
        // if the button shows the RESET icon
        else {
            // disable the the RESET and the SET AV button
            btnStopReset->setEnabled(false);
            avControl->btnSetAv->setEnabled(false);
            // reenable the RECORD button
            btnStartPause->setEnabled(true);
            // reset time
            avControl->stopped = false;
            totalTime = 0;
            sessionTime = 0;
            timer->setText("00:00");
            // clear all AV lists
            avControl->lstAV->clear();
            avControl->lstLeftAVs->clear();
            avControl->lstRightAVs->clear();
            avControl->lstAVTime->clear();
            avControl->lstLeftAVTime->clear();
            avControl->lstRightAVTime->clear();
            // update the graph timeline (delete)
            graphView->updateGraph(avControl->lstAV, avControl->lstLeftAVs, avControl->lstRightAVs);
            // disable all buttons
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
            // reset current AV values
            avControl->totalAV = 0;
            avControl->currentAV = 0;
            avControl->currentLeftAV = 0;
            avControl->currentRightAV = 0;
            avControl->totalLeftAV = 0;
            avControl->totalRightAV = 0;
            counter = 0;
            // set stylesheets to "not selected"
            avControl->btnSetLeft->setStyleSheet(this->qssNotSelected);
            avControl->btnSetRight->setStyleSheet(this->qssNotSelected);
            avControl->btnSetLeftRight->setStyleSheet(this->qssNotSelected);
            avControl->btnSelAV->setStyleSheet(this->qssNotSelected);
            avControl->btnAVLeft->setStyleSheet(this->qssNotSelected);
            avControl->btnAVRight->setStyleSheet(this->qssNotSelected);
            avControl->btnAV->setStyleSheet(this->qssNotSelected);
            // reset current times
            currentLeftTime = 0;
            currentRightTime = 0;
            currentLeftAV = 0;
            currentRightAV = 0;
            // clear the button lists
            btnView->clearButtons();
        }
    }

    /**
     * @brief The timer event method is called, whenever there is a change in the running timer,
     * which may be resulting in a changed view
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
                    graphView->updateGraph(avControl->lstAV, avControl->lstLeftAVs, avControl->lstRightAVs);
                updateButtonView();
            }
            counter = s;
        }
    }

    /**
     * @brief A Slot that is called, when updates in the button view occure. Buttons are added if
     * needed or adapted.
     */
    void StopWatch::updateButtonView(){

        int i = avControl->lstLeftAVs->count() -1;
                if(i > 0 && !avControl->lstLeftAVs->at(i)&& avControl->lstLeftAVs->at(i -1) && currentLeftAV < avControl->totalLeftAV) {
                    currentLeftAV++;
                    QString btn = "L ";
                    btn.append(QString("%1: %2s").arg(currentLeftAV).arg(currentLeftTime));
                    SelectableValueButton *leftButton = (new SelectableValueButton(currentLeftAV, currentLeftTime));
                    connect(leftButton, SIGNAL(clickedWithID(int)), this, SLOT(selectLeftAV(int)));
                    leftButton->setFixedSize(currentLeftTime*100, 60);
                    leftButton->setText(btn);
                    leftAVButtons->append(leftButton);
                    btnView->leftButtonLayout->addWidget(leftButton);
                    btnView->leftButtonLayout->addSpacerItem(new QSpacerItem(100, 60));
                }
                else if(!avControl->lstLeftAVs->at(i))
                        btnView->leftButtonLayout->addSpacerItem(new QSpacerItem(100, 60));
                else if(i > 0 && !avControl->lstLeftAVs->at(i -1))
                        currentLeftTime = 1;
                else
                        currentLeftTime++;

        i = avControl->lstRightAVs->count() -1;
                if(i > 0 && !avControl->lstRightAVs->at(i) && avControl->lstRightAVs->at(i -1) && currentRightAV < avControl->totalRightAV){
                    currentRightAV++;
                    QString btn = "R ";
                    btn.append(QString("%1: %2s").arg(currentRightAV).arg(currentRightTime));
                    SelectableValueButton *rightButton = new SelectableValueButton(currentRightAV, currentLeftTime);
                    connect(rightButton, SIGNAL(clickedWithID(int)), this, SLOT(selectRightAV(int)));
                    rightButton->setFixedSize(currentRightTime*100, 60);
                    rightButton->setText(btn);
                    rightAVButtons->append(rightButton);
                    btnView->rightButtonLayout->addWidget(rightButton);
                    btnView->rightButtonLayout->addSpacerItem(new QSpacerItem(100, 60));
                }
                else if(avControl->lstRightAVs->at(i) == false)
                        btnView->rightButtonLayout->addSpacerItem(new QSpacerItem(100, 60));
                else if(i > 0 && avControl->lstRightAVs->at(i -1) == false)
                        currentRightTime = 1;
                else
                        currentRightTime++;


        for(int i = 1; i <= avControl->totalAV; ++i){
            if(btnView->avButtonLayout->itemAt(i-1) == 0){
                QString btn = "AV ";
                int time = avControl->getTime(i);
                btn.append(QString("%1: %2s").arg(i).arg(time));
                SelectableValueButton *avButton = new SelectableValueButton(i, time);
                connect(avButton, SIGNAL(clickedWithID(int)), this, SLOT(selectAV(int)));
                avButton->setFixedSize(time*100,60);
                avButton->setText(btn);
                avButtons->append(avButton);
                btnView->avButtonLayout->addWidget(avButton);
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
            minimizedLayout->addSpacerItem(new QSpacerItem(70, 45));
            minimizedLayout->addWidget(avControl->btnAVLeft);
            minimizedLayout->addWidget(avControl->btnAVRight);
            minimizedLayout->addWidget(avControl->btnAV);
            minimizedLayout->addSpacerItem(new QSpacerItem(70, 45));
            minimizedLayout->addWidget(avControl->btnPrevAV);
            minimizedLayout->addWidget(avControl->btnSelAV);
            minimizedLayout->addWidget(avControl->btnNextAV);
            minimizedLayout->addWidget(timer, 0, Qt::AlignRight);
            minimizedLayout->addWidget(btnStartPause, 0, Qt::AlignRight);

            minimizedLayout->addWidget(avControl->btnMinus);
            minimizedLayout->addWidget(avControl->btnPlus);
            minimizedLayout->addWidget(avControl->avTime);
            minimizedLayout->addWidget(graphView);
            minimizedLayout->addWidget(avControl->btnSetAv);
            minimizedLayout->addWidget(avControl->btnSetLeft);
            minimizedLayout->addWidget(avControl->btnSetRight);
            minimizedLayout->addWidget(btnStopReset);
            minimizedLayout->addWidget(avControl->btnSetLeftRight);
            minimizedLayout->addWidget(timerTitle);
            minimizedLayout->addWidget(btnMinimize);

            btnMaximize->show();
            avControl->btnMinus->hide();
            avControl->btnPlus->hide();
            avControl->avTime->hide();
            graphView->hide();
            avControl->btnSetAv->hide();
            avControl->btnSetLeft->hide();
            avControl->btnSetRight->hide();
            btnStopReset->hide();
            avControl->btnSetLeftRight->hide();
            timerTitle->hide();
            btnMinimize->hide();

            mini->setLayout(minimizedLayout);
            this->setCentralWidget(mini);
            this->setMaximumHeight(65);            
        }
        else {
            standardView = true;
            btnMaximize->show();
            emit minimizePressed();
        }
    }

    /**
     * @brief creates and shows layout of the maximized view
     */
    void StopWatch::btnMaximizeClicked(){
        if(standardView){
            standardView = false;
            btnMaximize->hide();
            emit maximizePressed();
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
            avSetLayout = new QVBoxLayout();

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

            avSetLayout->addWidget(avControl->btnSetLeft);
            avSetLayout->addWidget(avControl->btnSetRight);
            avSetLayout->addWidget(avControl->btnSetAv);

            avControl->btnMinus->show();
            avControl->btnPlus->show();
            avControl->avTime->show();
            graphView->show();
            avControl->btnSetAv->show();
            avControl->btnSetLeft->show();
            avControl->btnSetRight->show();
            btnStopReset->show();
            avControl->btnSetLeftRight->show();
            timerTitle->show();
            btnMinimize->show();

            mainHLayout->addLayout(sizeLayout);
            mainHLayout->addLayout(mainAVLayout);
            mainHLayout->addWidget(graphView);
            mainHLayout->addLayout(avSetLayout);
            mainHLayout->addLayout(mainTimerLayout);
            mainHLayout->setAlignment(mainTimerLayout, Qt::AlignRight);

            mainVLayout->addLayout(mainHLayout);

            main->setLayout(mainVLayout);
            this->setCentralWidget(main);
            this->setMaximumHeight(175);
        }
    }

    void StopWatch::selectLeftAV(int id){
        standardView = true;
        btnMaximize->show();
        avControl->btnLeftClickedWithID(id);
        emit leftAvPressed();
    }

    void StopWatch::selectRightAV(int id){
        standardView = true;
        btnMaximize->show();
        avControl->btnRightClickedWithID(id);
        emit rightAvPressed();
    }

    void StopWatch::selectAV(int id){
        standardView = true;
        btnMaximize->show();
        avControl->btnAVClickedWithID(id);
        emit avPressed();
    }
