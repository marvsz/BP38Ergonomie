#include "selectablevaluebutton.h"
#include <QWidget>

const QString SelectableValueButton::qssSelected     = "QPushButton {font: 100 18px \"Serif\"; color: #FFFFFF; border: 2px solid #007aff; border-radius: 10px; background-color: #007aff; padding: 4px;}"; //QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
const QString SelectableValueButton::qssNotSelected  = "QPushButton {font: 100 18px \"Serif\"; color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f5f5; padding: 4px;}"; //QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";


SelectableValueButton::SelectableValueButton(int id, const QVariant &value, QWidget *parent) :
    QPushButton(parent),
    id(id)
{
    this->setSelected(false);
    this->setValue(value);
    connect(this, SIGNAL(clicked()), this, SLOT(btnClicked()));
}

//PRIVATE SLOTS
void SelectableValueButton::btnClicked(){
    emit clickedWithID(this->id);
    emit clickedWithID(this->id, this);
}

//GETTER AND SETTER
void SelectableValueButton::setSelected(bool isSelected){
    this->isSel = isSelected;
    if(isSel)
        this->setStyleSheet(qssSelected);
    else
        this->setStyleSheet(qssNotSelected);
}

bool SelectableValueButton::isSelected() const{
    return this->isSel;
}

void SelectableValueButton::setID(int id){
    this->id = id;
}

int SelectableValueButton::getID() const{
    return this->id;
}

QVariant SelectableValueButton::getValue() const{
    return value;
}

void SelectableValueButton::setValue(const QVariant &value){
    this->value = value;
}



