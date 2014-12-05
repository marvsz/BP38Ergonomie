#ifndef PAUSE_H
#define PAUSE_H

#include "numberbutton.h"
#include <QTime>

class Pause
{
public:
    Pause(NumberButton* interruptions, QTime* start, QTime* end);

private:
    NumberButton* interruptions;
    QTime* start;
    QTime* end;
};

#endif // PAUSE_H
