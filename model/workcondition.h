#ifndef WORKCONDITION_H
#define WORKCONDITION_H


class WorkCondition
{
public:
    WorkCondition(bool* torsoSupport, bool* armSupport, int* neededPrecision, int* neededVelocity, int* neededAcceleration, int* givenVibration, int* gripCondition, int* accessibility, int* terrain, int* lighting, int* clima, int* wind, int* clothing, int* mobility);
    ~WorkCondition();

private:
    bool* torsoSupport;
    bool* armSupport;
    int* neededPrecision;
    int* neededVelocity;
    int* neededAcceleration;
    int* givenVibration;
    int* gripCondition;
    int* accessibility;
    int* terrain;
    int* lighting;
    int* clima;
    int* wind;
    int* clothing;
    int* mobility;
};

#endif // WORKCONDITION_H
