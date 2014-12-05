#ifndef LINE_H
#define LINE_H

#include "textfield.h"
#include "numberfield.h"

class Line
{
public:
    Line(TextField* name, NumberField* workstationQuantity, TextField* description);

private:
    TextField* name;
    NumberField* workstationQuantity;
    TextField* description;
};

#endif // LINE_H
