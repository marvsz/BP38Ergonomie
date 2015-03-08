#include "timerviewcontroller.h"
#include <QVBoxLayout>
#include "../../databaseHandler/dbconstants.h"

TimerViewController::TimerViewController(QWidget *parent):
    QWidget(parent),
    isLeftSet(false),
    isRightSet(false),
    isGantShown(false),
    startTimeBasic(QTime(0,0)),
    startTimeLeft(QTime(0,0)),
    startTimeRight(QTime(0,0)),
    currentTime(QTime(0,0)),
    maxTimerView(new MaximizedTimerView(TimerState::IDLE, this)),
    minTimerView(new MinimizedTimerView(TimerState::IDLE, this))
{
    // PROPAGATE SIGNALS FROM MIN/MAX VIEW
    connect(maxTimerView, SIGNAL(nextWorkProcess()), this, SIGNAL(selectNextWorkProcess()));
    connect(maxTimerView, SIGNAL(previousWorkProcess()), this, SIGNAL(selectPreviousWorkProcess()));
    connect(maxTimerView, SIGNAL(workProcessTypeChanged(AVType)), this, SIGNAL(workProcessTypeChanged(AVType)));
    connect(maxTimerView, SIGNAL(play()), this, SLOT(startTimer()));
    connect(maxTimerView, SIGNAL(pause()), this, SLOT(pauseTimer()));
    connect(maxTimerView, SIGNAL(stop()), this, SLOT(stopTimer()));
    connect(maxTimerView, SIGNAL(reset()), this, SLOT(resetTimer()));
    connect(maxTimerView, SIGNAL(avSet()), this, SLOT(createBasicWorkProcessRequested()));
    connect(maxTimerView, SIGNAL(leftSet()), this, SLOT(createLeftWorkProcessRequested()));
    connect(maxTimerView, SIGNAL(rightSet()), this, SLOT(createRightWorkProcessRequested()));
    connect(maxTimerView, SIGNAL(durationChanged(QTime)), this, SIGNAL(workProcessDurationChanged(QTime)));

    connect(maxTimerView, SIGNAL(leftChanged(bool)), this, SLOT(changeLeft(bool)));
    connect(maxTimerView, SIGNAL(rightChanged(bool)), this, SLOT(changeRight(bool)));

    connect(minTimerView, SIGNAL(nextWorkProcess()), this, SIGNAL(selectNextWorkProcess()));
    connect(minTimerView, SIGNAL(previousWorkProcess()), this, SIGNAL(selectPreviousWorkProcess()));
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
void TimerViewController::setSelectedWorkProcess(QHash<QString, QVariant> values){
    if(values.value(DBConstants::COL_WORK_PROCESS_ID).toInt() != 0){
        QTime duration = QTime(0,0).addSecs(values.value(DBConstants::COL_WORK_PROCESS_BEGIN).toTime().secsTo(values.value(DBConstants::COL_WORK_PROCESS_END).toTime()));
        minTimerView->setSelectedAV(values.value(DBConstants::COL_WORK_PROCESS_ID).toInt());
        maxTimerView->setSelectedAV(values.value(DBConstants::COL_WORK_PROCESS_ID).toInt(), duration);
    } else
        setSelectedWorkprocessNone();
}

void TimerViewController::setHasPreviousWorkProcess(bool hasPrevious){
    maxTimerView->setHasPreviousAV(hasPrevious);
    minTimerView->setHasPreviousAV(hasPrevious);
}

void TimerViewController::setHasNextWorkProcess(bool hasNext){
    maxTimerView->setHasNextAV(hasNext);
    minTimerView->setHasNextAV(hasNext);
}

void TimerViewController::setSelectedWorkProcessType(AVType type){
    setWorkProcessType(type, TYPE_PREFIXE.at(type - 1));
}

void TimerViewController::initiliazedWorkProcesses(QList<QHash<QString, QVariant>> values){
    QVector<QVariant> *leftWorkProcesses = new QVector<QVariant>();
    QVector<QVariant> *rightWorkProcesses = new QVector<QVariant>();
    QVector<QVariant> *basicWorkProcesses = new QVector<QVariant>();

    for(int i = 0; i < values.count(); ++i){
        QHash<QString, QVariant> row = values.at(i);
        int type = row.value(DBConstants::COL_WORK_PROCESS_TYPE).toInt();
        QVariant id = row.value(DBConstants::COL_WORK_PROCESS_ID);
        QVariant start = row.value(DBConstants::COL_WORK_PROCESS_BEGIN);
        QVariant end = row.value(DBConstants::COL_WORK_PROCESS_END);
        if(type == 1){
            leftWorkProcesses->append(id);
            leftWorkProcesses->append(start);
            leftWorkProcesses->append(end);
        }
        else if(type == 2){
            rightWorkProcesses->append(id);
            rightWorkProcesses->append(start);
            rightWorkProcesses->append(end);
        }
        else{
            basicWorkProcesses->append(id);
            basicWorkProcesses->append(start);
            basicWorkProcesses->append(end);
        }

    }
    maxTimerView->initialize(leftWorkProcesses, rightWorkProcesses, basicWorkProcesses);
    if(leftWorkProcesses->count() != 0 || rightWorkProcesses->count() != 0 || basicWorkProcesses->count() != 0){
        syncTimerStates(TimerState::STOPPED);
        syncCurrentTime(basicWorkProcesses->at(basicWorkProcesses->count() -1).toTime());
    }
    else {
        syncTimerStates(TimerState::IDLE);
        syncCurrentTime(QTime(0,0));
    }
    maxTimerView->updateGraphTimeLine(currentTime);
}

//OLD STUFF
void TimerViewController::gantViewShown(){
    maxTimerView->disableMaximize();
    isGantShown = true;
}

void TimerViewController::gantViewHidden(){
    maxTimerView->enableMaximize();
    isGantShown = false;
}

void TimerViewController::closeTimerView(){
    maxTimerView->leaveTimer();
    if(isGantShown)
        emit hideGantView();
}

// PRIVATE SLOTS
void TimerViewController::setSelectedWorkprocessNone(){
    maxTimerView->setSelectedAVNone();
    minTimerView->setSelectedAVNone();
}

void TimerViewController::minimizeView(){
    if (isGantShown){
        emit hideGantView();
        displayState = TimerDisplayState::MAXIMIZED;
    }
    else if(!isGantShown){
        maxTimerView->hide();
        minTimerView->show();
        displayState = TimerDisplayState::MINIMIZED;
    }
}

void TimerViewController::maximizeView(){
    if(displayState == TimerDisplayState::MINIMIZED){
        minTimerView->hide();
        maxTimerView->show();
        displayState = TimerDisplayState::MAXIMIZED;
    }
    else if(displayState == TimerDisplayState::MAXIMIZED && !isGantShown)
        emit showGantView();
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
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORK_PROCESS_TYPE, AVType::LEFT);
    values.insert(DBConstants::COL_WORK_PROCESS_BEGIN, startTimeLeft);
    values.insert(DBConstants::COL_WORK_PROCESS_END, currentTime);
    emit createWorkProcess(values);
}

void TimerViewController::createRightWorkProcessRequested(){
    maxTimerView->rightEnded(currentTime);
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_WORK_PROCESS_TYPE, AVType::RIGHT);
    values.insert(DBConstants::COL_WORK_PROCESS_BEGIN, startTimeRight);
    values.insert(DBConstants::COL_WORK_PROCESS_END, currentTime);
    emit createWorkProcess(values);
}

void TimerViewController::createBasicWorkProcessRequested(){
    if(currentTime > startTimeBasic){
        isBasicSet = true;
        QHash<QString, QVariant> values = QHash<QString, QVariant>();
        values.insert(DBConstants::COL_WORK_PROCESS_TYPE, AVType::BASIC);
        values.insert(DBConstants::COL_WORK_PROCESS_BEGIN, startTimeBasic);
        values.insert(DBConstants::COL_WORK_PROCESS_END, currentTime);
        emit createWorkProcess(values);
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
void TimerViewController::timerEvent(QTimerEvent *){
    currentTime = currentTime.addSecs(1);
    isBasicSet = false;
    maxTimerView->setTime(currentTime);
    minTimerView->setTime(currentTime);
    maxTimerView->updateGraphTimeLine(currentTime);
}




