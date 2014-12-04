#ifndef EXECUTIONCONDITION_H
#define EXECUTIONCONDITION_H

#include "general.h"
#include "supply.h"
#include "workcondition.h"

class ExecutionCondition
{
public:
    ExecutionCondition(General* general, Supply* supply, WorkCondition* condition);
    ~ExecutionCondition();

private:
    General* general;
    Supply* supply;
    WorkCondition* condition;
};

#endif // EXECUTIONCONDITION_H
