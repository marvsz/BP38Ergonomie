#include "line.h"

Line::Line(QString* name, int* workstationQuantity, QString* description)
{
    this->description=description;
    this->name=name;
    this->workstationQuantity=workstationQuantity;
}
