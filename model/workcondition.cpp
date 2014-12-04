#include "workcondition.h"

WorkCondition::WorkCondition(BoolButton* torsoSupport, BoolButton* armSupport, NumberButton* neededPrecision, NumberButton* neededVelocity, NumberButton* neededAcceleration, NumberButton* givenVibration, NumberButton* gripCondition, NumberButton* accessibility, NumberButton* terrain, NumberButton* lighting, NumberButton* clima, NumberButton* wind, NumberButton* clothing, NumberButton* mobility)
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
