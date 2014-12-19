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

int ErgoModel::getUpperArmTwist(bool getLeft){}
void ErgoModel::setUpperArmTwist(bool setLeft, int angle){}

int ErgoModel::getForeArmAngle(bool getLeft){}
void ErgoModel::setForeArmAngle(bool setLeft, int angle){}

int ErgoModel::getForeArmTwist(bool getLeft){}
void ErgoModel::setForeArmTwist(bool setLeft, int angle){}

QString* ErgoModel::getArmWristMovement(bool getLeft){}
void ErgoModel::setArmWristMovement(bool setLeft, QString *angle){}

int ErgoModel::getHipAngle(bool getLeft){}
void ErgoModel::setHipAngle(bool setLeft, int angle){}

int ErgoModel::getKneeAngle(bool getLeft){}
void ErgoModel::setKneeAngle(bool setLeft, int angle){}

int ErgoModel::getAnkleAngle(bool getLeft){}
void ErgoModel::setAnkleAngle(bool setLeft, int angle){}

QString* ErgoModel::getLegPosture(){}
void ErgoModel::setLegPosture(QString* posture){}

void ErgoModel::setTransportation(int id){}
int ErgoModel::getTransportation(){}

QVector<int> ErgoModel::getTransportationIDs(){}
void ErgoModel::createTransportation(int id, QString *name, bool hasFixedRoller, bool hasBrakes, int emptyWeight, int maxLoad){}
void ErgoModel::removeTransportation(int id){}

QString* ErgoModel::getTransportationName(int id){}
void ErgoModel::setTransportationName(int id, QString* name){}

bool ErgoModel::getTransportationHasFixedRoller(int id){}
void ErgoModel::setTransportationHasFixedRoller(int id, bool hasFixedRoller){}

bool ErgoModel::getTransportationHasBrakes(int id){}
void ErgoModel::setTransportationHasBrakes(int id, bool hasBrakes){}

int ErgoModel::getTransportationEmptyWeight(int id){}
void ErgoModel::setTransportationEmptyWeight(int id, int weight){}

int ErgoModel::getTransportationMaxLoad(int id){}
void ErgoModel::setTransportationMaxLoad(int id, int load){}

void ErgoModel::setEquipment(int id){}
int ErgoModel::getEquipment(int id){}

QVector<int> ErgoModel::getEquipmentIDs(){}
void ErgoModel::createEquipment(int id, QString *name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity){}
void ErgoModel::removeEquipment(int id){}

QString* ErgoModel::getEquipmentName(int id){}
void ErgoModel::setEquipment(int id, QString* name){}

int ErgoModel::getEquipmentRecoilCount(int id){}
void ErgoModel::setEquipmentRecoilCount(int id, int count){}

int ErgoModel::getEquipmentRecoilIntensity(int id){}
void ErgoModel::setEquipmentRecoilIntensity(int id, int intensity){}

int ErgoModel::getEquipmentVibrationCount(int id){}
void ErgoModel::setEquipmentVibrationCount(int id, int count){}

int ErgoModel::getEquipmentVibrationIntensity(int id){}
void ErgoModel::setEquipmentVibrationIntensity(int id, int intensity){}

bool ErgoModel::getTorsoSupport(){}
void ErgoModel::setTorsoSupport(bool torsoSupport){}

bool ErgoModel::getArmSupport(){}
void ErgoModel::setArmSupport(bool armSupport){}

int ErgoModel::getPrecision(){}
void ErgoModel::setPrecision(int precision){}

int ErgoModel::getVelocity(){}
void ErgoModel::setVelocity(int velocity){}

int ErgoModel::getAcceleration(){}
void ErgoModel::setAcceleration(int acceleration){}

int ErgoModel::getVibration(){}
void ErgoModel::setVibration(int vibration){}

int ErgoModel::getGrabCondition(){}
void ErgoModel::setGrabCondition(int grabCondition){}

int ErgoModel::getAccessibility(){}
void ErgoModel::setAccessibility(int accessibility){}

int ErgoModel::getGround(){}
void ErgoModel::setGround(int ground){}

int ErgoModel::getLighting(){}
void ErgoModel::setLighting(int lighting){}

int ErgoModel::getClimate(){}
void ErgoModel::setClimate(int climate){}

int ErgoModel::getWind(){}
void ErgoModel::setWind(int wind){}

int ErgoModel::getClothing(){}
void ErgoModel::setClothing(int clothing){}

int ErgoModel::getRoomToMove(){}
void ErgoModel::setRoomToMove(int roomToMove){}

void ErgoModel::setLoadHandlingType(QString *handlingtype){}
void ErgoModel::setLoadHandlingLoad(int load){}
void ErgoModel::setLoadHandlingDistance(int distance){}

void ErgoModel::setAppliedForceOrgan(QString *organ){}
void ErgoModel::setAppliedForceDirection(QString *direction){}
void ErgoModel::setAppliedForceIntensity(int intensity){}
