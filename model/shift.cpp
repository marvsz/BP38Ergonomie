#include "shift.h"

Shift::Shift(int* shiftType, QTime* start, QTime* end, QTime* cycle, int* quantity)
{
    this->setCycle(cycle);
    this->setEnd(end);
    this->setQuantity(quantity);
    this->setShiftType(shiftType);
    this->setStart(start);
}

Shift::~Shift(){

}

QTime* Shift::getCycle(){
    return this->cycle;
}

QTime* Shift::getEnd(){
    return this->end;
}

int* Shift::getQuantity(){
    return this->quantity;
}

int* Shift::getShiftType(){
    return this->shiftType;
}

QTime* Shift::getStart(){
    return this->start;
}

void Shift::setCycle(QTime* c){
    this->cycle=c;
}

void Shift::setEnd(QTime* e){
    this->end=e;
}

void Shift::setQuantity(int* q){
    this->quantity=q;
}

void Shift::setShiftType(int* st){
    this->shiftType=st;
}

void Shift::setStart(QTime* s){
    this->start=s;
}
