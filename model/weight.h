#ifndef WEIGHT_H
#define WEIGHT_H

class Weight
{
public:
    Weight(int* weight);
    ~Weight();

    void setWeight(int* w);
    int* getWeight();

private:
    int* weight;
};

#endif // WEIGHT_H
