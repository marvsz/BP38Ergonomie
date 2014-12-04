#ifndef HANDLETYPE_H
#define HANDLETYPE_H

#include <string>
#include <iostream>
using namespace std;

class HandleType
{
public:
    HandleType(string handleType);
    ~HandleType();

    string getHandleType();
    void setHandleType(string h);

private:
    string handleType;
};

#endif // HANDLETYPE_H
