#ifndef ARM_H
#define ARM_H


class Arm
{
public:
    Arm(int* upperArmPosition, int* lowerArmPosition, int* upperArmRotation, int* lowerArmRotation, int* upperArmOpening);
    ~Arm();

    void setUpperArmPosition(int* uap);
    void setLowerArmPosition(int* lap);
    void setUpperArmRotation(int* uar);
    void setLowerArmRotation(int* lar);
    void setUpperArmOpening(int* uao);

    int getUpperArmPosition();
    int getLowerArmPosition();
    int getUpperArmRotation();
    int getLowerArmRotation();
    int getUpperArmOpening();

private:
    int* upperArmPosition;
    int* lowerArmPosition;
    int* upperArmRotation;
    int* lowerArmRotation;
    int* upperArmOpening;
};

#endif // ARM_H
