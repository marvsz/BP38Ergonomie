#include "maximizedtimerview.h"
#include <QGridLayout>
#include <QVBoxLayout>

const QVector<QString> MaximizedTimerView::wpTypes = QVector<QString>()<<"Links"<<"Rechts"<<"AV";

MaximizedTimerView::MaximizedTimerView(TimerState state, QWidget *parent) :
    QWidget(parent),
    state(state),
    lblTime(new QLabel("00:00")),
    btnMinimized(new QPushButton()),
    btnMaximized(new QPushButton()),
    btnPlayPaused(new QPushButton()),
    btnStopReset(new QPushButton()),
    btnSetLeft(new QPushButton("L")),
    btnSetRight(new QPushButton("R")),
    btnSetBoth(new QPushButton("L/R")),
    btnSetAV(new QPushButton("AV")),
    timePicker(new TimePicker()),
    wpSelector(new WorkProcessSelector),
    graphTimer(new GraphTimer())
{
    recordIcon = QIcon(":/timer/icons/Timer/record.png");
    playIcon = QIcon(":/timer/icons/Timer/start.png");
    pauseIcon = QIcon(":/timer/icons/Timer/pause.png");
    stopIcon = QIcon(":/timer/icons/Timer/stop.png");
    resetIcon = QIcon(":/timer/icons/Timer/reset.png");
    minimizedIcon = QIcon(":/timer/icons/Timer/minimize.png");
    maximizedIcon = QIcon(":/timer/icons/Timer/maximize.png");

    btnSetLeft->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    btnSetRight->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    btnSetBoth->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    btnSetAV->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    btnPlayPaused->setIconSize(QSize(45, 45));
    btnPlayPaused->setObjectName("btnTimer");
    connect(btnPlayPaused, SIGNAL(clicked()), this, SLOT(btnPlayPausedClicked()));

    btnStopReset->setIconSize(QSize(45, 45));
    btnStopReset->setObjectName("btnTimer");
    connect(btnStopReset, SIGNAL(clicked()), this, SLOT(btnStopResetClicked()));

    btnMinimized->setIconSize(QSize(45, 45));
    btnMinimized->setFixedSize(50, 50);
    btnMinimized->setObjectName("btnTimer");
    btnMinimized->setIcon(minimizedIcon);
    connect(btnMinimized, SIGNAL(clicked()), this, SIGNAL(minimize()));

    btnMaximized->setIconSize(QSize(45, 45));
    btnMaximized->setFixedSize(50, 50);
    btnMaximized->setObjectName("btnTimer");
    btnMaximized->setIcon(maximizedIcon);
    connect(btnMaximized, SIGNAL(clicked()), this, SIGNAL(maximize()));

    connect(timePicker, SIGNAL(timeChanged(QTime)), this, SIGNAL(durationChanged(QTime)));
    connect(wpSelector, SIGNAL(nextAV()), this, SIGNAL(nextWorkProcess()));
    connect(wpSelector, SIGNAL(previousAV()), this, SIGNAL(previousWorkProcess()));

    oscWorkProcessType = new OptionSelectionControl(wpTypes);
    connect(oscWorkProcessType, SIGNAL(selectionChanged(int)), this, SIGNAL(workProcessTypeChanged(int)));

    QVBoxLayout *minMaxLayout = new QVBoxLayout;
    minMaxLayout->addWidget(btnMaximized);
    minMaxLayout->addWidget(btnMinimized);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(minMaxLayout, 0, 0, 3, 1, 0);
    mainLayout->addWidget(oscWorkProcessType, 0, 1, 1, 1, 0);
    mainLayout->addWidget(wpSelector, 1, 1, 1, 1, 0);
    mainLayout->addWidget(timePicker, 2, 1, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 2, 3, 1, 0);
    //mainLayout->addWidget(graphTimer, 0, 2, 3, 1, 0);
    mainLayout->addWidget(btnSetLeft, 0, 3, 1, 1, 0);
    mainLayout->addWidget(btnSetRight, 1, 3, 1, 1, 0);
    mainLayout->addWidget(btnSetAV, 2, 3, 1, 1, 0);
    mainLayout->addWidget(btnSetBoth, 0, 4, 2, 1, 0);
    mainLayout->addWidget(btnPlayPaused, 0, 5, 1, 1, 0);
    mainLayout->addWidget(btnStopReset, 1, 5, 1, 1, 0);
    mainLayout->addWidget(lblTime, 2, 4, 1, 2, Qt::AlignCenter);

    setLayout(mainLayout);
    setState(state);
}

// PUBLIC
QTime MaximizedTimerView::getDuration() const{
    return timePicker->getTime();
}


QString MaximizedTimerView::getWorkprocessType() const{
    return oscWorkProcessType->getSelectedValue();
}

TimerState MaximizedTimerView::getState() const{
    return state;
}

QTime MaximizedTimerView::getTime() const {
    return QTime(0, lblTime->text().left(2).toInt(), lblTime->text().right(2).toInt(), 0);
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

void MaximizedTimerView::emitBothSet(){
    emit leftSet();
    emit rightSet();
}


MaximizedTimerView::~MaximizedTimerView(){
}
