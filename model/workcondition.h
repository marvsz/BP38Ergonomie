#ifndef WORKCONDITION_H
#define WORKCONDITION_H

#include "numberbutton.h"
#include "boolbutton.h"

class WorkCondition
{
public:
    WorkCondition(BoolButton* torsoSupport, BoolButton* armSupport, NumberButton* neededPrecision, NumberButton* neededVelocity, NumberButton* neededAcceleration, NumberButton* givenVibration, NumberButton* gripCondition, NumberButton* accessibility, NumberButton* terrain, NumberButton* lighting, NumberButton* clima, NumberButton* wind, NumberButton* clothing, NumberButton* mobility);
    ~WorkCondition();

private:
    BoolButton* torsoSupport;
    BoolButton* armSupport;
    NumberButton* neededPrecision;
    NumberButton* neededVelocity;
    NumberButton* neededAcceleration;
    NumberButton* givenVibration;
    NumberButton* gripCondition;
    NumberButton* accessibility;
    NumberButton* terrain;
    NumberButton* lighting;
    NumberButton* clima;
    NumberButton* wind;
    NumberButton* clothing;
    NumberButton* mobility;
};

#endif // WORKCONDITION_H
