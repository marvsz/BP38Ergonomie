#include "pause.h"

Pause::Pause(int* interruptions, QTime* start, QTime* end)
{
    this->end=end;
    this->interruptions=interruptions;
    this->start=start;
}
