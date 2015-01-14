#ifndef SPACERITEMTIMER_H
#define SPACERITEMTIMER_H

#include <QSpacerItem>


class SpacerItemTimer : public QSpacerItem
{
public:
    explicit SpacerItemTimer(int duration, int width, int height, QSizePolicy::Policy horPol, QSizePolicy::Policy verPol);
    ~SpacerItemTimer();

    int getDuration() const;
    void setDuration(int value);

private:
    int duration;
};

#endif // SPACERITEMTIMER_H
