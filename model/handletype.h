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

    void setHandleType(string h);
    string getHandleType() const;

private:
    string handleType;
};

#endif // HANDLETYPE_H
