#ifndef SHIFT_H
#define SHIFT_H

#include <QTime>

class Shift
{
public:
    Shift(int* shiftType, QTime* start, QTime* end, QTime* cycle, int* quantity);


private:
    int* shiftType;
    QTime* start;
    QTime* end;
    QTime* cycle;
    int* quantity;
};

#endif // SHIFT_H
