#include "transportation.h"

Transportation::Transportation()
{
    id = -1;
    setName(new QString(""));
    setHasFixedRoller(false);
    setHasBrakes(false);
    setEmptyWeight(0);
    setMaxLoad(0);
}


int Transportation::getID() const{
    return id;
}

QString* Transportation::getName() const{
    return name;
}
void Transportation::setName(QString *name){
    this->name = name;
}

bool Transportation::getHasFixedRoller() const{
    return hasFixedRoller;
}
void Transportation::setHasFixedRoller(bool hasFixedRoller){
    this->hasFixedRoller = hasFixedRoller;
}

bool Transportation::getHasBrakes() const{
    return hasBrakes;
}
void Transportation::setHasBrakes(bool hasBrakes){
    this->hasBrakes = hasBrakes;
}

int Transportation::getEmptyWeight() const{
    return emptyWeight;
}
void Transportation::setEmptyWeight(int weight){
    emptyWeight = weight;
}

int Transportation::getMaxLoad() const{
    return maxLoad;
}
void Transportation::setMaxLoad(int load){
    maxLoad = load;
}
