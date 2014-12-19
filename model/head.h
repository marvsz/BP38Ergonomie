#ifndef HEAD_H
#define HEAD_H

class Head
{
public:
    Head();

    int getTiltAngle() const;
    void setTiltAngle(int angle);

    int getTiltSidewaysAngle() const;
    void setTiltSidewaysAngle(int angle);

    int getTwistAngle() const;
    void setTwistAngle(int angle);

private:
    int tiltAngle;
    int tiltSidewaysAngle;
    int twistAngle;
};

#endif // HEAD_H
