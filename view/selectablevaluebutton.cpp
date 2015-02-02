#include "selectablevaluebutton.h"
#include <QWidget>
#include <QPushButton>

SelectableValueButton::SelectableValueButton(int id, const QVariant &value, QWidget *parent) :
    QPushButton(parent),
    id(id)
{
    this->setCheckable(true);
    this->setSelected(false);
    this->setValue(value);
    connect(this, SIGNAL(clicked()), this, SLOT(btnClicked()));
}

//PRIVATE SLOTS
void SelectableValueButton::btnClicked(){
    emit clickedWithID(id);
}

//GETTER AND SETTER
void SelectableValueButton::setSelected(bool isSelected){
    this->setChecked(isSelected);
}

bool SelectableValueButton::isSelected() const{
    return this->isChecked();
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


