#ifndef LOADHANDLING_H
#define LOADHANDLING_H

#include <QString>

class LoadHandling
{
public:
    LoadHandling(QString *handlingType);
    LoadHandling();

    int getID() const;

    int getLoad() const;
    void setLoad(int load);

    int getDistance() const;
    void setDistance(int distance);

    QString* getHandlingType()const;
    void setHandlingType(QString *type);


private:
    int id;
    int load;
    int distance;
    QString *handlingType;
};

#endif // LOADHANDLING_H
