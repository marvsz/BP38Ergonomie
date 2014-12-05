#include "line.h"

Line::Line(TextField* name, NumberField* workstationQuantity, TextField* description)
{
    this->description=description;
    this->name=name;
    this->workstationQuantity=workstationQuantity;
}
