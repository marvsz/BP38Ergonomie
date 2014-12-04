#ifndef NUMBERFIELD_H
#define NUMBERFIELD_H

class NumberField
{
public:
    NumberField(int number);
    ~NumberField();

    int getNumber();
    void setNumber(int n);

private:
    int number;
};

#endif // NUMBERFIELD_H
