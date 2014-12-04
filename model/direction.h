#ifndef DIRECTION_H
#define DIRECTION_H

#include <iostream>
#include <string>
using namespace std;

class Direction
{
public:
    Direction(string direction);
    ~Direction();

    void setDirection(string d);
    string getDirection();

private:
    string direction;
};

#endif // DIRECTION_H
