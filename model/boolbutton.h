#ifndef BOOLBUTTON_H
#define BOOLBUTTON_H

class BoolButton
{
public:
    BoolButton(bool value);
    ~BoolButton();

    bool getValue();
    void setValue(bool b);

private:
    bool value;
};

#endif // BOOLBUTTON_H
