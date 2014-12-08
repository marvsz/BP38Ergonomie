#ifndef LINE_H
#define LINE_H

#include <QString>

class Line
{
public:
    Line(QString* name, int* workstationQuantity, QString* description);

private:
    QString* name;
    int* workstationQuantity;
    QString* description;
};

#endif // LINE_H
