#ifndef SHIFTDATA_H
#define SHIFTDATA_H

#include "shift.h"
#include "targettime.h"
#include "pause.h"

class ShiftData
{
public:
    ShiftData(Shift* shift, TargetTime* targetTime, Pause* pause);


private:
    Shift* shift;
    TargetTime* targetTime;
    Pause* pause;
};

#endif // SHIFTDATA_H
