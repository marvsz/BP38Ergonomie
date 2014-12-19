#ifndef WORKPROCESS_H
#define WORKPROCESS_H

#include <QString>
#include <QTime>
#include "bodyposture.h"
#include "equipment.h"
#include "transportation.h"
#include "workcondition.h"
#include "appliedforce.h"
#include "loadhandling.h"

class WorkProcess
{
public:
    WorkProcess(int id, QTime* begin, int specification);

    int getDuration();

    int QTimeToSeconds(QTime* time);

    int getID() const;

    QString* getDescription()const;
    void setDescription(QString* description);

    int getSpecification() const;

    QTime* getBegin() const;
    void setBegin(QTime *begin);

    QTime* getEnd() const;
    void setEnd(QTime *end);

    QString* getMTMCode() const;
    void setMTMCode(QString *code);

    QString* getGraspingType() const;
    void setGraspingType(QString* type);

    int getFrequency() const;
    void setFrequency(int frequency);

    int getImpulseIntensity() const;
    void setImpulseIntensity(int intensity);

    int getImpulseCount() const;
    void setImpulseCount(int count);

    int getWorkingHeight() const;
    void setWorkingHeight(int height);

    int getDistance() const;
    void setDistance(int distance);

    BodyPosture* getBodyPosture() const;

    Transportation* getTransportation() const;

    Equipment* getEquipment() const;

    WorkCondition* getWorkCondition() const;

    AppliedForce* getAppliedForce() const;

    LoadHandling* getLoadHandling() const;

private:
    int id;
    QString *description;
    int specification;
    QTime *begin;
    QTime *end;
    QString *mtmCode;
    QString *graspingType;
    int frequency;
    int impulseIntensity;
    int impulseCount;
    int workingHeight;
    int distance;
    BodyPosture *bodyPosture;
    Transportation *transportation;
    Equipment *equipment;
    WorkCondition *workCondition;
    AppliedForce *appliedForce;
    LoadHandling *loadHandling;

};

#endif // WORKPROCESS_H
