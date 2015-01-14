#include "bodypostureview.h"
#include "flickcharm.h"
#include "separator.h"
#include <QVBoxLayout>
#include <QScrollArea>

const QVector<int> BodyPostureView::TRUNK_TILT_VALUES = QVector<int>()<<-45<<-20<<0<<20<<45<<90<<110;
const QVector<int> BodyPostureView::TRUNK_TILT_SIDEWAYS_VALUES = QVector<int>()<<0<<20<<45<<60<<90;
const QVector<int> BodyPostureView::TRUNK_TWIST_VALUES = QVector<int>()<<0<<20<<45<<60<<90;

const QVector<int> BodyPostureView::HEAD_TILT_VALUES = QVector<int>()<<-90<<-45<<0<<45<<90;
const QVector<int> BodyPostureView::HEAD_TILT_SIDEWAYS_VALUES = QVector<int>()<<0<<20<<45;
const QVector<int> BodyPostureView::HEAD_TWIST_VALUES = QVector<int>()<<0<<20<<45;

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
    QWidget(parent),
    varConTrunk(new VariantControl()),
    varConArms(new VariantControl()),
    varConLegs(new VariantControl()),
    varConHead(new VariantControl()),
    vcTrunkTilt(new ValueControl(VALUE)),
    vcTrunkSidewaysTilt(new ValueControl(VALUE)),
    vcTrunkTwist(new ValueControl(VALUE)),
    vcUpperArmAngle(new ValueControl(VALUE)),
    vcForearmAngle(new ValueControl(VALUE)),
    vcUpperArmTwist(new ValueControl(VALUE)),
    vcForearmTwist(new ValueControl(VALUE)),
    vcArmOpening(new ValueControl(VALUE)),
    vcWristAngle(new ValueControl(VALUE)),
    vcWristAngleSideways(new ValueControl(VALUE)),
    vcWristMovement(new ValueControl(VALUE)),
    vcHipAngle(new ValueControl(VALUE)),
    vcHipAngleSideways(new ValueControl(VALUE)),
    vcHipTwist(new ValueControl(VALUE)),
    vcKneeAngle(new ValueControl(VALUE)),
    vcAnkleAngle(new ValueControl(VALUE)),
    vcAnkleAngleSideways(new ValueControl(VALUE)),
    vcHeadTilt(new ValueControl(VALUE)),
    vcHeadTiltSideways(new ValueControl(VALUE)),
    vcHeadTwist(new ValueControl(VALUE)),
    varSpeciArms(new VariantSpecification()),
    varSpeciLegs(new VariantSpecification()),
    armSpeci_Type(3),
    legSpeci_Type(3)
{

    QVBoxLayout *categoryLayout = new QVBoxLayout;
    QScrollArea *categoryScrollArea = new QScrollArea;

    varSpeciArms->addSpecification(QString(tr("both")), 3, 3);
    varSpeciArms->addSpecification(QString(tr("left")), 2, 2);
    varSpeciArms->addSpecification(QString(tr("right")), 1, 1);
    connect(varSpeciArms, SIGNAL(selectedSpeciValueChanged(int)), this, SLOT(armSpeciChanged(int)));
    varSpeciLegs->addSpecification(QString(tr("both")), 3, 3);
    varSpeciLegs->addSpecification(QString(tr("left")), 2, 2);
    varSpeciLegs->addSpecification(QString(tr("right")), 1, 1);
    connect(varSpeciLegs, SIGNAL(selectedSpeciValueChanged(int)), this, SLOT(legSpeciChanged(int)));

    vcTrunkTilt->setUnit("°");
    vcTrunkTilt->setText(tr("Trunk tilt"));
    vcTrunkTilt->setValues(-60, 120, TRUNK_TILT_VALUES, QString(tr("trunk_tilt_icon_path")));
    connect(vcTrunkTilt, SIGNAL(valueChanged(int)), this, SLOT(vcTrunkTiltValueChanged(int)));

    vcTrunkSidewaysTilt->setUnit("°");
    vcTrunkSidewaysTilt->setText(tr("Trunk sideways tilt"));
    vcTrunkSidewaysTilt->setValues(0, 90, TRUNK_TILT_SIDEWAYS_VALUES, QString(tr("trunk_tilt_sideways_icon_path")));
    connect(vcTrunkSidewaysTilt, SIGNAL(valueChanged(int)), this, SLOT(vcTrunkTiltSidewaysValueChanged(int)));

    vcTrunkTwist->setUnit("°");
    vcTrunkTwist->setText(tr("Trunk twist"));
    vcTrunkTwist->setValues(0, 90, TRUNK_TWIST_VALUES, QString(tr("trunk_twist_icon_path")));
    connect(vcTrunkTwist, SIGNAL(valueChanged(int)), this, SLOT(vcTrunkTwistValueChanged(int)));

    vcUpperArmAngle->setUnit(tr("°"));
    vcUpperArmAngle->setText(tr("Upper arm angle"));
    vcUpperArmAngle->setValues(-90, 180, UPPER_ARM_ANGLE_VALUES, QString(tr("upper_arm_angle_icon_path")));

    vcForearmAngle->setUnit(tr("°"));
    vcForearmAngle->setText(tr("Forearm angle"));
    vcForearmAngle->setValues(0, 180, FOREARM_ANGLE_VALUES, QString(tr("forearm_angle_icon_path")));

    vcUpperArmTwist->setUnit(tr("°"));
    vcUpperArmTwist->setText(tr("Upper arm twist"));
    vcUpperArmTwist->setValues(-45, 90, UPPER_ARM_TWIST_VALUES, QString(tr("upper_arm_twist_icon_path")));

    vcForearmTwist->setUnit(tr("°"));
    vcForearmTwist->setText(tr("Forearm twist"));
    vcForearmTwist->setValues(-90, 90, FOREARM_TWIST_VALUES, QString(tr("forearm_twist_icon_path")));

    vcArmOpening->setUnit(tr("°"));
    vcArmOpening->setText(tr("Arm opening"));
    vcArmOpening->setValues(-90, 90, ARM_OPENING_VALUES, QString(tr("arm_opening_icon_path")));

    vcWristAngle->setUnit(tr("°"));
    vcWristAngle->setText(tr("Wrist angle"));
    vcWristAngle->setValues(-45, 45, WRIST_ANGLE_VALUES, QString(tr("wrist_angle_icon_path")));

    vcWristAngleSideways->setUnit(tr("°"));
    vcWristAngleSideways->setText(tr("Wrist sideways angle"));
    vcWristAngleSideways->setValues(-45, 45, WRIST_ANGLE_SIDEWAYS_VALUES, QString(tr("wrist_angle_sideways_icon_path")));

    vcWristMovement->setUnit(tr("°"));
    vcWristMovement->setText(tr("Wrist movement"));
    vcWristMovement->setValues(-45, 45, WRIST_MOVEMENT_VALUES, QString(tr("wrist_movement_icon_path")));

    vcHipAngle->setUnit("°");
    vcHipAngle->setText(tr("Hip angle"));
    vcHipAngle->setValues(-45, 180, HIP_ANGLE_VALUES, QString(tr("hip_angle_icon_path")));

    vcHipAngleSideways->setUnit("°");
    vcHipAngleSideways->setText(tr("Hip sideways angle"));
    vcHipAngleSideways->setValues(-45, 45, HIP_ANGLE_SIDEWAYS_VALUES, QString(tr("hip_angle_sideways_icon_path")));

    vcHipTwist->setUnit("°");
    vcHipTwist->setText(tr("Hip twist"));
    vcHipTwist->setValues(0, 90, HIP_TWIST_VALUES, QString(tr("hip_twist_icon_path")));

    vcKneeAngle->setUnit("°");
    vcKneeAngle->setText(tr("Knee angle"));
    vcKneeAngle->setValues(0, 180, KNEE_ANGLE_VALUES, QString(tr("knee_angle_icon_path")));

    vcAnkleAngle->setUnit("°");
    vcAnkleAngle->setText(tr("Ankle angle"));
    vcAnkleAngle->setValues(90, 180, ANKLE_ANGLE_VALUES, QString(tr("ankle_angle_icon_path")));

    vcAnkleAngleSideways->setUnit("°");
    vcAnkleAngleSideways->setText(tr("Ankle sideways angle"));
    vcAnkleAngleSideways->setValues(-45, 45, ANKLE_ANGLE_SIDEWAYS_VALUES, QString(tr("ankle_angle_sideways_icon_path")));

    vcHeadTilt->setUnit("°");
    vcHeadTilt->setText(tr("Head tilt"));
    vcHeadTilt->setValues(-90, 90, HEAD_TILT_VALUES, QString(tr("head_tilt_icon_path")));

    vcHeadTiltSideways->setUnit("°");
    vcHeadTiltSideways->setText(tr("Head sideways tilt"));
    vcHeadTiltSideways->setValues(0, 45, HEAD_TILT_SIDEWAYS_VALUES, QString(tr("head_tilt_sideways_icon_path")));

    vcHeadTwist->setUnit("°");
    vcHeadTwist->setText(tr("Head twist"));
    vcHeadTwist->setValues(0, 45, HEAD_TWIST_VALUES, QString(tr("head_twist_icon_path")));

    varConTrunk->setName(tr("Trunk"));
    varConTrunk->addVariant(tr("Tilt"));
    varConTrunk->addSubVariant(0, vcTrunkTilt);
    varConTrunk->addVariant(tr("Sideways tilt"));
    varConTrunk->addSubVariant(1, vcTrunkSidewaysTilt);
    varConTrunk->addVariant(tr("Twist"));
    varConTrunk->addSubVariant(2, vcTrunkTwist);
    varConTrunk->setSelectedVariant(0);
    varConTrunk->hideContent();
    connect(varConTrunk, SIGNAL(requestShowContent(QString)), this, SLOT(varConRequestShowContent(QString)));
    connect(this, SIGNAL(showExclusiveContentByName(QString)), varConTrunk, SLOT(setExclusiveDisplayByName(QString)));


    varConArms->setName(tr("Arms"));
    varConArms->addVariant(tr("Posture"));
    varConArms->addSubVariant(0, vcUpperArmAngle);
    varConArms->addSubVariant(0, vcForearmAngle);
    varConArms->addVariant(tr("Twist"));
    varConArms->addSubVariant(1, vcUpperArmTwist);
    varConArms->addSubVariant(1, vcForearmTwist);
    varConArms->addVariant(tr("Opening"));
    varConArms->addSubVariant(2, vcArmOpening);
    varConArms->addVariant(tr("Wrist"));
    varConArms->addSubVariant(3, vcWristAngle);
    varConArms->addSubVariant(3, vcWristAngleSideways);
    varConArms->addSubVariant(3, vcWristMovement);
    varConArms->setSpecification(varSpeciArms);
    varConArms->setSelectedSpecification(3);
    varConArms->setSelectedVariant(0);
    varConArms->hideContent();
    connect(varConArms, SIGNAL(requestShowContent(QString)), this, SLOT(varConRequestShowContent(QString)));
    connect(this, SIGNAL(showExclusiveContentByName(QString)), varConArms, SLOT(setExclusiveDisplayByName(QString)));

    varConLegs->setName(tr("Legs"));
    varConLegs->addVariant(tr("Hip"));
    varConLegs->addSubVariant(0, vcHipAngle);
    varConLegs->addSubVariant(0, vcHipAngleSideways);
    varConLegs->addVariant(tr("Knee"));
    varConLegs->addSubVariant(1, vcKneeAngle);
    varConLegs->addVariant(tr("Ankle"));
    varConLegs->addSubVariant(2, vcAnkleAngle);
    varConLegs->addSubVariant(2, vcAnkleAngleSideways);
    varConLegs->setSpecification(varSpeciLegs);
    varConLegs->setSelectedSpecification(3);
    varConLegs->setSelectedVariant(0);
    varConLegs->hideContent();
    connect(varConLegs, SIGNAL(requestShowContent(QString)), this, SLOT(varConRequestShowContent(QString)));
    connect(this, SIGNAL(showExclusiveContentByName(QString)), varConLegs, SLOT(setExclusiveDisplayByName(QString)));

    varConHead->setName(tr("Head"));
    varConHead->addVariant(tr("Tilt"));
    varConHead->addSubVariant(0, vcHeadTilt);
    varConHead->addVariant(tr("Sideways tilt"));
    varConHead->addSubVariant(1, vcHeadTiltSideways);
    varConHead->addVariant(tr("Twist"));
    varConHead->addSubVariant(2, vcHeadTwist);
    varConHead->setSelectedVariant(0);
    varConHead->hideContent();
    connect(varConHead, SIGNAL(requestShowContent(QString)), this, SLOT(varConRequestShowContent(QString)));
    connect(this, SIGNAL(showExclusiveContentByName(QString)), varConHead, SLOT(setExclusiveDisplayByName(QString)));

    QWidget *main = new QWidget();;
    categoryLayout->addWidget(varConTrunk);
    categoryLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    categoryLayout->addWidget(varConArms);
    categoryLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    categoryLayout->addWidget(varConLegs);
    categoryLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    categoryLayout->addWidget(varConHead);
    main->setLayout(categoryLayout);

    categoryScrollArea->setWidget(main);
    categoryScrollArea->setWidgetResizable(true);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(categoryScrollArea);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(categoryScrollArea);
    this->setLayout(mainLayout);

}


