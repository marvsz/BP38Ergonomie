#ifndef ORGAN_H
#define ORGAN_H

#include <iostream>
#include <string>
using namespace std;

class Organ
{
public:
    Organ(string organ);
    ~Organ();

    void setOrgan(string o);
    string getOrgan();

private:
    string organ;
};

#endif // ORGAN_H
