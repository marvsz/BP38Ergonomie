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

void WorkCondition::setTorsoSupport(bool* ts){
    this->torsoSupport=ts;
}

void WorkCondition::setArmSupport(bool* as){
    this->armSupport=as;
}

void WorkCondition::setNeededPrecision(int* np){
    this->neededPrecision=np;
}

void WorkCondition::setNeededVelocity(int* nv){
    this->neededVelocity=nv;
}

void WorkCondition::setNeededAccelaration(int* na){
    this->neededAcceleration=na;
}

void WorkCondition::setGivenVibration(int* gv){
    this->givenVibration=gv;
}

void WorkCondition::setGripCondition(int* gc){
    this->gripCondition=gc;
}

void WorkCondition::setAccessibility(int* ac){
    this->accessibility=ac;
}

void WorkCondition::setTerrain(int* te){
    this->terrain=te;
}

void WorkCondition::setLighting(int* li){
    this->lighting=li;
}

void WorkCondition::setClima(int* cl){
    this->clima=cl;
}

void WorkCondition::setWind(int* wi){
    this->wind=wi;
}

void WorkCondition::setClothing(int* clo){
    this->clothing=clo;
}

void WorkCondition::setMobility(int* mo){
    this->mobility=mo;
}

bool* WorkCondition::isTorsoSupported(){
    return this->torsoSupport;
}

bool* WorkCondition::isArmSupported(){
    return this->armSupport;
}

int* WorkCondition::getNeededPrecision(){
    return this->neededPrecision;
}

int* WorkCondition::getNeededVelocity(){
    return this->neededVelocity;
}

int* WorkCondition::getNeededAcceleration(){
    return this->neededAcceleration;
}

int* WorkCondition::getGivenVibration(){
    return this->givenVibration;
}

int* WorkCondition::getGripCondition(){
    return this->gripCondition;
}

int* WorkCondition::getAccessibility(){
    return this->accessibility;
}

int* WorkCondition::getTerrain(){
    return this->terrain;
}

int* WorkCondition::getLighting(){
    return this->lighting;
}

int* WorkCondition::getClima(){
    return this->clima;
}

int* WorkCondition::getWind(){
    return this->wind;
}

int* WorkCondition::getClothing(){
    return this->clothing;
}

int* WorkCondition::getMobility(){
    return this->mobility;
}
