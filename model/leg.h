#ifndef LEG_H
#define LEG_H

class Leg
{
public:
    Leg();

    int getHipAngle() const;
    void setHipAngle(int angle);

    int getKneeAngle() const;
    void setKneeAngle(int angle);

    int getAnkleAngle() const;
    void setAnkleAngle(int angle);

private:
    int hipAngle;
    int kneeAngle;
    int ankleAngle;
};

#endif // LEG_H
