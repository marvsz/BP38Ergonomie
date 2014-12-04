#ifndef WEIGHT_H
#define WEIGHT_H

class Weight
{
public:
    Weight(int weight);
    ~Weight();

    int getWeight() const;
    void setWeight(int w);

private:
    int weight;
};

#endif // WEIGHT_H
