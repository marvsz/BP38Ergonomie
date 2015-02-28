#include "selectablevaluebutton.h"
#include <QWidget>
#include <QPushButton>

SelectableValueButton::SelectableValueButton(int id, const QVariant &value, QWidget *parent) :
    QPushButton(parent),
    id(id)
{
    this->setSelected(false);
    this->setValue(value);
    this->setCheckable(true);
    connect(this, SIGNAL(clicked()), this, SLOT(btnClicked()));
}

//PRIVATE SLOTS
void SelectableValueButton::btnClicked(){
    emit clickedWithID(id);
}

//GETTER AND SETTER
void SelectableValueButton::setSelected(bool isSelected){
    selected = isSelected;
    setChecked(isSelected);
    //if(selected)
    //    this->setStyleSheet("QPushButton {font: 100 18px \"Serif\"; color: #FFFFFF; border: 2px solid #007aff; border-radius: 10px; background-color: #007aff; padding: 4px;}");
    //else
    //    this->setStyleSheet("QPushButton {font: 100 18px \"Serif\"; color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f5f5; padding: 4px;}");
}

bool SelectableValueButton::isSelected() const{
    return selected;
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


