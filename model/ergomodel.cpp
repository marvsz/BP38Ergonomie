#include "ergomodel.h"

ErgoModel::ErgoModel()
{
    this->workProcesses = new QVector<WorkProcess*>();
    this->transportations = new QVector<Transportation*>();
    this->equipment = new QVector<Equipment*>();
    this->currentWorkProcess = NULL;
}

QVector<int>* ErgoModel::getAllWorkProcesses(int spec){
    QVector<int> *wpList = new QVector<int>();
    for(int i = 0; i < workProcesses->length(); ++i){
        WorkProcess *wp = workProcesses->at(i);
        if(wp->getSpecification() == spec){
            wpList->append(wp->getID());
            wpList->append(wp->QTimeToSeconds(wp->getBegin()));
            wpList->append(wp->getDuration());
        }
    }
    return wpList;
}

void ErgoModel::createWorkProcess(int id, QTime *begin, int specification){
    workProcesses->append(new WorkProcess(id, begin, specification));
}
void ErgoModel::setWorkProcessToEdit(int id, int specification){
    foreach(WorkProcess* wp, (*workProcesses))
        if(wp->getID() == id && wp->getSpecification() == specification)
            currentWorkProcess = wp;
}
void ErgoModel::setWorkProcessEnd(QTime *end){
    currentWorkProcess->setEnd(end);
}

QString* ErgoModel::getWorkProcessDescription(){
    return currentWorkProcess->getDescription();
}
void ErgoModel::setWorkProcessDescription(QString *description){
    currentWorkProcess->setDescription(description);
}

QString* ErgoModel::getMTMCode(){
    return currentWorkProcess->getMTMCode();
}
void ErgoModel::setMTMCode(QString *mtmCode){
    currentWorkProcess->setMTMCode(mtmCode);
}

QString* ErgoModel::getGraspingType(){
    return currentWorkProcess->getGraspingType();
}
void ErgoModel::setGraspingType(QString *graspingType){
    currentWorkProcess->setGraspingType(graspingType);
}

int ErgoModel::getFrequency(){
    return currentWorkProcess->getFrequency();
}
void ErgoModel::setFrequency(int frequency){
    currentWorkProcess->setFrequency(frequency);
}

int ErgoModel::getImpulseCount(){
    return currentWorkProcess->getImpulseCount();
}
void ErgoModel::setImpulseCount(int count){
    currentWorkProcess->setImpulseCount(count);
}

int ErgoModel::getImpulseIntensity(){
    return currentWorkProcess->getImpulseIntensity();
}
void ErgoModel::setImpulseIntensity(int intensity){
    currentWorkProcess->setImpulseIntensity(intensity);
}

int ErgoModel::getWorkingHeight(){
    return currentWorkProcess->getWorkingHeight();
}
void ErgoModel::setWorkingHeight(int height){
    currentWorkProcess->setWorkingHeight(height);
}

int ErgoModel::getWorkProcessDistance(){
    return currentWorkProcess->getDistance();
}
void ErgoModel::setWorkProcessDistance(int distance){
    currentWorkProcess->setDistance(distance);
}

int ErgoModel::getHeadTilt(){
    return currentWorkProcess->getBodyPosture()->getHead()->getTiltAngle();
}
void ErgoModel::setHeadTilt(int angle){
    currentWorkProcess->getBodyPosture()->getHead()->setTiltAngle(angle);
}

int ErgoModel::getHeadSidewaysTilt(){
    return currentWorkProcess->getBodyPosture()->getHead()->getTiltSidewaysAngle();
}
void ErgoModel::setHeadSidewaysTilt(int angle){
    currentWorkProcess->getBodyPosture()->getHead()->setTiltSidewaysAngle(angle);
}

int ErgoModel::getHeadTwist(){
    return currentWorkProcess->getBodyPosture()->getHead()->getTwistAngle();
}
void ErgoModel::setHeadTwist(int angle){
    currentWorkProcess->getBodyPosture()->getHead()->setTwistAngle(angle);
}

int ErgoModel::getTorsoTilt(){
    return currentWorkProcess->getBodyPosture()->getTorso()->getTiltAngle();
}
void ErgoModel::setTorsoTilt(int angle){
    currentWorkProcess->getBodyPosture()->getTorso()->setTiltAngle(angle);
}

