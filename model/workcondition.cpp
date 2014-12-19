#include "workcondition.h"

WorkCondition::WorkCondition()
{
    id = -1;
    torsoSupport = false;
    armSupport = false;
    precision = 0;
    velocity = 0;
    acceleration = 0;
    grabCondition = 0;
    vibration = 0;
    accessibility = 0;
    ground = 0;
    lighting = 0;
    climate = 0;
    wind = 0;
    clothing = 0;
    roomToMove = 0;
}

int WorkCondition::getID() const{
    return id;
}

bool WorkCondition::getTorsoSupport() const{
    return torsoSupport;
}
void WorkCondition::setTorsoSupport(bool support){
    torsoSupport = support;
}

bool WorkCondition::getArmSupport() const{
    return armSupport;
}
void WorkCondition::setArmSupport(bool support){
    armSupport = support;
}

int WorkCondition::getPrecision() const{
    return precision;
}
void WorkCondition::setPrecision(int precision){
    this->precision = precision;
}

int WorkCondition::getVelocity() const{
    return velocity;
}
void WorkCondition::setVelocity(int velocity){
    this->velocity = velocity;
}

int WorkCondition::getAcceleration() const{
    return acceleration;
}
void WorkCondition::setAcceleration(int acceleration){
    this->acceleration = acceleration;
}

int WorkCondition::getVibration() const{
    return vibration;
}
void WorkCondition::setVibration(int vibration){
    this->vibration = vibration;
}

int WorkCondition::getGrabCondition() const{
    return grabCondition;
}
void WorkCondition::setGrabCondition(int grabCondition){
    this->grabCondition = grabCondition;
}

int WorkCondition::getAccessibility() const{
    return accessibility;
}
void WorkCondition::setAccessibility(int accessibility){
    this->accessibility = accessibility;
}

int WorkCondition::getGround() const{
    return ground;
}
void WorkCondition::setGround(int ground){
    this->ground = ground;
}

int WorkCondition::getLighting() const{
    return lighting;
}
void WorkCondition::setLighting(int lighting){
    this->lighting = lighting;
}

int WorkCondition::getClimate() const{
    return climate;
}
void WorkCondition::setClimate(int climate){
    this->climate = climate;
}

int WorkCondition::getWind() const{
    return wind;
}
void WorkCondition::setWind(int wind){
    this->wind = wind;
}

int WorkCondition::getClothing() const{
    return clothing;
}
void WorkCondition::setClothing(int clothing){
    this->clothing = clothing;
}

int WorkCondition::getRoomToMove() const{
    return roomToMove;
}
void WorkCondition::setRoomToMove(int roomToMove){
    this->roomToMove = roomToMove;
}
