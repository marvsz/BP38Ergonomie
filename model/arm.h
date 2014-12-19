#ifndef ARM_H
#define ARM_H

#include <QString>

class Arm
{
public:
    Arm();

    int getOpeningAngle() const;
    void setOpeningAngle(int angle);

    int getUpperArmAngle() const;
    void setUpperArmAngle(int angle);

    int getUpperArmTwist() const;
    void setUpperArmTwist(int angle);

    int getForeArmAngle() const;
    void setForeArmAngle(int angle);

    int getForeArmTwist() const;
    void setForeArmTwist(int angle);

    QString* getWristMovement() const;
    void setWristMovement(QString* wristMovement);


private:
    int openingAngle;
    int upperArmAngle;
    int upperArmTwist;
    int foreArmAngle;
    int foreArmTwist;
    QString *wristMovement;
};

#endif // ARM_H