int ErgoModel::getTorsoSidewaysTilt(){
    return currentWorkProcess->getBodyPosture()->getTorso()->getTiltSidewaysAngle();
}
void ErgoModel::setTorsoSidewaysTilt(int angle){
    currentWorkProcess->getBodyPosture()->getTorso()->setTiltSidewaysAngle(angle);
}

int ErgoModel::getTorsoTwist(){
    return currentWorkProcess->getBodyPosture()->getTorso()->getTwistAngle();
}
void ErgoModel::setTorsoTwist(int angle){
    currentWorkProcess->getBodyPosture()->getTorso()->setTwistAngle(angle);
}

Arm* ErgoModel::getArm(bool left){
    if(left)
        return currentWorkProcess->getBodyPosture()->getLeftArm();
    else
        return currentWorkProcess->getBodyPosture()->getRightArm();
}

int ErgoModel::getArmOpening(bool getLeft){
    return getArm(getLeft)->getOpeningAngle();
}
void ErgoModel::setArmOpening(bool setLeft, int angle){
    getArm(setLeft)->setOpeningAngle(angle);
}

int ErgoModel::getUpperArmAngle(bool getLeft){
    return getArm(getLeft)->getUpperArmAngle();
}
void ErgoModel::setUpperArmAngle(bool setLeft, int angle){
    getArm(setLeft)->setUpperArmAngle(angle);
}

int ErgoModel::getUpperArmTwist(bool getLeft){
    return getArm(getLeft)->getUpperArmTwist();
}
void ErgoModel::setUpperArmTwist(bool setLeft, int angle){
    getArm(setLeft)->setUpperArmTwist(angle);
}

int ErgoModel::getForeArmAngle(bool getLeft){
    return getArm(getLeft)->getForeArmAngle();
}
void ErgoModel::setForeArmAngle(bool setLeft, int angle){
    getArm(setLeft)->setForeArmAngle(angle);
}

int ErgoModel::getForeArmTwist(bool getLeft){
    return getArm(getLeft)->getForeArmTwist();
}
void ErgoModel::setForeArmTwist(bool setLeft, int angle){
    getArm(setLeft)->setForeArmTwist(angle);
}

QString* ErgoModel::getArmWristMovement(bool getLeft){
    return getArm(getLeft)->getWristMovement();
}
void ErgoModel::setArmWristMovement(bool setLeft, QString *angle){
    getArm(setLeft)->setWristMovement(angle);
}

Leg* ErgoModel::getLeg(bool left){
    if(left)
        return currentWorkProcess->getBodyPosture()->getLeftLeg();
    else
        return currentWorkProcess->getBodyPosture()->getRightLeg();
}


int ErgoModel::getHipAngle(bool getLeft){
    return getLeg(getLeft)->getHipAngle();
}
void ErgoModel::setHipAngle(bool setLeft, int angle){
    getLeg(setLeft)->setHipAngle(angle);
}

int ErgoModel::getKneeAngle(bool getLeft){
    return getLeg(getLeft)->getKneeAngle();
}
void ErgoModel::setKneeAngle(bool setLeft, int angle){
    getLeg(setLeft)->setKneeAngle(angle);
}

int ErgoModel::getAnkleAngle(bool getLeft){
    return getLeg(getLeft)->getAnkleAngle();
}
void ErgoModel::setAnkleAngle(bool setLeft, int angle){
    return getLeg(setLeft)->setAnkleAngle(angle);
}

QString* ErgoModel::getLegPosture(){
    return currentWorkProcess->getBodyPosture()->getLegPosture();
}
void ErgoModel::setLegPosture(QString* posture){
    currentWorkProcess->getBodyPosture()->setLegPosture(posture);
}

void ErgoModel::setTransportation(int id){
    currentWorkProcess->setTransportation(getTransportation(id));
}
int ErgoModel::getTransportation(){
    return currentWorkProcess->getTransportation()->getID();
}

Transportation* ErgoModel::getTransportation(int id){
    foreach(Transportation* trans, (*transportations))
        if(trans->getID() == id)
            return trans;
    return NULL;
}

QVector<int>* ErgoModel::getTransportationIDs(){
    QVector<int>* transIDs = new QVector<int>();
    foreach(Transportation* trans, (*transportations))
        transIDs->append(trans->getID());
    return transIDs;
}
void ErgoModel::createTransportation(QString *name, bool hasFixedRoller, bool hasBrakes, int emptyWeight, int maxLoad){
    transportations->append(new Transportation(name, hasFixedRoller, hasBrakes, emptyWeight, maxLoad));
}
void ErgoModel::removeTransportation(int id){
    int i = -1;
    foreach(Transportation *trans, (*transportations)){
        ++i;
        if(trans->getID() == id)
            break;
    }
    if(i != -1)
        transportations->remove(i);
}

