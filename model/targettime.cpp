#include "targettime.h"

TargetTime::TargetTime(QTime* basicTime, QTime* setupTime, QTime* restTime, QTime* distributeTime)
{
    this->basicTime=basicTime;
    this->distributeTime=distributeTime;
    this->restTime=restTime;
    this->setupTime=setupTime;
}
