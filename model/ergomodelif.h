#ifndef ERGOMODELIF_H
#define ERGOMODELIF_H

#include <QTime>
#include <QString>
#include <QVector>

class ErgoModelIf
{
public:

    virtual QVector<int>* getAllWorkProcesses(int spec);
    virtual void createWorkProcess(int id, QTime *begin, int specification);
    virtual void setWorkProcessToEdit(int id, int specification);
    virtual void setWorkProcessEnd(QTime *end);

    virtual QString* getWorkProcessDescription();
    virtual void setWorkProcessDescription(QString *description);

    virtual QString* getMTMCode();
    virtual void setMTMCode(QString *mtmCode);

    virtual QString* getGraspingType();
    virtual void setGraspingType(QString *graspingType);

    virtual int getFrequency();
    virtual void setFrequency(int frequency);

    virtual int getImpulseCount();
    virtual void setImpulseCount(int count);

    virtual int getImpulseIntensity();
    virtual void setImpulseIntensity(int intensity);

    virtual int getWorkingHeight();
    virtual void setWorkingHeight(int height);

    virtual int getWorkProcessDistance();
    virtual void setWorkProcessDistance(int distance);

    virtual int getHeadTilt();
    virtual void setHeadTilt(int angle);

    virtual int getHeadSidewaysTilt();
    virtual void setHeadSidewaysTilt(int angle);

    virtual int getHeadTwist();
    virtual void setHeadTwist(int angle);

    virtual int getTorsoTilt();
    virtual void setTorsoTilt(int angle);

    virtual int getTorsoSidewaysTilt();
    virtual void setTorsoSidewaysTilt(int angle);

    virtual int getTorsoTwist();
    virtual void setTorsoTwist(int angle);

    virtual int getArmOpening(bool getLeft);
    virtual void setArmOpening(bool setLeft, int angle);

    virtual int getUpperArmAngle(bool getLeft);
    virtual void setUpperArmAngle(bool setLeft, int angle);

    virtual int getUpperArmTwist(bool getLeft);
    virtual void setUpperArmTwist(bool setLeft, int angle);

    virtual int getForeArmAngle(bool getLeft);
    virtual void setForeArmAngle(bool setLeft, int angle);

    virtual int getForeArmTwist(bool getLeft);
    virtual void setForeArmTwist(bool setLeft, int angle);

    virtual QString* getArmWristMovement(bool getLeft);
    virtual void setArmWristMovement(bool setLeft, QString *angle);

    virtual int getHipAngle(bool getLeft);
    virtual void setHipAngle(bool setLeft, int angle);

    virtual int getKneeAngle(bool getLeft);
    virtual void setKneeAngle(bool setLeft, int angle);

    virtual int getAnkleAngle(bool getLeft);
    virtual void setAnkleAngle(bool setLeft, int angle);

    virtual QString* getLegPosture();
    virtual void setLegPosture(QString* posture);

    virtual void setTransportation(int id);
    virtual int getTransportation();

    virtual QVector<int> getTransportationIDs();
    virtual void createTransportation(int id, QString *name, bool hasFixedRoller, bool hasBrakes, int emptyWeight, int maxLoad);
    virtual void removeTransportation(int id);

    virtual QString* getTransportationName(int id);
    virtual void setTransportationName(int id, QString* name);

    virtual bool getTransportationHasFixedRoller(int id);
    virtual void setTransportationHasFixedRoller(int id, bool hasFixedRoller);

    virtual bool getTransportationHasBrakes(int id);
    virtual void setTransportationHasBrakes(int id, bool hasBrakes);

    virtual int getTransportationEmptyWeight(int id);
    virtual void setTransportationEmptyWeight(int id, int weight);

    virtual int getTransportationMaxLoad(int id);
    virtual void setTransportationMaxLoad(int id, int load);

    virtual void setEquipment(int id);
    virtual int getEquipment(int id);

    virtual QVector<int> getEquipmentIDs();
    virtual void createEquipment(int id, QString *name, int recoilCount, int recoilIntensity, int vibrationCount, int vibrationIntensity);
    virtual void removeEquipment(int id);

    virtual QString* getEquipmentName(int id);
    virtual void setEquipmentName(int id, QString* name);

    virtual int getEquipmentRecoilCount(int id);
    virtual void setEquipmentRecoilCount(int id, int count);

    virtual int getEquipmentRecoilIntensity(int id);
    virtual void setEquipmentRecoilIntensity(int id, int intensity);

    virtual int getEquipmentVibrationCount(int id);
    virtual void setEquipmentVibrationCount(int id, int count);

    virtual int getEquipmentVibrationIntensity(int id);
    virtual void setEquipmentVibrationIntensity(int id, int intensity);

    virtual bool getTorsoSupport();
    virtual void setTorsoSupport(bool torsoSupport);

    virtual bool getArmSupport();
    virtual void setArmSupport(bool armSupport);

    virtual int getPrecision();
    virtual void setPrecision(int precision);

    virtual int getVelocity();
    virtual void setVelocity(int velocity);

    virtual int getAcceleration();
    virtual void setAcceleration(int acceleration);

    virtual int getVibration();
    virtual void setVibration(int vibration);

    virtual int getGrabCondition();
    virtual void setGrabCondition(int grabCondition);

    virtual int getAccessibility();
    virtual void setAccessibility(int accessibility);

    virtual int getGround();
    virtual void setGround(int ground);

    virtual int getLighting();
    virtual void setLighting(int lighting);

    virtual int getClimate();
    virtual void setClimate(int climate);

    virtual int getWind();
    virtual void setWind(int wind);

    virtual int getClothing();
    virtual void setClothing(int clothing);

    virtual int getRoomToMove();
    virtual void setRoomToMove(int roomToMove);

    virtual QString* getLoadHandlingType();
    virtual void setLoadHandlingType(QString *handlingtype);

    virtual int getLoadHandlingLoad();
    virtual void setLoadHandlingLoad(int load);

    virtual int getLoadHandlingDistance();
    virtual void setLoadHandlingDistance(int distance);

    virtual QString* getAppliedForceOrgan();
    virtual void setAppliedForceOrgan(QString *organ);

    virtual QString* getAppliedForceDirection();
    virtual void setAppliedForceDirection(QString *direction);

    virtual int getAppliedForceIntensity();
    virtual void setAppliedForceIntensity(int intensity);

};

#endif // ERGOMODELIF_H