//PRIVATE SLOTS
void BodyPostureView::varConRequestShowContent(const QString &name){
    emit showExclusiveContentByName(name);
}

void BodyPostureView::armSpeciChanged(int type){
    armSpeci_Type = type;
}

void BodyPostureView::legSpeciChanged(int type){
    legSpeci_Type = type;
}

void BodyPostureView::vcTrunkTiltValueChanged(int value){
    record.setValue(DBConstants::COL_BODY_POSTURE_TRUNK_TILT, value);
}

void BodyPostureView::vcTrunkTiltSidewaysValueChanged(int value){}
void BodyPostureView::vcTrunkTwistValueChanged(int value){}

void BodyPostureView::vcUpperArmAngleValueChanged(int value){
    if(armSpeci_Type == 1 || armSpeci_Type == 3)
        record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT, value);
    if(armSpeci_Type == 2 || armSpeci_Type == 3)
        record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT, value);
}
void BodyPostureView::vcForearmAngleValueChanged(int value){}
void BodyPostureView::vcUpperArmTwistValueChanged(int value){}
void BodyPostureView::vcForearmTwistValueChanged(int value){}
void BodyPostureView::vcArmOpeningValueChanged(int value){}
void BodyPostureView::vcWristAngleValueChanged(int value){}
void BodyPostureView::vcWristAngleSidewaysValueChanged(int value){}
void BodyPostureView::vcWristMovementValueChanged(int value){}

void BodyPostureView::vcHipAngleValueChanged(int value){}
void BodyPostureView::vcHipAngleSidewaysValueChanged(int value){}
void BodyPostureView::vcHipTwistValueChanged(int value){}
void BodyPostureView::vcKneeAngleValueChanged(int value){}
void BodyPostureView::vcAnkleAngleValueChanged(int value){}
void BodyPostureView::vcAnkleAngleSidewaysValueChanged(int value){}

void BodyPostureView::vcHeadTiltValueChanged(int value){}
void BodyPostureView::vcHeadTiltSidewaysValueChanged(int value){}
void BodyPostureView::vcHeadTwistValueChanged(int value){}

//GETTER SETTER
QSqlRecord BodyPostureView::getRecord() const{
    return this->record;
}
void BodyPostureView::setRecord(const QSqlRecord &record){
    this->record = record;
}

