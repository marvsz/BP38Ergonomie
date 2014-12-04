#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <string>
#include <iostream>
using namespace std;

class TextField
{
public:
    TextField(string description);
    ~TextField();

    string getTextField();
    void setTextField(string d);

private:
    string description;
};

#endif // TEXTFIELD_H
