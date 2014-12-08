#ifndef DIRECTION_H
#define DIRECTION_H

#include <QString>

class Direction
{
public:
    Direction(QString* direction);
    ~Direction();

    void setDirection(QString* d);
    QString getDirection();

private:
    QString* direction;
};

#endif // DIRECTION_H
