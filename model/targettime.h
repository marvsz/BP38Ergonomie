#ifndef TARGETTIME_H
#define TARGETTIME_H

#include <QTime>

class TargetTime
{
public:
    TargetTime(QTime* basicTime, QTime* setupTime, QTime* restTime, QTime* distributeTime);

    void setBasicTime(QTime* bt);
    void setSetupTime(QTime* st);
    void setRestTime(QTime* rt);
    void setDistributeTime(QTime* dt);

private:
    QTime* basicTime;
    QTime* setupTime;
    QTime* restTime;
    QTime* distributeTime;
};

#endif // TARGETTIME_H
