#ifndef INTENSITY_H
#define INTENSITY_H

class Intensity
{
public:
    Intensity(int* newton);
    ~Intensity();

    int* getIntensity();
    void setIntensity(int* i);

private:
    int* newton;
};

#endif // INTENSITY_H
