#ifndef ANGLE_H
#define ANGLE_H

class Angle
{
public:
    Angle(int degree);
    ~Angle();

    int getDegree() const;
    void setDegree(int degree) const;

private:
    int degree;
};

#endif // ANGLE_H
