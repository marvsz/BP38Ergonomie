#include "bodypostureview.h"
#include "flickcharm.h"
#include <QPushButton>
#include <QGroupBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QResizeEvent>
#include <QScroller>

const QVector<int> BodyPostureView::TRUNK_TILT_VALUES = QVector<int>()<<-45<<-20<<0<<20<<45<<90<<110;
const QVector<int> BodyPostureView::TRUNK_TILT_SIDEWAYS_VALUES = QVector<int>()<<0<<20<<45<<60<<90;
const QVector<int> BodyPostureView::TRUNK_TWIST_VALUES = QVector<int>()<<0<<20<<45<<60<<90;

const QVector<int> BodyPostureView::HEAD_TILT_VALUES = QVector<int>()<<-90<<-45<<0<<45<<90;
const QVector<int> BodyPostureView::HEAD_TILT_SIDEWAYS_VALUES = QVector<int>()<<0<<20<<45;
const QVector<int> BodyPostureView::HEAD_TILT_TWIST_VALUES = QVector<int>()<<0<<20<<45;

const QVector<int> BodyPostureView::UPPER_ARM_ANGLE_VALUES = QVector<int>()<<-90<<0<<45<<90<<135<<180;
const QVector<int> BodyPostureView::FOREARM_ANGLE_VALUES = QVector<int>()<<0<<45<<90<<135<<180;
const QVector<int> BodyPostureView::UPPER_ARM_TWIST_VALUES = QVector<int>()<<-45<<0<<45<<90;
const QVector<int> BodyPostureView::FOREARM_TWIST_VALUES = QVector<int>()<<-90<<-45<<0<<45<<90;
const QVector<int> BodyPostureView::ARM_OPENING_VALUES = QVector<int>()<<-90<<-45<<0<<45<<90;
const QVector<int> BodyPostureView::WRIST_ANGLE_VALUES = QVector<int>()<<-45<<-20<<0<<20<<45;
const QVector<int> BodyPostureView::WRIST_ANGLE_SIDEWAYS_VALUES = QVector<int>()<<-45<<-20<<0<<20<<45;
const QVector<int> BodyPostureView::WRIST_MOVEMENT_VALUES = QVector<int>()<<-45<<-20<<0<<20<<45;

const QVector<int> BodyPostureView::HIP_ANGLE_VALUES = QVector<int>()<<45<<90<<135<<180;
const QVector<int> BodyPostureView::HIP_ANGLE_SIDEWAYS_VALUES = QVector<int>()<<-45<<-20<<0<<20<<45;
const QVector<int> BodyPostureView::HIP_TWIST_VALUES = QVector<int>()<<0<<20<<45<<60<<90;
const QVector<int> BodyPostureView::KNEE_ANGLE_VALUES = QVector<int>()<<0<<45<<90<<135<<180;
const QVector<int> BodyPostureView::ANKLE_ANGLE_VALUES = QVector<int>()<<90<<135<<180;
const QVector<int> BodyPostureView::ANKLE_ANGLE_SIDEWAYS_VALUES = QVector<int>()<<-45<<-20<<0<<20<<45;

