#include "spaceritemtimer.h"

SpacerItemTimer::SpacerItemTimer(int duration, int width, int height, QSizePolicy::Policy horPol, QSizePolicy::Policy verPol):
    QSpacerItem(width, height, horPol, verPol),
    duration(duration)
{

}

SpacerItemTimer::~SpacerItemTimer()
{

}


int SpacerItemTimer::getDuration() const{
    return duration;
}
void SpacerItemTimer::setDuration(int value){
    duration = value;
}
