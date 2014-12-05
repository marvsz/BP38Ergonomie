#ifndef TARGETTIME_H
#define TARGETTIME_H

#import <QTime>

class TargetTime
{
public:
    TargetTime(QTime* basicTime, QTime* setupTime, QTime* restTime, QTime* distributeTime);

private:
    QTime* basicTime;
    QTime* setupTime;
    QTime* restTime;
    QTime* distributeTime;
};

#endif // TARGETTIME_H