QString* ErgoModel::getTransportationName(int id){
    return getTransportation(id)->getName();
}
void ErgoModel::setTransportationName(int id, QString* name){
    getTransportation(id)->setName(name);
}

bool ErgoModel::getTransportationHasFixedRoller(int id){
    return getTransportation(id)->getHasFixedRoller();
}
void ErgoModel::setTransportationHasFixedRoller(int id, bool hasFixedRoller){
    getTransportation(id)->setHasFixedRoller(hasFixedRoller);
}

bool ErgoModel::getTransportationHasBrakes(int id){
    return getTransportation(id)->getHasBrakes();
}
void ErgoModel::setTransportationHasBrakes(int id, bool hasBrakes){
    getTransportation(id)->setHasBrakes(hasBrakes);
}

int ErgoModel::getTransportationEmptyWeight(int id){
    return getTransportation(id)->getEmptyWeight();
}
void ErgoModel::setTransportationEmptyWeight(int id, int weight){
    getTransportation(id)->setEmptyWeight(weight);
}

int ErgoModel::getTransportationMaxLoad(int id){
    return getTransportation(id)->getMaxLoad();
}
void ErgoModel::setTransportationMaxLoad(int id, int load){
    getTransportation(id)->setMaxLoad(load);
}

void ErgoModel::setEquipment(int id){
    currentWorkProcess->setEquipment(getEquipment(id));
}
int ErgoModel::getEquipment(){
    return currentWorkProcess->getEquipment()->getID();
}

Equipment* ErgoModel::getEquipment(int id){
    foreach(Equipment *equip, (*equipment))
        if(equip->getID() == id)
            return equip;
    return NULL;
}

QVector<int> *ErgoModel::getEquipmentIDs(){
    QVector<int> *equipIDs = new QVector<int>();
    foreach(Equipment *equip, (*equipment))
        equipIDs->append(equip->getID());
    return equipIDs;
}
void ErgoModel::createEquipment(QString *name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity){
    equipment->append(new Equipment(name, recoilCount, recoilIntensity, vibrationCount, vibrationIntensity));
}
void ErgoModel::removeEquipment(int id){
    int i = -1;
    foreach(Equipment *equip, (*equipment)){
        ++i;
        if(equip->getID() == id)
            break;
    }
    if(i != -1)
        equipment->remove(i);
}

QString* ErgoModel::getEquipmentName(int id){
    return getEquipment(id)->getName();
}
void ErgoModel::setEquipmentName(int id, QString* name){
    getEquipment(id)->setName(name);
}

int ErgoModel::getEquipmentRecoilCount(int id){
    return getEquipment(id)->getRecoilCount();
}
void ErgoModel::setEquipmentRecoilCount(int id, int count){
    getEquipment(id)->setRecoilCount(count);
}

int ErgoModel::getEquipmentRecoilIntensity(int id){
    return getEquipment(id)->getRecoilIntensity();
}
void ErgoModel::setEquipmentRecoilIntensity(int id, int intensity){
    getEquipment(id)->setRecoilIntensity(intensity);
}

int ErgoModel::getEquipmentVibrationCount(int id){
    return getEquipment(id)->getVibrationCount();
}
void ErgoModel::setEquipmentVibrationCount(int id, int count){
    getEquipment(id)->setVibrationCount(count);
}

int ErgoModel::getEquipmentVibrationIntensity(int id){
    return getEquipment(id)->getVibrationIntensity();
}
void ErgoModel::setEquipmentVibrationIntensity(int id, int intensity){
    getEquipment(id)->setVibrationIntensity(intensity);
}

bool ErgoModel::getTorsoSupport(){
    return currentWorkProcess->getWorkCondition()->getTorsoSupport();
}
void ErgoModel::setTorsoSupport(bool torsoSupport){
    currentWorkProcess->getWorkCondition()->setTorsoSupport(torsoSupport);
}

bool ErgoModel::getArmSupport(){
    return currentWorkProcess->getWorkCondition()->getArmSupport();
}
void ErgoModel::setArmSupport(bool armSupport){
    currentWorkProcess->getWorkCondition()->setArmSupport(armSupport);
}

