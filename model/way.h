#ifndef WAY_H
#define WAY_H

class Way
{
public:
    Way(int* meter);
    ~Way();

    int* getWay();
    void setWay(int* m);

private:
    int* meter;
};

#endif // WAY_H
