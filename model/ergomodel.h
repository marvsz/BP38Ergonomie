#ifndef ERGOMODEL_H
#define ERGOMODEL_H

#include "workprocess.h"
#include <QVector>
#include <QTime>
#include <QString>

class ErgoModel
{
public:
    ErgoModel();

    QVector<int>* getAllWorkProcesses(int spec);
    void createWorkProcess(int id, QTime *begin, int specification);
    void setWorkProcessToEdit(int id, int specification);
    void setWorkProcessEnd(QTime *end);

    QString* getWorkProcessDescription();
    void setWorkProcessDescription(QString *description);

    QString* getMTMCode();
    void setMTMCode(QString *mtmCode);

    QString* getGraspingType();
    void setGraspingType(QString *graspingType);

    int getFrequency();
    void setFrequency(int frequency);

    int getImpulseCount();
    void setImpulseCount(int count);

    int getImpulseIntensity();
    void setImpulseIntensity(int intensity);

    int getWorkingHeight();
    void setWorkingHeight(int height);

    int getWorkProcessDistance();
    void setWorkProcessDistance(int distance);

    int getHeadTilt();
    void setHeadTilt(int angle);

    int getHeadSidewaysTilt();
    void setHeadSidewaysTilt(int angle);

    int getHeadTwist();
    void setHeadTwist(int angle);

    int getTorsoTilt();
    void setTorsoTilt(int angle);

    int getTorsoSidewaysTilt();
    void setTorsoSidewaysTilt(int angle);

    int getTorsoTwist();
    void setTorsoTwist(int angle);

    int getArmOpening(bool getLeft);
    void setArmOpening(bool setLeft, int angle);

    int getUpperArmAngle(bool getLeft);
    void setUpperArmAngle(bool setLeft, int angle);

    int getUpperArmTwist(bool getLeft);
    void setUpperArmTwist(bool setLeft, int angle);

    int getForeArmAngle(bool getLeft);
    void setForeArmAngle(bool setLeft, int angle);

    int getForeArmTwist(bool getLeft);
    void setForeArmTwist(bool setLeft, int angle);

    QString* getArmWristMovement(bool getLeft);
    void setArmWristMovement(bool setLeft, QString *angle);

    int getHipAngle(bool getLeft);
    void setHipAngle(bool setLeft, int angle);

    int getKneeAngle(bool getLeft);
    void setKneeAngle(bool setLeft, int angle);

    int getAnkleAngle(bool getLeft);
    void setAnkleAngle(bool setLeft, int angle);

    QString* getLegPosture();
    void setLegPosture(QString* posture);

    void setTransportation(int id);
    int getTransportation();

    QVector<int> getTransportationIDs();
    void createTransportation(int id, QString *name, bool hasFixedRoller, bool hasBrakes, int emptyWeight, int maxLoad);
    void removeTransportation(int id);

    QString* getTransportationName(int id);
    void setTransportationName(int id, QString* name);

    bool getTransportationHasFixedRoller(int id);
    void setTransportationHasFixedRoller(int id, bool hasFixedRoller);

    bool getTransportationHasBrakes(int id);
    void setTransportationHasBrakes(int id, bool hasBrakes);

    int getTransportationEmptyWeight(int id);
    void setTransportationEmptyWeight(int id, int weight);

    int getTransportationMaxLoad(int id);
    void setTransportationMaxLoad(int id, int load);

    void setEquipment(int id);
    int getEquipment(int id);

    QVector<int> getEquipmentIDs();
    void createEquipment(int id, QString *name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity);
    void removeEquipment(int id);

    QString* getEquipmentName(int id);
    void setEquipment(int id, QString* name);

    int getEquipmentRecoilCount(int id);
    void setEquipmentRecoilCount(int id, int count);

    int getEquipmentRecoilIntensity(int id);
    void setEquipmentRecoilIntensity(int id, int intensity);

    int getEquipmentVibrationCount(int id);
    void setEquipmentVibrationCount(int id, int count);

    int getEquipmentVibrationIntensity(int id);
    void setEquipmentVibrationIntensity(int id, int intensity);

    bool getTorsoSupport();
    void setTorsoSupport(bool torsoSupport);

    bool getArmSupport();
    void setArmSupport(bool armSupport);

    int getPrecision();
    void setPrecision(int precision);

    int getVelocity();
    void setVelocity(int velocity);

    int getAcceleration();
    void setAcceleration(int acceleration);

    int getVibration();
    void setVibration(int vibration);

    int getGrabCondition();
    void setGrabCondition(int grabCondition);

    int getAccessibility();
    void setAccessibility(int accessibility);

    int getGround();
    void setGround(int ground);

    int getLighting();
    void setLighting(int lighting);

    int getClimate();
    void setClimate(int climate);

    int getWind();
    void setWind(int wind);

    int getClothing();
    void setClothing(int clothing);

    int getRoomToMove();
    void setRoomToMove(int roomToMove);

    void setLoadHandlingType(QString *handlingtype);
    void setLoadHandlingLoad(int load);
    void setLoadHandlingDistance(int distance);

    void setAppliedForceOrgan(QString *organ);
    void setAppliedForceDirection(QString *direction);
    void setAppliedForceIntensity(int intensity);

private:
    QVector<WorkProcess*> *workProcesses;
    QVector<Equipment*> *equipment;
    QVector<Transportation*> *transportations;
    WorkProcess *currentWorkProcess;

    Arm* getArm(bool left);
    Leg* getLeg(bool left);
};

#endif // ERGOMODEL_H
