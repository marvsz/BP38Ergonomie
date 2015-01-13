#ifndef BODYPOSTUREVIEW_H
#define BODYPOSTUREVIEW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QVector>
#include "variantspecification.h"
#include "variantcontrol.h"
#include "../enum.h"
#include <QPushButton>
#include <QLabel>


class BodyPostureView : public QWidget
{
    Q_OBJECT

public:
    explicit BodyPostureView(QWidget *parent = 0);

    //Trunk
    int getTrunkTilt() const;
    int getTrunkSidewaysTilt() const;
    int getTrunkTwist() const;

    //Head
    int getHeadTilt() const;
    int getHeadRotation() const;
    int getHeadSidewaysTilt() const;

    //Arm
    int getArmOpeningRight() const;
    int getArmOpeningLeft() const;
    int getUpperArmAngleRight() const;
    int getUpperArmAngleLeft() const;
    int getUpperArmTwistRight() const;
    int getUpperArmTwistLeft() const;
    int getForearmAngleRight() const;
    int getForearmAngleLeft() const;
    int getForearmTwistRight() const;
    int getForearmTwistLeft() const;
    int getWristAngleRight() const;
    int getWristAngleLeft() const;
    int getWristAngleSidewaysRight() const;
    int getWristAngleSidewaysLeft() const;
    int getWristMovementRight() const;
    int getWristMovementLeft() const;

    //Leg
    int getHipAngleRight() const;
    int getHipAngleLeft() const;
    int getHipAngleSidewaysRight() const;
    int getHipAngleSidewaysLeft() const;
    int getHipTwistRight() const;
    int getHipTwistLeft() const;
    int getKneeAngleRight() const;
    int getKneeAngleLeft() const;
    int getAnkleAngleRight() const;
    int getAnkleAngleLeft() const;
    int getAnkleAngleSidewaysRight() const;
    int getAnkleAngleSidewaysLeft() const;

public slots:

signals:

private:
    static const QVector<int> TRUNK_TILT_VALUES;
    static const QVector<int> TRUNK_TILT_SIDEWAYS_VALUES;
    static const QVector<int> TRUNK_TWIST_VALUES;

    static const QVector<int> HEAD_TILT_VALUES;
    static const QVector<int> HEAD_TILT_SIDEWAYS_VALUES;
    static const QVector<int> HEAD_TILT_TWIST_VALUES;

    static const QVector<int> UPPER_ARM_ANGLE_VALUES;
    static const QVector<int> FOREARM_ANGLE_VALUES;
    static const QVector<int> UPPER_ARM_TWIST_VALUES;
    static const QVector<int> FOREARM_TWIST_VALUES;
    static const QVector<int> ARM_OPENING_VALUES;
    static const QVector<int> WRIST_ANGLE_VALUES;
    static const QVector<int> WRIST_ANGLE_SIDEWAYS_VALUES;
    static const QVector<int> WRIST_MOVEMENT_VALUES;

    static const QVector<int> HIP_ANGLE_VALUES;
    static const QVector<int> HIP_ANGLE_SIDEWAYS_VALUES;
    static const QVector<int> HIP_TWIST_VALUES;
    static const QVector<int> KNEE_ANGLE_VALUES;
    static const QVector<int> ANKLE_ANGLE_VALUES;
    static const QVector<int> ANKLE_ANGLE_SIDEWAYS_VALUES;

    VariantControl *varConTrunk;

    ValueControl *vcTrunkTilt;
    ValueControl *vcTrunkSidewaysTilt;
    ValueControl *vcTrunkTwist;

    VariantSpecification* varSpeciArms;
    VariantSpecification* varSpeciLegs;


};

#endif // BODYPOSTUREVIEW_H
