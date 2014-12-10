#include "selectablevaluebutton.h"
#include <QWidget>

const QString SelectableValueButton::qssSelected = "QPushButton {font: 100 20px \"Serif\";color: #FFFFFF; border: 2px solid #007aff; border-radius: 10px; background-color: #007aff;padding:4px;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
const QString SelectableValueButton::qssNotSelected = "QPushButton {font: 100 20px \"Serif\";color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f5f5;padding: 4px;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";


SelectableValueButton::SelectableValueButton(int id, int value, QWidget *parent) :
    QPushButton(parent)
{
    this->id = id;
    this->setSelected(false);
    this->setValue(value);
    connect(this, SIGNAL(pressed()), this, SLOT(qpbtnPressed()));
}


void SelectableValueButton::setSelected(bool isSelected){
    this->isSel = isSelected;
    if(isSel)
        this->setStyleSheet(this->qssSelected);
    else
        this->setStyleSheet(this->qssNotSelected);
}

bool SelectableValueButton::isSelected() const{
    return this->isSel;
}

int SelectableValueButton::getID() const{
    return this->id;
}

void SelectableValueButton::qpbtnPressed(){
    emit pressedWithID(this->id);
}

int SelectableValueButton::getValue(){
    return value;
}

void SelectableValueButton::setValue(int value){
    this->value = value;
}

