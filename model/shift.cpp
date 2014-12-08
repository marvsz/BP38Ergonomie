#include "shift.h"

Shift::Shift(int* shiftType, QTime* start, QTime* end, QTime* cycle, int* quantity)
{
    this->cycle=cycle;
    this->end=end;
    this->quantity=quantity;
    this->shiftType=shiftType;
    this->start=start;
}
