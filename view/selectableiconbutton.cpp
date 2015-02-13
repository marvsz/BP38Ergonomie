#include "selectableiconbutton.h"

SelectableIconButton::SelectableIconButton(int id, QWidget *parent) :
    QPushButton(parent),
    id(id)
{
    connect(this, SIGNAL(clicked()), this, SLOT(btnClicked());
}

int SelectableIconButton::getID(){
    return id;
}

void SelectableIconButton::setID(int id){
    this->id = id;
}

// private slots

void SelectableIconButton::btnClicked(){
    emit clickedWithID(id);
}
