#ifndef TORSO_H
#define TORSO_H

class Torso
{
public:
    Torso();

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

#endif // TORSO_H
