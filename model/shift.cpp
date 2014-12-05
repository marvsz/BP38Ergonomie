#include "shift.h"

Shift::Shift(NumberButton* shiftType, QTime* start, QTime* end, QTime* cycle, NumberField* quantity)
{
    this->cycle=cycle;
    this->end=end;
    this->quantity=quantity;
    this->shiftType=shiftType;
    this->start=start;
}
