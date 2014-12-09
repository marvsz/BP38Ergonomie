#include "executioncondition.h"

ExecutionCondition::ExecutionCondition(General* general, Supply* supply, WorkCondition* condition)
{
    this->condition = condition;
    this->general = general;
    this->supply = supply;
}

ExecutionCondition::~ExecutionCondition(){

}

General* ExecutionCondition::getGeneral(){
    return this->general;
}

Supply* ExecutionCondition::getSupply(){
    return this->supply;
}

WorkCondition* ExecutionCondition::getWorkcondition(){
    return this->condition;
}

void ExecutionCondition::setGeneral(General* g){
    this->general=g;
}

void ExecutionCondition::setSupply(Supply* s){
    this->supply=s;
}

void ExecutionCondition::setWorkCondition(WorkCondition* c){
    this->condition=c;
}
