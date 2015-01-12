#include "minimizedtimerview.h"
#include "QHBoxLayout"
#include <QStyle>

const QStringList MinimizedTimerView::wpTypes = QStringList()<<"Links"<<"Rechts"<<"AV";

MinimizedTimerView::MinimizedTimerView(TimerState state, QWidget *parent) : QWidget(parent),
    lblTime(new QLabel("00:00")),
    btnMaximized(new QPushButton()),
    btnPlayPaused(new QPushButton()),
    wpSelector(new WorkProcessSelector()),
    oscWorkProcessType(new OptionSelectionControl())
{
    btnPlayPaused->setFixedSize(45, 45);
    btnPlayPaused->setObjectName("recordIcon");
    connect(btnPlayPaused, SIGNAL(clicked()), this, SLOT(btnPlayPausedClicked()));

    btnMaximized->setFixedSize(45, 45);
    btnMaximized->setObjectName("upIcon");

    connect(btnMaximized, SIGNAL(clicked()), this, SIGNAL(maximize()));
    connect(wpSelector, SIGNAL(nextAV()), this, SIGNAL(nextWorkProcess()));
    connect(wpSelector, SIGNAL(previousAV()), this, SIGNAL(previousWorkProcess()));

    oscWorkProcessType->setValues(wpTypes);
    connect(oscWorkProcessType, SIGNAL(selectionChanged(int)), this, SIGNAL(workProcessTypeChanged(int)));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(btnMaximized, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(oscWorkProcessType, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(wpSelector, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    mainLayout->addWidget(lblTime, 0, Qt::AlignCenter);
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    mainLayout->addWidget(btnPlayPaused, 0, Qt::AlignCenter);

    this->setLayout(mainLayout);
    setState(state);
}

//PUBLIC

QString MinimizedTimerView::getWorkprocessType() const{
    return oscWorkProcessType->getSelectedValue().toString();
}

TimerState MinimizedTimerView::getState() const{
    return state;
}

QTime MinimizedTimerView::getTime() const {
    return QTime(0, lblTime->text().left(2).toInt(), lblTime->text().right(2).toInt(), 0);
}

//PUBLIC SLOTS
void MinimizedTimerView::setState(TimerState state){
    this->state = state;
    switch(state){
    case TimerState::IDLE:
        btnPlayPaused->setEnabled(true);
        btnPlayPaused->setObjectName("playIcon");
        btnPlayPaused->style()->unpolish(btnPlayPaused);
        btnPlayPaused->style()->polish(btnPlayPaused);
        break;
    case TimerState::STARTED:
        btnPlayPaused->setObjectName("pauseIcon");
        btnPlayPaused->style()->unpolish(btnPlayPaused);
        btnPlayPaused->style()->polish(btnPlayPaused);
        break;
    case TimerState::PAUSED:
        btnPlayPaused->setObjectName("playIcon");
        btnPlayPaused->style()->unpolish(btnPlayPaused);
        btnPlayPaused->style()->polish(btnPlayPaused);
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

