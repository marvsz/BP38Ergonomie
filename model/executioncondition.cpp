#include "executioncondition.h"

ExecutionCondition::ExecutionCondition(General* general, Supply* supply, WorkCondition* condition)
{
    this->condition = condition;
    this->general = general;
    this->supply = supply;
}
