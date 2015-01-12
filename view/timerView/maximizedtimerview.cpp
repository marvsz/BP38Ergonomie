#include "maximizedtimerview.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include "separator.h"
#include <QIcon>
#include <QStyle>

const QStringList MaximizedTimerView::wpTypes = QStringList()<<"Links"<<"Rechts"<<"AV";

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
    oscWorkProcessType(new OptionSelectionControl()),
    graphTimer(new GraphTimelineView())
{
    btnSetLeft->setFixedSize(45, 45);
    btnSetLeft->setText("L");
    btnSetRight->setFixedSize(45, 45);
    btnSetRight->setText("R");
    btnSetBoth->setFixedWidth(45);
    btnSetBoth->setText("L/R");
    btnSetAV->setFixedSize(45, 45);
    btnSetAV->setText("AV");

    btnSetBoth->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

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

    oscWorkProcessType->setValues(wpTypes);
    connect(oscWorkProcessType, SIGNAL(selectionChanged(int)), this, SIGNAL(workProcessTypeChanged(int)));

    oscWorkProcessType->setMaximumWidth(220);
    wpSelector->setMaximumWidth(220);
    timePicker->setMaximumWidth(220);

    QVBoxLayout *minMaxLayout = new QVBoxLayout;
    minMaxLayout->addWidget(btnMaximized, 0, Qt::AlignCenter);
    minMaxLayout->addWidget(btnMinimized, 0, Qt::AlignCenter);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(minMaxLayout, 0, 0, 3, 1, 0);
    mainLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 1, 3, 1, 0);
    mainLayout->addWidget(oscWorkProcessType, 0, 2, 1, 1, 0);
    mainLayout->addWidget(wpSelector, 1, 2, 1, 1, 0);
    mainLayout->addWidget(timePicker, 2, 2, 1, 1, 0);
    mainLayout->addWidget(graphTimer, 0, 3, 3, 1, Qt::AlignVCenter);
    mainLayout->addWidget(btnSetLeft, 0, 4, 1, 1, 0);
    mainLayout->addWidget(btnSetRight, 1, 4, 1, 1, 0);
    mainLayout->addWidget(btnSetAV, 2, 4, 1, 1, 0);
    mainLayout->addWidget(btnSetBoth, 0, 5, 2, 1, 0);
    mainLayout->addWidget(btnPlayPaused, 0, 6, 1, 1, 0);
    mainLayout->addWidget(btnStopReset, 1, 6, 1, 1, 0);
    mainLayout->addWidget(lblTime, 2, 5, 1, 2, 0);

    setLayout(mainLayout);
    setState(state);
}

// PUBLIC
QTime MaximizedTimerView::getDuration() const{
    return timePicker->getTime();
}


QString MaximizedTimerView::getWorkprocessType() const{
    return oscWorkProcessType->getSelectedValue().toString();
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
            btnStopReset->setObjectName("resetIcon");
            btnPlayPaused->style()->unpolish(btnPlayPaused);
            btnPlayPaused->style()->polish(btnPlayPaused);
            btnStopReset->style()->unpolish(btnStopReset);
            btnStopReset->style()->polish(btnStopReset);
            btnPlayPaused->setEnabled(true);
            btnStopReset->setEnabled(false);
        break;
    case TimerState::STARTED:
            btnSetAV->setEnabled(true);

            btnPlayPaused->setObjectName("pauseIcon");
            btnStopReset->setObjectName("stopIcon");

            btnPlayPaused->style()->unpolish(btnPlayPaused);
            btnPlayPaused->style()->polish(btnPlayPaused);
            btnStopReset->style()->unpolish(btnStopReset);
            btnStopReset->style()->polish(btnStopReset);

            btnStopReset->setEnabled(true);
        break;
    case TimerState::PAUSED:
            btnSetAV->setEnabled(false);

            btnPlayPaused->setObjectName("playIcon");
            btnStopReset->setObjectName("stopIcon");

            btnPlayPaused->style()->unpolish(btnPlayPaused);
            btnPlayPaused->style()->polish(btnPlayPaused);
            btnStopReset->style()->unpolish(btnStopReset);
            btnStopReset->style()->polish(btnStopReset);

        break;
    case TimerState::STOPPED:
            btnSetAV->setEnabled(false);
            btnSetLeft->setEnabled(false);
            btnSetRight->setEnabled(false);
            btnSetBoth->setEnabled(false);

            btnStopReset->setObjectName("resetIcon");
            btnStopReset->style()->unpolish(btnStopReset);
            btnStopReset->style()->polish(btnStopReset);
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

void MaximizedTimerView::updateGraph(QList<bool> *lstAV, QList<bool> *lstLeftAVs, QList<bool> *lstRightAVs){
    graphTimer->updateGraph(lstAV, lstLeftAVs, lstRightAVs);
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
