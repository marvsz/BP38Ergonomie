#ifndef PAUSE_H
#define PAUSE_H

#include <QTime>

class Pause
{
public:
    Pause(int* interruptions, QTime* start, QTime* end);

private:
    int* interruptions;
    QTime* start;
    QTime* end;
};

#endif // PAUSE_H
