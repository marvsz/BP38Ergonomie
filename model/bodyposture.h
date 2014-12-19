#ifndef BODYPOSTURE_H
#define BODYPOSTURE_H

#include <QString>
#include "head.h"
#include "torso.h"
#include "arm.h"
#include "leg.h"

class BodyPosture
{
public:
    BodyPosture();

    int getID() const;

    Head* getHead() const;
    void setHead(Head *head);

    Torso* getTorso() const;
    void setTorso(Torso *torso);

    Arm* getLeftArm() const;
    void setLeftArm(Arm *arm);

    Arm* getRightArm() const;
    void setRightArm(Arm *arm);

    Leg* getLeftLeg() const;
    void setLeftLeg(Leg *leg);

    Leg* getRightLeg() const;
    void setRightLeg(Leg *leg);

    QString* getLegPosture() const;
    void setLegPosture(QString* legPosture);
private:
    int id;
    Head *head;
    Torso *torso;
    Arm *leftArm;
    Arm *rightArm;
    Leg *leftLeg;
    Leg *rightLeg;
    QString *legPosture;
};

#endif // BODYPOSTURE_H
