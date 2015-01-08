#include "timerviewcontroller.h"
#include <QVBoxLayout>

TimerViewController::TimerViewController(QWidget *parent):
    QWidget(parent),
    maxTimerView(new MaximizedTimerView(TimerState::IDLE, this)),
    minTimerView(new MinimizedTimerView(TimerState::IDLE, this))
{
    // PROPAGATE SIGNALS FROM MIN/MAX VIEW
    connect(maxTimerView, SIGNAL(nextWorkProcess()), this, SIGNAL(nextWorkProcess()));
    connect(maxTimerView, SIGNAL(previousWorkProcess()), this, SIGNAL(previousWorkProcess()));
    connect(maxTimerView, SIGNAL(workProcessTypeChanged(int)), this, SIGNAL(workProcessTypeChanged(int)));
    connect(maxTimerView, SIGNAL(play()), this, SIGNAL(play()));
    connect(maxTimerView, SIGNAL(pause()), this, SIGNAL(pause()));
    connect(maxTimerView, SIGNAL(stop()), this, SIGNAL(stop()));
    connect(maxTimerView, SIGNAL(reset()), this, SIGNAL(reset()));
    connect(maxTimerView, SIGNAL(leftSet()), this, SIGNAL(leftSet()));
    connect(maxTimerView, SIGNAL(rightSet()), this, SIGNAL(rightSet()));
    connect(maxTimerView, SIGNAL(avSet()), this, SIGNAL(avSet()));
    connect(maxTimerView, SIGNAL(durationChanged(QTime)), this, SIGNAL(durationChanged(QTime)));

    connect(minTimerView, SIGNAL(nextWorkProcess()), this, SIGNAL(nextWorkProcess()));
    connect(minTimerView, SIGNAL(previousWorkProcess()), this, SIGNAL(previousWorkProcess()));
    connect(minTimerView, SIGNAL(workProcessTypeChanged(int)), this, SIGNAL(workProcessTypeChanged(int)));
    connect(minTimerView, SIGNAL(play()), this, SIGNAL(play()));
    connect(minTimerView, SIGNAL(pause()), this, SIGNAL(pause()));

    connect(maxTimerView, SIGNAL(minimize()), this, SLOT(minimizeView()));
    connect(maxTimerView, SIGNAL(maximize()), this, SIGNAL(showGantView()));
    connect(minTimerView, SIGNAL(maximize()), this, SLOT(maximizeView()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(maxTimerView);
    mainLayout->addWidget(minTimerView);
    setLayout(mainLayout);


    maximizeView();
}


// PUBLIC SLOTS
void TimerViewController::setState(TimerState state){
    minTimerView->setState(state);
    maxTimerView->setState(state);
}

void TimerViewController::setTime(const QTime &time){
    minTimerView->setTime(time);
    maxTimerView->setTime(time);
}

void TimerViewController::setSelectedAV(int id){
    minTimerView->setSelectedAV(id);
    maxTimerView->setSelectedAV(id);
}

void TimerViewController::setWorkProcessType(int id, const QString &prefix){
    minTimerView->setWorkProcessType(id, prefix);
    maxTimerView->setWorkProcessType(id, prefix);
}

// PRIVATE SLOTS
void TimerViewController::minimizeView(){
    maxTimerView->hide();
    minTimerView->show();
}

void TimerViewController::maximizeView(){
    minTimerView->hide();
    maxTimerView->show();
}

