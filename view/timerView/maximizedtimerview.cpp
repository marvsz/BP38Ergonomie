#include "maximizedtimerview.h"

const QVector<QString> MaximizedTimerView::wpTypes = QVector<QString>()<<"Links"<<"Rechts"<<"AV";

const QIcon MaximizedTimerView::recordIcon = QIcon(":/timer/icons/Timer/record.png");
const QIcon MaximizedTimerView::playIcon = QIcon(":/timer/icons/Timer/start.png");
const QIcon MaximizedTimerView::pauseIcon = QIcon(":/timer/icons/Timer/pause.png");
const QIcon MaximizedTimerView::stopIcon = QIcon(":/timer/icons/Timer/stop.png");
const QIcon MaximizedTimerView::resetIcon = QIcon(":/timer/icons/Timer/reset.png");

MaximizedTimerView::MaximizedTimerView(TimerState state, QWidget *parent) :
    QWidget(parent),
    state(state),
    lblTime(new QLabel("00:00")),
    btnMinimized(new QPushButton()),
    btnMaximized(new QPushButton()),
    btnPlayPaused(new QPushButton()),
    btnStopReset(new QPushButton()),
    btnSetLeft(new QPushButton()),
    btnSetRight(new QPushButton()),
    btnSetBoth(new QPushButton()),
    btnSetAV(new QPushButton()),
    timePicker(new TimePicker
               ()),
    wpSelector(new WorkProcessSelector),
    graphTimer(new GraphTimer())
{
    btnPlayPaused->setIconSize(QSize(45, 45));
    btnPlayPaused->setObjectName("btnTimer");
    connect(btnPlayPaused, SIGNAL(clicked()), this, SLOT(btnPlayPausedClicked()));

    btnStopReset->setIconSize(QSize(45, 45));
    btnStopReset->setObjectName("btnTimer");
    connect(btnStopReset, SIGNAL(clicked()), this, SLOT(btnStopResetClicked()));

    btnMinimized->setIconSize(QSize(45, 45));
    btnMinimized->setObjectName("btnTimer");
    connect(btnMinimized, SIGNAL(clicked()), this, SIGNAL(minimize()));

    btnMaximized->setIconSize(QSize(45, 45));
    btnMaximized->setObjectName("btnTimer");
    connect(btnMaximized, SIGNAL(clicked()), this, SIGNAL(maximize()));

    connect(timePicker, SIGNAL(timeChanged(QTime)), this, SIGNAL(durationChanged(QTime)));
    connect(wpSelector, SIGNAL(nextAV()), this, SIGNAL(nextWorkProcess()));
    connect(wpSelector, SIGNAL(previousAV()), this, SIGNAL(previousWorkProcess()));

    oscWorkProcessType = new OptionSelectionControl(wpTypes);
    connect(oscWorkProcessType, SIGNAL(selectionChanged(int)), this, SIGNAL(workProcessTypeChanged(int)));

    QGridLayout *mainLayout = new QGridLayout;

    setLayout(mainLayout);

}

// PUBLIC SLOTS

void MaximizedTimerView::setState(TimerState state){
    this->state = state;
    switch(state){
    case TimerState::IDLE:
            btnPlayPaused->setIcon(recordIcon);
            btnStopReset->setIcon(resetIcon);
            btnPlayPaused->setEnabled(true);
            btnStopReset->setEnabled(false);
        break;
    case TimerState::STARTED:
            btnPlayPaused->setIcon(pauseIcon);
            btnStopReset->setIcon(resetIcon);
            btnStopReset->setEnabled(true);
        break;
    case TimerState::PAUSED:
            btnPlayPaused->setIcon(playIcon);
            btnStopReset->setIcon(stopIcon);
        break;
    case TimerState::STOPPED:
            btnStopReset->setIcon(resetIcon);
            btnPlayPaused->setEnabled(false);
        break;
    }
}

void MaximizedTimerView::setTime(const QTime &time){
    lblTime->setText(QString("%1:%2").arg(time.minute()).arg(time.second()));
}

void MaximizedTimerView::setSelectedAV(int id){
    wpSelector->setSelectedAV(id);
}

void MaximizedTimerView::setWorkProcessType(int id, const QString &prefix){
    oscWorkProcessType->setSelectedValue(id);
    wpSelector->setAVPrefix(prefix);
}

// PRIVATE SLOTS
void MaximizedTimerView::btnPlayPausedClicked(){
    switch(state){
    case TimerState::IDLE:
            emit play();
        break;
    case TimerState::STARTED:
            emit pause();
        break;
    case TimerState::PAUSED:
            emit play();
        break;
    case TimerState::STOPPED:
        break;
    }
}

void MaximizedTimerView::btnStopResetClicked(){
    switch(state){
    case TimerState::IDLE:
        break;
    case TimerState::STARTED:
            emit stop();
        break;
    case TimerState::PAUSED:
            emit stop();
        break;
    case TimerState::STOPPED:
            emit reset();
        break;
    }
}

MaximizedTimerView::~MaximizedTimerView(){

}
