#include "head.h"

Head::Head()
{
    setTiltAngle(0);
    setTiltSidewaysAngle(0);
    setTwistAngle(0);
}

int Head::getTiltAngle() const{
    return tiltAngle;
}
void Head::setTiltAngle(int angle){
    tiltAngle = angle;
}

int Head::getTiltSidewaysAngle() const{
    return tiltSidewaysAngle;
}
void Head::setTiltSidewaysAngle(int angle){
    tiltSidewaysAngle = angle;
}

int Head::getTwistAngle() const{
    return twistAngle;
}
void Head::setTwistAngle(int angle){
    twistAngle = angle;
}
