#include "timepicker.h"
#include <QHBoxLayout>

TimePicker::TimePicker(QWidget *parent) :
    QWidget(parent),
    timeBxTime(new TimeLineEdit),
    btnIncreaseTime(new QPushButton("+")),
    btnDecreaseTime(new QPushButton("-"))
{
    timeBxTime->setMaximumWidth(150);
    timeBxTime->setMinimumWidth(100);

    btnIncreaseTime->setFixedSize(40, 40);
    btnDecreaseTime->setFixedSize(40, 40);

    this->setMaximumWidth(230);
    this->setMinimumWidth(180);

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
