#include "maximizedtimerview.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include "../separator.h"
#include <QIcon>
#include <QStyle>


MaximizedTimerView::MaximizedTimerView(TimerState state, QWidget *parent) :
    QWidget(parent),
    state(state),
    lblTime(new QLabel("00:00")),
    btnMinimized(new QPushButton()),
    btnMaximized(new QPushButton()),
    btnPlayPaused(new QPushButton()),
    btnStopReset(new QPushButton()),
    btnSetLeft(new SelectableValueButton(0, 0, this)),
    btnSetRight(new SelectableValueButton(1, 1, this)),
    btnSetBoth(new SelectableValueButton(2, 2, this)),
    btnSetAV(new QPushButton("AV")),
    timePicker(new TimePicker()),
    wpSelector(new WorkProcessSelector),
    wpTypePicker(new WorkProcessTypePicker()),
    graphTimer(new GraphTimelineView())
{
    btnSetLeft->setFixedSize(45, 45);
    btnSetLeft->setText("L");
    btnSetRight->setFixedSize(45, 45);
    btnSetRight->setText("R");
    btnSetBoth->setFixedSize(45, 110);
    btnSetBoth->setText("L/R");
    btnSetAV->setFixedSize(45, 45);
    btnSetAV->setText("AV");

    btnSetBoth->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    connect(btnSetLeft, SIGNAL(clicked()), this, SLOT(btnLeftClicked()));
    connect(btnSetRight, SIGNAL(clicked()), this, SLOT(btnRightClicked()));
    connect(btnSetBoth, SIGNAL(clicked()), this, SLOT(btnBothClicked()));
    connect(btnSetAV, SIGNAL(clicked()), this, SLOT(btnAVClicked()));

    btnPlayPaused->setFixedSize(45, 45);
    btnPlayPaused->setObjectName("recordIcon");
    connect(btnPlayPaused, SIGNAL(clicked()), this, SLOT(btnPlayPausedClicked()));

    btnStopReset->setFixedSize(45, 45);
    btnStopReset->setObjectName("resetIcon");
    connect(btnStopReset, SIGNAL(clicked()), this, SLOT(btnStopResetClicked()));

    btnMinimized->setFixedSize(45, 45);
    btnMinimized->setObjectName("downIcon");
    connect(btnMinimized, SIGNAL(clicked()), this, SIGNAL(minimize()));

    btnMaximized->setFixedSize(45, 45);
    btnMaximized->setObjectName("upIcon");
    connect(btnMaximized, SIGNAL(clicked()), this, SIGNAL(maximize()));

    connect(timePicker, SIGNAL(timeChanged(QTime)), this, SIGNAL(durationChanged(QTime)));
    connect(wpSelector, SIGNAL(nextAV()), this, SIGNAL(nextWorkProcess()));
    connect(wpSelector, SIGNAL(previousAV()), this, SIGNAL(previousWorkProcess()));

    connect(wpTypePicker, SIGNAL(selectedTypeChanged(AVType)), this, SIGNAL(workProcessTypeChanged(AVType)));

    wpTypePicker->setMaximumWidth(220);
    wpSelector->setMaximumWidth(220);
    timePicker->setMaximumWidth(220);

    QVBoxLayout *minMaxLayout = new QVBoxLayout;
    minMaxLayout->addWidget(btnMaximized, 0, Qt::AlignCenter);
    minMaxLayout->addWidget(btnMinimized, 0, Qt::AlignCenter);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(minMaxLayout, 0, 0, 3, 1, 0);
    mainLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 1, 3, 1, 0);
    mainLayout->addWidget(wpTypePicker, 0, 2, 1, 1, 0);
    mainLayout->addWidget(wpSelector, 1, 2, 1, 1, 0);
    mainLayout->addWidget(timePicker, 2, 2, 1, 1, 0);
    mainLayout->addWidget(graphTimer, 0, 3, 3, 1, Qt::AlignVCenter);
    mainLayout->addWidget(btnSetLeft, 0, 4, 1, 1, 0);
    mainLayout->addWidget(btnSetRight, 1, 4, 1, 1, 0);
    mainLayout->addWidget(btnSetAV, 2, 4, 1, 1, 0);
    mainLayout->addWidget(btnSetBoth, 0, 5, 2, 1, 0);
    mainLayout->addWidget(btnPlayPaused, 0, 6, 1, 1, 0);
    mainLayout->addWidget(btnStopReset, 1, 6, 1, 1, 0);
    mainLayout->addWidget(lblTime, 2, 5, 1, 2, Qt::AlignCenter);
    mainLayout->setAlignment(btnSetBoth, Qt::AlignBottom);

    setLayout(mainLayout);
    setState(state);
}

