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

    void setGeneral(General* g);
    void setSupply(Supply* s);
    void setWorkCondition(WorkCondition* c);

    General* getGeneral();
    Supply* getSupply();
    WorkCondition* getWorkcondition();

private:
    General* general;
    Supply* supply;
    WorkCondition* condition;
};

#endif // EXECUTIONCONDITION_H