BodyPostureView::BodyPostureView(QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout *categoryLayout = new QVBoxLayout;
    QScrollArea *categoryScrollArea = new QScrollArea;

    varSpeciArms = new VariantSpecification();
    //varSpeciArms->addSpezification(new QString(tr("both"))); varSpeciArms->addSpezification(new QString(tr("left"))); varSpeciArms->addSpezification(new QString(tr("right")));
    varSpeciLegs = new VariantSpecification();
    //varSpeciLegs->addSpezification(new QString(tr("both"))); varSpeciLegs->addSpezification(new QString(tr("left"))); varSpeciLegs->addSpezification(new QString(tr("right")));

    /*trunkTilt = new Variant(new QString(tr("flexion")), new SubVariant(new QString(tr("flexion angle")), -60, 120, TRUNK_TILT_VALUES, new QString(tr("torso_Flexion_Icon"))));
    trunkSidewaysTilt = new Variant(new QString(tr("sidewise tilt")), new SubVariant(new QString(tr("sidewise tilt")), 0, 90, TRUNK_TILT_SIDEWAYS_VALUES, new QString(tr("torso_Tilt_Icon"))));
    trunkTwist = new Variant(new QString(tr("rotation")), new SubVariant(new QString(tr("rotation")), 0, 90, TRUNK_TWIST_VALUES, new QString(tr("torso_Rotation_Icon"))));

    headTilt = new Variant(new QString(tr("inclination")), new SubVariant(new QString(tr("head inclination")), -90, 90, HEAD_TILT_VALUES, new QString(tr("head_Tilt_Icon"))));
    headTwist = new Variant(new QString(tr("rotation")), new SubVariant(new QString(tr("head rotation")), 0, 45, HEAD_TILT_TWIST_VALUES, new QString(tr("head_Rotation_Icon"))));
    headSidewaysTilt = new Variant(new QString(tr("sidewise inclination")), new SubVariant(new QString(tr("head inclination")), 0, 45, HEAD_TILT_SIDEWAYS_VALUES, new QString(tr("head_Sidewise_Tilt_Icon"))));

    armAngle = new Variant(new QString(tr("stance")), new SubVariant(new QString(tr("upper arm angle")), -90, 180, UPPER_ARM_ANGLE_VALUES, new QString(tr("upper_Arm_Position_Icon"))));
    forearmAngle = new SubVariant(new QString(tr("forearm angle")), 0, 180, FOREARM_ANGLE_VALUES, new QString(tr("forearm_Position_Icon")));
    armTwist = new Variant(new QString(tr("rotation")), new SubVariant(new QString(tr("upper arm rotation angle")), -45, 90, UPPER_ARM_TWIST_VALUES, new QString(tr("Upper_Arm_Rotation_Icon"))));
    forearmTwist = new SubVariant(new QString(tr("forearm rotation angle")), -90, 90, FOREARM_TWIST_VALUES, new QString(tr("forearm_Rotation_Icon")));
    armOpening = new Variant(new QString(tr("opening")), new SubVariant(new QString(tr("upper arm opening angle")), -90, 90, ARM_OPENING_VALUES, new QString(tr("upper_Arm_Opening_Icon"))));
    wristAngle = new Variant(new QString(tr("wrist")), new SubVariant(new QString(tr("wrist angle")), -45, 45, WRIST_ANGLE_VALUES, new QString(tr("wrist_Angle_Icon"))));
    wristAngleSideways = new SubVariant(new QString(tr("wrist angle sideways")), -45, 45, WRIST_ANGLE_SIDEWAYS_VALUES, new QString(tr("wirst_Angle_Sideways_Icon")));
    wristMovement = new SubVariant(new QString(tr("wirst movement")), -45, 45, WRIST_MOVEMENT_VALUES, new QString(tr("wrist_Movement_Icon")));

    hipAngle = new Variant(new QString(tr("hip angle")), new SubVariant(new QString(tr("hip angle")), 45, 180, HIP_ANGLE_VALUES, new QString(tr("leg_Hip_Icon"))));
    hipAngleSideways = new SubVariant(new QString(tr("Hip angle sideways")), -45, 45, HIP_ANGLE_SIDEWAYS_VALUES, new QString(tr("hip_Angle_Sideways_Icon")));
    hipTwist = new SubVariant(new QString(tr("hip twist")), 0, 90, HIP_TWIST_VALUES, new QString(tr("hip_Twist_Icon")));
    kneeAngle = new Variant(new QString(tr("knee angle")), new SubVariant(new QString("knee angle"), 0, 180, KNEE_ANGLE_VALUES, new QString(tr("knee_Angle_Icon"))));
    ankleAngle = new Variant(new QString(tr("ankle angle")), new SubVariant(new QString(tr("ankle angle")), 90, 180, ANKLE_ANGLE_VALUES, new QString(tr("ankle_Angle_Icon"))));
    ankleSidewaysAngle = new SubVariant(new QString(tr("ankle sideways")), -45, 45, ANKLE_ANGLE_SIDEWAYS_VALUES, new QString(tr("ankle_Angle_Sideways_Icon")));

    acTrunk = new AngleControl(new QString(tr("torso")), trunkTilt, NULL, categoryScrollArea);
    acTrunk->addVariant(trunkSidewaysTilt);
    acTrunk->addVariant(trunkTwist);

    acArms = new AngleControl(new QString(tr("arms")), armAngle, varSpeciArms, categoryScrollArea);
    armAngle->addSubVariant(forearmAngle);
    acArms->addVariant(armTwist);
    armTwist->addSubVariant(forearmTwist);
    acArms->addVariant(armOpening);
    acArms->addVariant(wristAngle);
    wristAngle->addSubVariant(wristAngleSideways);
    wristAngle->addSubVariant(wristMovement);


    acLegs = new AngleControl(new QString(tr("legs")), hipAngle, varSpeciLegs, categoryScrollArea);
    hipAngle->addSubVariant(hipAngleSideways);
    hipAngle->addSubVariant(hipTwist);
    acLegs->addVariant(kneeAngle);
    acLegs->addVariant(ankleAngle);
    ankleAngle->addSubVariant(ankleSidewaysAngle);

    acHead = new AngleControl(new QString(tr("head")), headTwist, NULL, categoryScrollArea);
    acHead->addVariant(headTilt);
    acHead->addVariant(headSidewaysTilt);*/

    QWidget *main = new QWidget();
    /*categoryLayout->addWidget(acTrunk);
    categoryLayout->addWidget(acArms);
    categoryLayout->addWidget(acLegs);
    categoryLayout->addWidget(acHead);*/
    main->setLayout(categoryLayout);

    categoryScrollArea->setWidget(main);
    categoryScrollArea->setWidgetResizable(true);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(categoryScrollArea);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(categoryScrollArea);
    this->setLayout(mainLayout);

}


