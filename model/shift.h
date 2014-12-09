#ifndef SHIFT_H
#define SHIFT_H

#include <QTime>

class Shift
{
public:
    Shift(int* shiftType, QTime* start, QTime* end, QTime* cycle, int* quantity);
    ~Shift();

    void setShiftType(int* st);
    void setStart(QTime* s);
    void setEnd(QTime* e);
    void setCycle(QTime* c);
    void setQuantity(int* q);

    int* getShiftType();
    QTime* getStart();
    QTime* getEnd();
    QTime* getCycle();
    int* getQuantity();


private:
    int* shiftType;
    QTime* start;
    QTime* end;
    QTime* cycle;
    int* quantity;
};

#endif // SHIFT_H
