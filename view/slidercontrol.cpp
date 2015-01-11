#include "slidercontrol.h"

SliderControl::SliderControl(QWidget *parent) : QWidget(parent),
    lblMin(new QLabel(tr("0"))),
    lblMax(new QLabel(tr("10"))),
    lblValue(new QLabel(tr("0"))),
    sldrValue(new QSlider(Qt::Horizontal, this))
{
    sldrValue->setMinimumHeight(50);
    sldrValue->setMinimum(0);
    sldrValue->setMaximum(10);
    connect(sldrValue, SIGNAL(valueChanged(int)), this, SLOT(sldrValueChanged(int)));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(lblValue, 0, 0, 1, 3, Qt::AlignCenter);
    mainLayout->addWidget(lblMin, 1, 0, 1, 1, 0);
    mainLayout->addWidget(sldrValue, 1, 1, 1, 1, 0);
    mainLayout->addWidget(lblMax, 1, 2, 1, 1, 0);
    this->setLayout(mainLayout);

    setValue(0);
}

SliderControl::~SliderControl()
{

}


//PUBLIC SLOTS
void SliderControl::setValue(int value){
    sldrValue->setValue(value);
}


//PRIVATE SLOTS
void SliderControl::sldrValueChanged(int value){
    lblValue->setText(QString::number(value));
    emit valueChanged(value);
}

//GETTER / SETTER
void SliderControl::setMinMax(int min, int max){
    if(min < max){
        sldrValue->setMinimum(min);
        lblMin->setText(QString::number(min));
        sldrValue->setMaximum(max);
        lblMax->setText(QString::number(max));
    }
}

void SliderControl::setInterval(int interval){
    sldrValue->setTickInterval(interval);
}

int SliderControl::getValue() const{
    return sldrValue->value();
}
int SliderControl::getMin() const{
    return sldrValue->minimum();
}
int SliderControl::getMax() const{
    return sldrValue->maximum();
}