// PUBLIC
QTime MaximizedTimerView::getDuration() const{
    return timePicker->getTime();
}


AVType MaximizedTimerView::getWorkprocessType() const{
    return wpTypePicker->getSelectedType();
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
            btnSetAV->setEnabled(false);
            btnSetLeft->setEnabled(true);
            btnSetRight->setEnabled(true);
            btnSetBoth->setEnabled(true);

            btnPlayPaused->setObjectName("recordIcon");
            btnPlayPaused->style()->unpolish(btnPlayPaused);
            btnPlayPaused->style()->polish(btnPlayPaused);
            btnPlayPaused->setEnabled(true);

            btnStopReset->setObjectName("resetIcon");
            btnStopReset->style()->unpolish(btnStopReset);
            btnStopReset->style()->polish(btnStopReset);
            btnStopReset->setEnabled(false);

            timePicker->setEnabled(false);
            break;
    case TimerState::STARTED:
            btnSetAV->setEnabled(true);
            btnSetLeft->setEnabled(true);
            btnSetRight->setEnabled(true);
            btnSetBoth->setEnabled(true);

            btnPlayPaused->setObjectName("pauseIcon");
            btnPlayPaused->style()->unpolish(btnPlayPaused);
            btnPlayPaused->style()->polish(btnPlayPaused);
            btnPlayPaused->setEnabled(true);

            btnStopReset->setObjectName("stopIcon");
            btnStopReset->style()->unpolish(btnStopReset);
            btnStopReset->style()->polish(btnStopReset);
            btnStopReset->setEnabled(true);
            break;
    case TimerState::PAUSED:
            btnSetAV->setEnabled(false);
            btnSetLeft->setEnabled(true);
            btnSetRight->setEnabled(true);
            btnSetBoth->setEnabled(true);

            btnPlayPaused->setObjectName("playIcon");
            btnPlayPaused->style()->unpolish(btnPlayPaused);
            btnPlayPaused->style()->polish(btnPlayPaused);
            btnPlayPaused->setEnabled(true);

            btnStopReset->setObjectName("stopIcon");
            btnStopReset->style()->unpolish(btnStopReset);
            btnStopReset->style()->polish(btnStopReset);
            btnStopReset->setEnabled(true);
            break;
    case TimerState::STOPPED:
            btnSetAV->setEnabled(false);
            btnSetLeft->setEnabled(false);
            btnSetRight->setEnabled(false);
            btnSetBoth->setEnabled(false);

            btnPlayPaused->setObjectName("recordIcon");
            btnPlayPaused->style()->unpolish(btnPlayPaused);
            btnPlayPaused->style()->polish(btnPlayPaused);
            btnPlayPaused->setEnabled(false);

            btnStopReset->setObjectName("resetIcon");
            btnStopReset->style()->unpolish(btnStopReset);
            btnStopReset->style()->polish(btnStopReset);
            btnStopReset->setEnabled(true);

            timePicker->setEnabled(true);
            break;
    }
}

void MaximizedTimerView::setTime(const QTime &time){
    lblTime->setText(QString("%1").arg(time.toString("mm:ss")));
}

void MaximizedTimerView::setSelectedAV(int id, const QTime &duration){
    wpSelector->setSelectedAV(id);
    timePicker->setTime(duration);
}

void MaximizedTimerView::setWorkProcessType(AVType type, const QString &prefix){
    wpTypePicker->setSelectedType(type);
    wpSelector->setAVPrefix(prefix);
}

