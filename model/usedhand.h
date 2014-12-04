#ifndef USEDHAND_H
#define USEDHAND_H

#include <string>
#include <iostream>
using namespace std;

class UsedHand
{
public:
    UsedHand(string hand);
    ~UsedHand();

    void setHand(string h);
    string getHand() const;

private:
    string hand;
};

#endif // USEDHAND_H
