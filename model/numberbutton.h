#ifndef NUMBERBUTTON_H
#define NUMBERBUTTON_H

class NumberButton
{
public:
    NumberButton(int number);
    ~NumberButton();

    int getNumber();
    void setNumber(int n);

private:
    int number;
};

#endif // NUMBERBUTTON_H
