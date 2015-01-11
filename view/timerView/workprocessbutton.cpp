#include "workprocessbutton.h"

WorkProcessButton::WorkProcessButton(int id, int value, const QTime &start, const QTime &end, QWidget *parent) : SelectableValueButton(id, value, parent),
    start(start),
    end(end)
{
    connect(this, SIGNAL(clicked()), this, SLOT(btnClicked()));
}

WorkProcessButton::~WorkProcessButton()
{

}


//PRIVATE SLOTS
void WorkProcessButton::btnClicked(){
    emit clickedWithIDValue(getID(), getValue().toInt());
}


//GETTER SETTER
QTime WorkProcessButton::getEndTime() const{
    return end;
}

void WorkProcessButton::setEndTime(const QTime &end){
    this->end = end;
}

QTime WorkProcessButton::getStartTime() const{
    return start;
}

void WorkProcessButton::setStartTime(const QTime &start){
    this->start = start;
}
