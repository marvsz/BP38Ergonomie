#include "minimizedtimerview.h"
#include "QHBoxLayout"

const QVector<QString> MinimizedTimerView::wpTypes = QVector<QString>()<<"Links"<<"Rechts"<<"AV";

MinimizedTimerView::MinimizedTimerView(TimerState state, QWidget *parent) : QWidget(parent),
    lblTime(new QLabel("00:00")),
    btnMaximized(new QPushButton()),
    btnPlayPaused(new QPushButton()),
    wpSelector(new WorkProcessSelector())
{
    recordIcon = QIcon(":/timer/icons/Timer/record.png");
    playIcon = QIcon(":/timer/icons/Timer/start.png");
    pauseIcon = QIcon(":/timer/icons/Timer/pause.png");
    maximizedIcon = QIcon(":/timer/icons/Timer/maximize.png");

    btnPlayPaused->setIconSize(QSize(45, 45));
    btnPlayPaused->setObjectName("btnTimer");
    connect(btnPlayPaused, SIGNAL(clicked()), this, SLOT(btnPlayPausedClicked()));

    btnMaximized->setIconSize(QSize(45, 45));
    btnMaximized->setObjectName("btnTimer");
    connect(btnMaximized, SIGNAL(clicked()), this, SIGNAL(maximize()));

    connect(wpSelector, SIGNAL(nextAV()), this, SIGNAL(nextWorkProcess()));
    connect(wpSelector, SIGNAL(previousAV()), this, SIGNAL(previousWorkProcess()));

    oscWorkProcessType = new OptionSelectionControl(wpTypes);
    connect(oscWorkProcessType, SIGNAL(selectionChanged(int)), this, SIGNAL(workProcessTypeChanged(int)));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(btnMaximized);
    mainLayout->addWidget(oscWorkProcessType);
    mainLayout->addWidget(wpSelector);
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    mainLayout->addWidget(lblTime);
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    mainLayout->addWidget(btnPlayPaused);

    this->setLayout(mainLayout);
    setState(state);
}

//PUBLIC SLOTS
void MinimizedTimerView::setState(TimerState state){
    this->state = state;
    switch(state){
    case TimerState::IDLE:
            btnPlayPaused->setIcon(recordIcon);
            btnPlayPaused->setEnabled(true);
        break;
    case TimerState::STARTED:
            btnPlayPaused->setIcon(pauseIcon);
        break;
    case TimerState::PAUSED:
            btnPlayPaused->setIcon(playIcon);
        break;
    case TimerState::STOPPED:
            btnPlayPaused->setEnabled(false);
        break;
    }
}

void MinimizedTimerView::setTime(const QTime &time){
    lblTime->setText(QString("%1:%2").arg(time.minute()).arg(time.second()));
}

void MinimizedTimerView::setSelectedAV(int id){
    wpSelector->setSelectedAV(id);
}

void MinimizedTimerView::setWorkProcessType(int id, const QString &prefix){
    oscWorkProcessType->setSelectedValue(id);
    wpSelector->setAVPrefix(prefix);
}

//PRIVATE SLOTS
void MinimizedTimerView::btnPlayPausedClicked(){
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

MinimizedTimerView::~MinimizedTimerView(){
}

