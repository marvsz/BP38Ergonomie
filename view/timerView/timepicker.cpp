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
    timeBxTime->setValue(timeBxTime->getValue().addSecs(1));
    emitTimeChanged();
}

void TimePicker::decreaseTime(){
    timeBxTime->setValue(timeBxTime->getValue().addSecs(-1));
    emitTimeChanged();
}

QTime TimePicker::getTime() const{
    return timeBxTime->getValue();
}

void TimePicker::setTime(const QTime &time){
    timeBxTime->setValue(time);
}

void TimePicker::emitTimeChanged(){
    emit timeChanged(timeBxTime->getValue());
}

TimePicker::~TimePicker(){

}
