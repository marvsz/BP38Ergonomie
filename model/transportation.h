#ifndef TRANSPORTATION_H
#define TRANSPORTATION_H

#include <QString>

class Transportation
{
public:
    Transportation();

    int getID() const;

    QString* getName() const;
    void setName(QString *name);

    bool getHasFixedRoller() const;
    void setHasFixedRoller(bool hasFixedRoller);

    bool getHasBrakes() const;
    void setHasBrakes(bool hasBrakes);

    int getEmptyWeight() const;
    void setEmptyWeight(int weight);

    int getMaxLoad() const;
    void setMaxLoad(int load);

private:
    int id;
    QString *name;
    bool hasFixedRoller;
    bool hasBrakes;
    int emptyWeight;
    int maxLoad;
};

#endif // TRANSPORTATION_H
