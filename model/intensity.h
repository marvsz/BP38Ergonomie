#ifndef INTENSITY_H
#define INTENSITY_H

class Intensity
{
public:
    Intensity(int* newton);
    ~Intensity();

    int getIntensity() const;
    void setIntensity(int* i);

private:
    int* newton;
};

#endif // INTENSITY_H