void MaximizedTimerView::setSelectedAVNone(){
    wpSelector->setSelectedAVNone();
    timePicker->setTime(QTime(0,0));
}

void MaximizedTimerView::setHasPreviousAV(bool hasPrevious){
    wpSelector->setHasPreviousAV(hasPrevious);
}

void MaximizedTimerView::setHasNextAV(bool hasNext){
    wpSelector->setHasNextAV(hasNext);
}

void MaximizedTimerView::leftStarted(const QTime &startTime){
    graphTimer->leftStarted(startTime);
}

void MaximizedTimerView::leftEnded(const QTime &endTime){
    graphTimer->leftEnded(endTime);
}

void MaximizedTimerView::rightStarted(const QTime &startTime){
    graphTimer->rightStarted(startTime);
}

void MaximizedTimerView::rightEnded(const QTime &endTime){
    graphTimer->rightEnded(endTime);
}

void MaximizedTimerView::basicStarted(const QTime &startTime){
    graphTimer->basicStarted(startTime);
}

void MaximizedTimerView::basicEnded(const QTime &endTime){
    graphTimer->basicEnded(endTime);
}

void MaximizedTimerView::initialize(QVector<QVariant> *leftWPs, QVector<QVariant> *rightWPs, QVector<QVariant> *basicWPs){
    graphTimer->initialize(leftWPs, rightWPs, basicWPs);
}

void MaximizedTimerView::updateGraphTimeLine(const QTime &currentTime){
    graphTimer->updateGraphTimeLine(currentTime);
}

void MaximizedTimerView::leaveTimer(){
    if(state != TimerState::STOPPED)
        btnStopResetClicked();
}

void MaximizedTimerView::disableMaximize(){
    btnMaximized->setEnabled(false);
}

void MaximizedTimerView::enableMaximize(){
    btnMaximized->setEnabled(true);
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
            emit avSet();
            if(btnSetLeft->isSelected()){
                btnSetLeft->clicked();
            }
            if(btnSetRight->isSelected()){
                btnSetRight->clicked();
            }
            emit stop();
        break;
    case TimerState::PAUSED:
            emit avSet();
            if(btnSetLeft->isSelected()){
                btnSetLeft->clicked();
            }
            if(btnSetRight->isSelected()){
                btnSetRight->clicked();
            }
            emit stop();
        break;
    case TimerState::STOPPED:
            btnSetLeft->setSelected(false);
            btnSetRight->setSelected(false);
            btnSetBoth->setSelected(false);
            emit reset();
        break;
    }
}

void MaximizedTimerView::emitBothSet(){
    emit leftSet();
    emit rightSet();
}

void MaximizedTimerView::btnLeftClicked(){
    btnSetLeft->setSelected(!btnSetLeft->isSelected());
    btnSetBoth->setSelected(btnSetRight->isSelected() && btnSetLeft->isSelected());
    emit leftChanged(btnSetLeft->isSelected());
    if(!btnSetLeft->isSelected())
        emit leftSet();
}

void MaximizedTimerView::btnRightClicked(){
    btnSetRight->setSelected(!btnSetRight->isSelected());
    btnSetBoth->setSelected(btnSetRight->isSelected() && btnSetLeft->isSelected());
    emit rightChanged(btnSetRight->isSelected());
    if(!btnSetRight->isSelected())
        emit rightSet();
}

void MaximizedTimerView::btnBothClicked(){
    btnSetBoth->setSelected(!btnSetBoth->isSelected());
    if(btnSetLeft->isSelected() == btnSetRight->isSelected()){
        btnLeftClicked();
        btnRightClicked();
    }
    if(!btnSetLeft->isSelected() && btnSetRight->isSelected())
        btnLeftClicked();
    if(btnSetLeft->isSelected() && !btnSetRight->isSelected())
        btnRightClicked();

}

void MaximizedTimerView::btnAVClicked(){
    emit avSet();
}

MaximizedTimerView::~MaximizedTimerView(){
}
