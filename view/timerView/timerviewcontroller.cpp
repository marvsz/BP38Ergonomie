#include "timerviewcontroller.h"
#include <QVBoxLayout>

TimerViewController::TimerViewController(QWidget *parent):
    QWidget(parent),
    isLeftSet(false),
    isRightSet(false),
    startTimeBasic(QTime(0,0)),
    startTimeLeft(QTime(0,0)),
    startTimeRight(QTime(0,0)),
    currentTime(QTime(0,0)),
    maxTimerView(new MaximizedTimerView(TimerState::IDLE, this)),
    minTimerView(new MinimizedTimerView(TimerState::IDLE, this))
{
    // PROPAGATE SIGNALS FROM MIN/MAX VIEW
    connect(maxTimerView, SIGNAL(nextWorkProcess()), this, SIGNAL(nextWorkProcess()));
    connect(maxTimerView, SIGNAL(previousWorkProcess()), this, SIGNAL(previousWorkProcess()));
    connect(maxTimerView, SIGNAL(workProcessTypeChanged(AVType)), this, SIGNAL(workProcessTypeChanged(AVType)));
    connect(maxTimerView, SIGNAL(play()), this, SLOT(startTimer()));
    connect(maxTimerView, SIGNAL(pause()), this, SLOT(pauseTimer()));
    connect(maxTimerView, SIGNAL(stop()), this, SLOT(stopTimer()));
    connect(maxTimerView, SIGNAL(reset()), this, SLOT(resetTimer()));
    connect(maxTimerView, SIGNAL(minimize()), this, SIGNAL(hideGantView()));
    connect(maxTimerView, SIGNAL(avSet()), this, SLOT(createBasicWorkProcessRequested()));
    connect(maxTimerView, SIGNAL(leftSet()), this, SLOT(createLeftWorkProcessRequested()));
    connect(maxTimerView, SIGNAL(rightSet()), this, SLOT(createRightWorkProcessRequested()));
    connect(maxTimerView, SIGNAL(durationChanged(QTime)), this, SIGNAL(durationChanged(QTime)));

    connect(maxTimerView, SIGNAL(leftChanged(bool)), this, SLOT(changeLeft(bool)));
    connect(maxTimerView, SIGNAL(rightChanged(bool)), this, SLOT(changeRight(bool)));

    connect(minTimerView, SIGNAL(nextWorkProcess()), this, SIGNAL(nextWorkProcess()));
    connect(minTimerView, SIGNAL(previousWorkProcess()), this, SIGNAL(previousWorkProcess()));
    connect(minTimerView, SIGNAL(workProcessTypeChanged(AVType)), this, SIGNAL(workProcessTypeChanged(AVType)));
    connect(minTimerView, SIGNAL(play()), this, SLOT(startTimer()));
    connect(minTimerView, SIGNAL(pause()), this, SLOT(pauseTimer()));

    connect(maxTimerView, SIGNAL(minimize()), this, SLOT(minimizeView()));
    connect(maxTimerView, SIGNAL(maximize()), this, SLOT(maximizeView()));
    connect(minTimerView, SIGNAL(maximize()), this, SLOT(maximizeView()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(maxTimerView);
    mainLayout->addWidget(minTimerView);
    setLayout(mainLayout);

    timerState = TimerState::IDLE;
    displayState = TimerDisplayState::MINIMIZED;
    maximizeView();
}


// PUBLIC SLOTS
void TimerViewController::setSelectedAV(int id, const QTime &duration){
    minTimerView->setSelectedAV(id);
    maxTimerView->setSelectedAV(id, duration);
}

void TimerViewController::setWorkProcessLists(QVector<QVariant> *leftWPs, QVector<QVariant> *rightWPs, QVector<QVariant> *basicWPs){
    maxTimerView->initialize(leftWPs, rightWPs, basicWPs);
    if(leftWPs->count() != 0 || rightWPs->count() != 0 || basicWPs->count() != 0){
        syncTimerStates(TimerState::STOPPED);
        syncCurrentTime(basicWPs->at(basicWPs->count() -1).toTime());
    }
    else {
        syncTimerStates(TimerState::IDLE);
        syncCurrentTime(QTime(0,0));
    }
    maxTimerView->updateGraphTimeLine(currentTime);
}

void TimerViewController::setSelectedType(AVType type){
    setWorkProcessType(type, TYPE_PREFIXE.at(type - 1));
}

void TimerViewController::closeTimerView(){
    maxTimerView->leaveTimer();
    if(displayState == TimerDisplayState::GANT){
        emit hideGantView();
        displayState = TimerDisplayState::MAXIMIZED;
    }
}

// PRIVATE SLOTS
void TimerViewController::minimizeView(){
    if(displayState == TimerDisplayState::MAXIMIZED){
        maxTimerView->hide();
        minTimerView->show();
        displayState = TimerDisplayState::MINIMIZED;
    }
    else if (displayState == TimerDisplayState::GANT){
        emit hideGantView();
        displayState = TimerDisplayState::MAXIMIZED;
    }
}

void TimerViewController::maximizeView(){
    if(displayState == TimerDisplayState::MINIMIZED){
        minTimerView->hide();
        maxTimerView->show();
        displayState = TimerDisplayState::MAXIMIZED;
    }
    else if(displayState == TimerDisplayState::MAXIMIZED || displayState == TimerDisplayState::GANT){
        emit showGantView();
        displayState = TimerDisplayState::GANT;
    }
}

void TimerViewController::startTimer(){
    if(timerState == TimerState::IDLE){
        timerID = QObject::startTimer(1000);
        syncTimerStates(TimerState::STARTED);
        maxTimerView->basicStarted(currentTime);
    }
    if(timerState == TimerState::PAUSED){
        timerID = QObject::startTimer(1000);
        syncTimerStates(TimerState::STARTED);
    }

}

void TimerViewController::pauseTimer(){
    if(timerState == TimerState::STARTED){
        killTimer(timerID);
        syncTimerStates(TimerState::PAUSED);
    }
}

void TimerViewController::stopTimer(){
    if(timerState == TimerState::STARTED || timerState == TimerState::PAUSED){
        killTimer(timerID);
        syncTimerStates(TimerState::STOPPED);
    }
}

void TimerViewController::resetTimer(){
    if(timerState == TimerState::STOPPED){
        currentTime = QTime(0,0);
        setTime(currentTime);
        syncTimerStates(TimerState::IDLE);
        startTimeBasic = QTime(0,0);
        startTimeLeft = QTime(0,0);
        startTimeRight = QTime(0,0);
        isLeftSet = false;
        isRightSet = false;
        maxTimerView->updateGraphTimeLine(currentTime);
        emit resetWorkProcesses();
    }
}

void TimerViewController::setTime(const QTime &time){
    minTimerView->setTime(time);
    maxTimerView->setTime(time);
}

void TimerViewController::createLeftWorkProcessRequested(){
    maxTimerView->leftEnded(currentTime);
    emit createWorkProcess(AVType::LEFT, startTimeLeft, currentTime);
}

void TimerViewController::createRightWorkProcessRequested(){
    maxTimerView->rightEnded(currentTime);
    emit createWorkProcess(AVType::RIGHT, startTimeRight, currentTime);
}

void TimerViewController::createBasicWorkProcessRequested(){
    if(currentTime > startTimeBasic){
        isBasicSet = true;
        emit createWorkProcess(AVType::BASIC, startTimeBasic, currentTime);
        startTimeBasic = currentTime;
        maxTimerView->basicEnded(currentTime);
        maxTimerView->basicStarted(currentTime);
    }
}

void TimerViewController::setWorkProcessType(AVType type, const QString &prefix){
    minTimerView->setWorkProcessType(type, prefix);
    maxTimerView->setWorkProcessType(type, prefix);
}

void TimerViewController::changeLeft(bool b){
    isLeftSet = b;
    if(b){
        startTimeLeft = currentTime;
        maxTimerView->leftStarted(startTimeLeft);
    }
}

void TimerViewController::changeRight(bool b){
    isRightSet = b;
    if(b){
        startTimeRight = currentTime;
        maxTimerView->rightStarted(startTimeRight);
    }
}

// PRIVATE

void TimerViewController::syncTimerStates(TimerState state){
    timerState = state;
    minTimerView->setState(state);
    maxTimerView->setState(state);
}

void TimerViewController::syncCurrentTime(const QTime &currentTime){
    minTimerView->setTime(currentTime);
    maxTimerView->setTime(currentTime);
    this->currentTime = currentTime;
}

// PROTECTED
void TimerViewController::timerEvent(QTimerEvent *event){
    currentTime = currentTime.addSecs(1);
    isBasicSet = false;
    maxTimerView->setTime(currentTime);
    minTimerView->setTime(currentTime);
    maxTimerView->updateGraphTimeLine(currentTime);
}



