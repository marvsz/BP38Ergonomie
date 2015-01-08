#include "timepicker.h"
#include <QHBoxLayout>

TimePicker::TimePicker(QWidget *parent) :
    QWidget(parent),
    timeBxTime(new TimeLineEdit),
    btnIncreaseTime(new QPushButton("+")),
    btnDecreaseTime(new QPushButton("-"))
{
    connect(btnIncreaseTime, SIGNAL(clicked()), this, SLOT(increaseTime()));
    connect(btnDecreaseTime, SIGNAL(clicked()), this, SLOT(decreaseTime()));
    connect(timeBxTime, SIGNAL(editingFinished()), this, SLOT(emitTimeChanged()));
    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addWidget(btnDecreaseTime);
    mainLayout->addWidget(timeBxTime);
    mainLayout->addWidget(btnIncreaseTime);

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
