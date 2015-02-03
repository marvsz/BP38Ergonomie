#include "timepicker.h"
#include <QHBoxLayout>
#include <QIcon>
TimePicker::TimePicker(QWidget *parent) :
    QWidget(parent),
    timeBxTime(new TimeLineEdit),
    btnIncreaseTime(new QPushButton()),
    btnDecreaseTime(new QPushButton())
{
    timeBxTime->setMinimumSize(100, 45);
    timeBxTime->setAlignment(Qt::AlignCenter);
    btnIncreaseTime->setFixedSize(45, 45);
    btnIncreaseTime->setObjectName("plusIcon");

    btnDecreaseTime->setFixedSize(45, 45);
    btnDecreaseTime->setObjectName("minusIcon");

    connect(btnIncreaseTime, SIGNAL(clicked()), this, SLOT(increaseTime()));
    connect(btnDecreaseTime, SIGNAL(clicked()), this, SLOT(decreaseTime()));
    connect(timeBxTime, SIGNAL(editingFinished()), this, SLOT(emitTimeChanged()));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(btnDecreaseTime, 0, Qt::AlignHCenter);
    mainLayout->addWidget(timeBxTime, 0, Qt::AlignHCenter);
    mainLayout->addWidget(btnIncreaseTime, 0, Qt::AlignHCenter);
    setLayout(mainLayout);
}

void TimePicker::increaseTime(){
    timeBxTime->setTime(timeBxTime->getTime().addSecs(1));
    emitTimeChanged();
}

void TimePicker::decreaseTime(){
    timeBxTime->setTime(timeBxTime->getTime().addSecs(-1));
    emitTimeChanged();
}

QTime TimePicker::getTime() const{
    return timeBxTime->getTime();
}

void TimePicker::setTime(const QTime &time){
    timeBxTime->setTime(time);
}

void TimePicker::emitTimeChanged(){
    emit timeChanged(timeBxTime->getTime());
}

TimePicker::~TimePicker(){

}
