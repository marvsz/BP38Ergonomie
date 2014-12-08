#ifndef LINE_H
#define LINE_H

#include <QString>

class Line
{
public:
    Line(QString* name, int* workstationQuantity, QString* description);

    void setName(QString* n);
    void setWorkstationQuantity(int* w);
    void setDescription(QString* d);

    QString getName();
    int getWorkstationQuantity();
    QString getDescription();

private:
    QString* name;
    int* workstationQuantity;
    QString* description;
};

#endif // LINE_H
