#include "buttonwithid.h"
#include <QWidget>

ButtonWithID::ButtonWithID(int id, QWidget *parent) :
    QPushButton(parent)
{
    this->id = id;
    this->setSelected(false);

    connect(this, SIGNAL(pressed()), this, SLOT(qpbtnPressed()));
}


void ButtonWithID::setSelected(bool isSelected){
    this->isSel = isSelected;
    if(isSel)
        this->setStyleSheet(this->qssSelected);
    else
        this->setStyleSheet(this->qssNotSelected);
}

bool ButtonWithID::isSelected() const{
    return this->isSel;
}

int ButtonWithID::getID() const{
    return this->id;
}

void ButtonWithID::qpbtnPressed(){
    emit pressedWithID(this->id);
}
