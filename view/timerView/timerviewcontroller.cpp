#include "timerviewcontroller.h"
#include <QVBoxLayout>

TimerViewController::TimerViewController(QWidget *parent):
    QWidget(parent),
    listLeftAVs(new QList<bool>()),
    listRightAVs(new QList<bool>()),
    listBasicAVs(new QList<bool>()),
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
    connect(maxTimerView, SIGNAL(workProcessTypeChanged(int)), this, SIGNAL(workProcessTypeChanged(int)));
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
    connect(minTimerView, SIGNAL(workProcessTypeChanged(int)), this, SIGNAL(workProcessTypeChanged(int)));
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
void TimerViewController::setSelectedAV(int id){
    minTimerView->setSelectedAV(id);
    maxTimerView->setSelectedAV(id);
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
    else if(displayState == TimerDisplayState::MAXIMIZED){
        emit showGantView();
        displayState = TimerDisplayState::GANT;
    }
}

void TimerViewController::startTimer(){
    if(timerState == TimerState::IDLE || timerState == TimerState::PAUSED){
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
        listLeftAVs->clear();
        listRightAVs->clear();
        listBasicAVs->clear();
        isLeftSet = false;
        isRightSet = false;
        maxTimerView->updateGraph(listBasicAVs, listLeftAVs, listRightAVs);
        emit resetWorkProcesses();
    }
}

void TimerViewController::setTime(const QTime &time){
    minTimerView->setTime(time);
    maxTimerView->setTime(time);
}

void TimerViewController::createLeftWorkProcessRequested(){
    emit createWorkProcess(1, startTimeLeft, currentTime);
}

void TimerViewController::createRightWorkProcessRequested(){
    emit createWorkProcess(2, startTimeRight, currentTime);
}

void TimerViewController::createBasicWorkProcessRequested(){
    isBasicSet = true;
    emit createWorkProcess(3, startTimeBasic, currentTime);
}

void TimerViewController::setWorkProcessType(int id, const QString &prefix){
    minTimerView->setWorkProcessType(id, prefix);
    maxTimerView->setWorkProcessType(id, prefix);
}

void TimerViewController::changeLeft(bool b){
    isLeftSet = b;
}

void TimerViewController::changeRight(bool b){
    isRightSet = b;
}

// PRIVATE

void TimerViewController::syncTimerStates(TimerState state){
    timerState = state;
    minTimerView->setState(state);
    maxTimerView->setState(state);
}


// PROTECTED
void TimerViewController::timerEvent(QTimerEvent *event){
    currentTime = currentTime.addSecs(1);
    listLeftAVs->append(isLeftSet);
    listRightAVs->append(isRightSet);
    listBasicAVs->append(isBasicSet);
    isBasicSet = false;

    maxTimerView->updateGraph(listBasicAVs, listLeftAVs, listRightAVs);
}



