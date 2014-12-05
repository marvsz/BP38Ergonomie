#ifndef SHIFT_H
#define SHIFT_H

#include "numberbutton.h"
#include "numberfield.h"
#include <QTime>

class Shift
{
public:
    Shift(NumberButton* shiftType, QTime* start, QTime* end, QTime* cycle, NumberField* quantity);


private:
    NumberButton* shiftType;
    QTime* start;
    QTime* end;
    QTime* cycle;
    NumberField* quantity;
};

#endif // SHIFT_H