int ErgoModel::getPrecision(){
    return currentWorkProcess->getWorkCondition()->getPrecision();
}
void ErgoModel::setPrecision(int precision){
    currentWorkProcess->getWorkCondition()->setPrecision(precision);
}

int ErgoModel::getVelocity(){
    return currentWorkProcess->getWorkCondition()->getVelocity();
}
void ErgoModel::setVelocity(int velocity){
    currentWorkProcess->getWorkCondition()->setVelocity(velocity);
}

int ErgoModel::getAcceleration(){
    return currentWorkProcess->getWorkCondition()->getAcceleration();
}
void ErgoModel::setAcceleration(int acceleration){
    currentWorkProcess->getWorkCondition()->setAcceleration(acceleration);
}

int ErgoModel::getVibration(){
    return currentWorkProcess->getWorkCondition()->getVibration();
}
void ErgoModel::setVibration(int vibration){
    currentWorkProcess->getWorkCondition()->setVibration(vibration);
}

int ErgoModel::getGrabCondition(){
    return currentWorkProcess->getWorkCondition()->getGrabCondition();
}
void ErgoModel::setGrabCondition(int grabCondition){
    currentWorkProcess->getWorkCondition()->setGrabCondition(grabCondition);
}

int ErgoModel::getAccessibility(){
    return currentWorkProcess->getWorkCondition()->getAccessibility();
}
void ErgoModel::setAccessibility(int accessibility){
    currentWorkProcess->getWorkCondition()->setAccessibility(accessibility);
}

int ErgoModel::getGround(){
    return currentWorkProcess->getWorkCondition()->getGround();
}
void ErgoModel::setGround(int ground){
    currentWorkProcess->getWorkCondition()->setGround(ground);
}

int ErgoModel::getLighting(){
    return currentWorkProcess->getWorkCondition()->getLighting();
}
void ErgoModel::setLighting(int lighting){
    currentWorkProcess->getWorkCondition()->setLighting(lighting);
}

int ErgoModel::getClimate(){
    return currentWorkProcess->getWorkCondition()->getClimate();
}
void ErgoModel::setClimate(int climate){
    currentWorkProcess->getWorkCondition()->setClimate(climate);
}

int ErgoModel::getWind(){
    return currentWorkProcess->getWorkCondition()->getWind();
}
void ErgoModel::setWind(int wind){
    currentWorkProcess->getWorkCondition()->setWind(wind);
}

int ErgoModel::getClothing(){
    return currentWorkProcess->getWorkCondition()->getClothing();
}
void ErgoModel::setClothing(int clothing){
    currentWorkProcess->getWorkCondition()->setClothing(clothing);
}

int ErgoModel::getRoomToMove(){
    return currentWorkProcess->getWorkCondition()->getRoomToMove();
}
void ErgoModel::setRoomToMove(int roomToMove){
    currentWorkProcess->getWorkCondition()->setRoomToMove(roomToMove);
}

QString* ErgoModel::getLoadHandlingType(){
    return currentWorkProcess->getLoadHandling()->getHandlingType();
}
void ErgoModel::setLoadHandlingType(QString *handlingtype){
    currentWorkProcess->getLoadHandling()->setHandlingType(handlingtype);
}

int ErgoModel::getLoadHandlingLoad(){
    return currentWorkProcess->getLoadHandling()->getLoad();
}
void ErgoModel::setLoadHandlingLoad(int load){
    currentWorkProcess->getLoadHandling()->setLoad(load);
}

int ErgoModel::getLoadHandlingDistance(){
    return currentWorkProcess->getLoadHandling()->getDistance();
}
void ErgoModel::setLoadHandlingDistance(int distance){
    currentWorkProcess->getLoadHandling()->setDistance(distance);
}

QString* ErgoModel::getAppliedForceOrgan(){
    return currentWorkProcess->getAppliedForce()->getOrgan();
}
void ErgoModel::setAppliedForceOrgan(QString *organ){
    currentWorkProcess->getAppliedForce()->setOrgan(organ);
}

QString* ErgoModel::getAppliedForceDirection(){
    return currentWorkProcess->getAppliedForce()->getDirection();
}
void ErgoModel::setAppliedForceDirection(QString *direction){
    currentWorkProcess->getAppliedForce()->setDirection(direction);
}

int ErgoModel::getAppliedForceIntensity(){
    return currentWorkProcess->getAppliedForce()->getIntensity();
}
void ErgoModel::setAppliedForceIntensity(int intensity){
    currentWorkProcess->getAppliedForce()->setIntensity(intensity);
}
