#ifndef PAUSE_H
#define PAUSE_H

#include <QTime>

class Pause
{
public:
    Pause(int* interruptions, QTime* start, QTime* end);
    ~Pause();

    void setInterruptions(int* i);
    void setStart(QTime* s);
    void setEnd(QTime* e);

    int* getInterruptions();
    QTime* getStart();
    QTime* getEnd();


private:
    int* interruptions;
    QTime* start;
    QTime* end;
};

#endif // PAUSE_H
