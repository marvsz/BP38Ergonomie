#ifndef TORSO_H
#define TORSO_H

class Torso
{
public:
    Torso(int* flextion, int* tilt, int* rotation);
    ~Torso();

    void setFextion(int* f);
    void setTilt(int* t);
    void setRotation(int* r);

    int getFlextion();
    int getTilt();
    int getRotation();

private:
    int* flextion;
    int* tilt;
    int* rotation;
};

#endif // TORSO_H
