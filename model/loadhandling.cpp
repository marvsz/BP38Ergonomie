#include "loadhandling.h"

LoadHandling::LoadHandling(QString *handlingType)
{
    id = -1;
    setLoad(0);
    setDistance(0);
    setHandlingType(handlingType);
}

LoadHandling::LoadHandling(){
    id = -1;
    setLoad(0);
    setDistance(0);
    setHandlingType(new QString(""));
}


int LoadHandling::getID() const{
    return id;
}

int LoadHandling::getLoad() const{
    return load;
}
void LoadHandling::setLoad(int load){
    this->load = load;
}

int LoadHandling::getDistance() const{
    return distance;
}
void LoadHandling::setDistance(int distance){
    this->distance = distance;
}

QString* LoadHandling::getHandlingType()const{
    return handlingType;
}
void LoadHandling::setHandlingType(QString *type){
    handlingType = type;
}

