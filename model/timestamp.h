#ifndef TIMESTAMP_H
#define TIMESTAMP_H

class TimeStamp
{
public:
    TimeStamp(int minute, int second);
    ~TimeStamp();

   /* void setMinute(int m);
    void setSecond(int s);
    void setTime(int ss); */

private:
    int minute;
    int second;
    // int seconds;
};

#endif // TIMESTAMP_H
