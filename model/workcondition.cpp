#include "workcondition.h"

WorkCondition::WorkCondition(bool* torsoSupport, bool* armSupport, int* neededPrecision, int* neededVelocity, int* neededAcceleration, int* givenVibration, int* gripCondition, int* accessibility, int* terrain, int* lighting, int* clima, int* wind, int* clothing, int* mobility)
{
    this->accessibility = accessibility;
    this->armSupport = armSupport;
    this->clima = clima;
    this->clothing = clothing;
    this->givenVibration = givenVibration;
    this->gripCondition = gripCondition;
    this->lighting = lighting;
    this->mobility = mobility;
    this->neededAcceleration = neededAcceleration;
    this->neededPrecision = neededPrecision;
    this->neededVelocity = neededVelocity;
    this->terrain = terrain;
    this->torsoSupport = torsoSupport;
    this->wind = wind;
}

WorkCondition::~WorkCondition(){

}
