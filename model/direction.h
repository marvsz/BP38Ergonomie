#ifndef DIRECTION_H
#define DIRECTION_H

#include <QString>

class Direction
{
public:
    Direction(QString* direction);
    ~Direction();

private:
    QString* direction;
};

#endif // DIRECTION_H
