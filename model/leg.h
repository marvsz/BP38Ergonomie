#ifndef LEG_H
#define LEG_H

class Leg
{
public:
    Leg(int* hip, int* knee, int* ankle);
    ~Leg();

    void setHip(int* h);
    void setKnee(int* k);
    void setAnkle(int* a);

    int getHip();
    int getKnee();
    int getAnkle();
private:
    int* hip;
    int* knee;
    int* ankle;
};

#endif // LEG_H
