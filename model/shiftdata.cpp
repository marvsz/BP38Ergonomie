#include "shiftdata.h"

ShiftData::ShiftData(Shift* shift, TargetTime* targetTime, Pause* pause)
{
    this->shift = shift;
    this->pause = pause;
    this->targetTime = targetTime;
}
