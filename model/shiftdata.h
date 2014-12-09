#ifndef SHIFTDATA_H
#define SHIFTDATA_H

#include "shift.h"
#include "targettime.h"
#include "pause.h"

class ShiftData
{
public:
    ShiftData(Shift* shift, TargetTime* targetTime, Pause* pause);
    ~ShiftData();

    void setShift(Shift* s);
    void setTargetTime(TargetTime* t);
    void setPause(Pause* p);

    Shift* getShift();
    TargetTime* getTargetTime();
    Pause* getPause();


private:
    Shift* shift;
    TargetTime* targetTime;
    Pause* pause;
};

#endif // SHIFTDATA_H
