#include "pause.h"

Pause::Pause(int* interruptions, QTime* start, QTime* end)
{
    this->setEnd(end);
    this->setInterruptions(interruptions);
    this->setStart(start);
}

Pause::~Pause(){

}

int* Pause::getInterruptions(){
    return this->interruptions;
}

QTime* Pause::getEnd(){
    return this->end;
}

QTime* Pause::getStart(){
    return this->start;
}

void Pause::setEnd(QTime *e){
    this->end=e;
}

void Pause::setInterruptions(int *i){
    this->interruptions=i;
}

void Pause::setStart(QTime *s){
    this->start=s;
}