//GETTER
//Trunk
int BodyPostureView::getTrunkTilt() const{
}
int BodyPostureView::getTrunkSidewaysTilt() const{}
int BodyPostureView::getTrunkTwist() const{}

//Head
int BodyPostureView::getHeadTilt() const{}
int BodyPostureView::getHeadRotation() const{}
int BodyPostureView::getHeadSidewaysTilt() const{}

//Arm
int BodyPostureView::getArmOpeningRight() const{}
int BodyPostureView::getArmOpeningLeft() const{}
int BodyPostureView::getUpperArmAngleRight() const{}
int BodyPostureView::getUpperArmAngleLeft() const{}
int BodyPostureView::getUpperArmTwistRight() const{}
int BodyPostureView::getUpperArmTwistLeft() const{}
int BodyPostureView::getForearmAngleRight() const{}
int BodyPostureView::getForearmAngleLeft() const{}
int BodyPostureView::getForearmTwistRight() const{}
int BodyPostureView::getForearmTwistLeft() const{}
int BodyPostureView::getWristAngleRight() const{}
int BodyPostureView::getWristAngleLeft() const{}
int BodyPostureView::getWristAngleSidewaysRight() const{}
int BodyPostureView::getWristAngleSidewaysLeft() const{}
int BodyPostureView::getWristMovementRight() const{}
int BodyPostureView::getWristMovementLeft() const{}

//Leg
int BodyPostureView::getHipAngleRight() const{}
int BodyPostureView::getHipAngleLeft() const{}
int BodyPostureView::getHipAngleSidewaysRight() const{}
int BodyPostureView::getHipAngleSidewaysLeft() const{}
int BodyPostureView::getHipTwistRight() const{}
int BodyPostureView::getHipTwistLeft() const{}
int BodyPostureView::getKneeAngleRight() const{}
int BodyPostureView::getKneeAngleLeft() const{}
int BodyPostureView::getAnkleAngleRight() const{}
int BodyPostureView::getAnkleAngleLeft() const{}
int BodyPostureView::getAnkleAngleSidewaysRight() const{}
int BodyPostureView::getAnkleAngleSidewaysLeft() const{}
