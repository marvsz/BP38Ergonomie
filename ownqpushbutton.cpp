#include "ownqpushbutton.h"
#include <QWidget>
#include <QString>
#include <QPushButton>

OwnQPushButton::OwnQPushButton(int id, int value, QString unitSymbol, int min, int max, QWidget *parent) :
    QPushButton(parent)
{
    this->id = id;
    this->setMin(min);
    this->setMax(max);
    this->setUnitSymbol(unitSymbol);
    this->setValue(value);
    this->setSelected(false);

    connect(this, SIGNAL(pressed()), this, SLOT(qpbtnPressed()));
}


void OwnQPushButton::setSelected(bool isSelected){
    this->isSel = isSelected;
    if(isSel)
        this->setStyleSheet(this->qssSelected);
    else
        this->setStyleSheet(this->qssNotSelected);
}
bool OwnQPushButton::isSelected() const{
    return this->isSel;
}
int OwnQPushButton::getID() const{
    return this->id;
}
int OwnQPushButton::getValue() const{
    return this->value;
}
void OwnQPushButton::setValue(int value){
    changeValue(value);
}

int OwnQPushButton::getMin() const{
    return this->min;
}
void OwnQPushButton::setMin(int min){
    this->min = min;
}

int OwnQPushButton::getMax() const{
    return this->max;
}
void OwnQPushButton::setMax(int max){
    this->max = max;
}
void OwnQPushButton::setSelectedByValue(int value){
    if(isValueInRange(value)){
        setSelected(true);
    }
    else {
        setSelected(false);
    }
}

void OwnQPushButton::setUnitSymbol(QString unitSymbol){
    this->unitSymbol = unitSymbol;
    QString s;
    s = s.number(value);
    s = s.append(" ");
    s = s.append(unitSymbol);
    this->setText(s);
}
QString OwnQPushButton::getUnitSymbol()const{
    return this->unitSymbol;
}

void OwnQPushButton::qpbtnPressed(){
    emit pressedWithID(this->id);
}

void OwnQPushButton::changeValue(int value){
    if(isValueInRange(value)){
        this->value = value;
        QString s;
        s = s.number(value);
        s = s.append(" ");
        s = s.append(unitSymbol);
        this->setText(s);
        emit this->valueChanged();
    }
}

bool OwnQPushButton::isValueInRange(int value) const{
    return value <= this->max && value >= this->min;
}
