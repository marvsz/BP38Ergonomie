#include "bodypostureview.h"
#include "../../flickcharm.h"
#include "../../separator.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QDebug>

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
    TitledWidget(tr("Body posture"), parent),
    quickSelectionLayout(new QuickSelectionControl()),
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
    values = QHash<QString, QVariant>();

    QVBoxLayout *categoryLayout = new QVBoxLayout;
    QScrollArea *categoryScrollArea = new QScrollArea;

    varSpeciArms->addSpecification(QString(tr("both")), 3, 3);
    varSpeciArms->addSpecification(QString(tr("left")), 1, 1);
    varSpeciArms->addSpecification(QString(tr("right")), 2, 2);
    connect(varSpeciArms, SIGNAL(selectedSpeciValueChanged(int)), this, SLOT(armSpeciChanged(int)));
    varSpeciLegs->addSpecification(QString(tr("both")), 3, 3);
    varSpeciLegs->addSpecification(QString(tr("left")), 1, 1);
    varSpeciLegs->addSpecification(QString(tr("right")), 2, 2);
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
    connect(vcUpperArmAngle, SIGNAL(valueChanged(int)),this,SLOT(vcUpperArmAngleValueChanged(int)));

    vcForearmAngle->setUnit(tr("°"));
    vcForearmAngle->setText(tr("Forearm angle"));
    vcForearmAngle->setValues(0, 180, FOREARM_ANGLE_VALUES, QString(tr("forearm_angle_icon_path")));
    connect(vcForearmAngle, SIGNAL(valueChanged(int)),this,SLOT(vcForearmAngleValueChanged(int)));

    vcUpperArmTwist->setUnit(tr("°"));
    vcUpperArmTwist->setText(tr("Upper arm twist"));
    vcUpperArmTwist->setValues(-45, 90, UPPER_ARM_TWIST_VALUES, QString(tr("upper_arm_twist_icon_path")));
    connect(vcUpperArmTwist, SIGNAL(valueChanged(int)),this,SLOT(vcUpperArmTwistValueChanged(int)));

    vcForearmTwist->setUnit(tr("°"));
    vcForearmTwist->setText(tr("Forearm twist"));
    vcForearmTwist->setValues(-90, 90, FOREARM_TWIST_VALUES, QString(tr("forearm_twist_icon_path")));
    connect(vcForearmTwist,SIGNAL(valueChanged(int)),this,SLOT(vcForearmTwistValueChanged(int)));

    vcArmOpening->setUnit(tr("°"));
    vcArmOpening->setText(tr("Arm opening"));
    vcArmOpening->setValues(-90, 90, ARM_OPENING_VALUES, QString(tr("arm_opening_icon_path")));
    connect(vcArmOpening, SIGNAL(valueChanged(int)),this,SLOT(vcArmOpeningValueChanged(int)));

    vcWristAngle->setUnit(tr("°"));
    vcWristAngle->setText(tr("Wrist angle"));
    vcWristAngle->setValues(-45, 45, WRIST_ANGLE_VALUES, QString(tr("wrist_angle_icon_path")));
    connect(vcWristAngle, SIGNAL(valueChanged(int)), this, SLOT(vcWristAngleValueChanged(int)));

    vcWristAngleSideways->setUnit(tr("°"));
    vcWristAngleSideways->setText(tr("Wrist sideways angle"));
    vcWristAngleSideways->setValues(-45, 45, WRIST_ANGLE_SIDEWAYS_VALUES, QString(tr("wrist_angle_sideways_icon_path")));
    connect(vcWristAngleSideways, SIGNAL(valueChanged(int)), this, SLOT(vcWristAngleSidewaysValueChanged(int)));

    vcWristMovement->setUnit(tr("°"));
    vcWristMovement->setText(tr("Wrist movement"));
    vcWristMovement->setValues(-45, 45, WRIST_MOVEMENT_VALUES, QString(tr("wrist_movement_icon_path")));
    connect(vcWristMovement, SIGNAL(valueChanged(int)), this, SLOT(vcWristMovementValueChanged(int)));

    vcHipAngle->setUnit("°");
    vcHipAngle->setText(tr("Hip angle"));
    vcHipAngle->setValues(-45, 180, HIP_ANGLE_VALUES, QString(tr("hip_angle_icon_path")));
    connect(vcHipAngle, SIGNAL(valueChanged(int)), this, SLOT(vcHipAngleValueChanged(int)));

    vcHipAngleSideways->setUnit("°");
    vcHipAngleSideways->setText(tr("Hip sideways angle"));
    vcHipAngleSideways->setValues(-45, 45, HIP_ANGLE_SIDEWAYS_VALUES, QString(tr("hip_angle_sideways_icon_path")));
    connect(vcHipAngleSideways, SIGNAL(valueChanged(int)), this, SLOT(vcHipAngleSidewaysValueChanged(int)));

    vcHipTwist->setUnit("°");
    vcHipTwist->setText(tr("Hip twist"));
    vcHipTwist->setValues(0, 90, HIP_TWIST_VALUES, QString(tr("hip_twist_icon_path")));
    connect(vcHipTwist, SIGNAL(valueChanged(int)), this, SLOT(vcHipTwistValueChanged(int)));

    vcKneeAngle->setUnit("°");
    vcKneeAngle->setText(tr("Knee angle"));
    vcKneeAngle->setValues(0, 180, KNEE_ANGLE_VALUES, QString(tr("knee_angle_icon_path")));
    connect(vcKneeAngle, SIGNAL(valueChanged(int)), this, SLOT(vcKneeAngleValueChanged(int)));

    vcAnkleAngle->setUnit("°");
    vcAnkleAngle->setText(tr("Ankle angle"));
    vcAnkleAngle->setValues(90, 180, ANKLE_ANGLE_VALUES, QString(tr("ankle_angle_icon_path")));
    connect(vcAnkleAngle, SIGNAL(valueChanged(int)), this, SLOT(vcAnkleAngleValueChanged(int)));

    vcAnkleAngleSideways->setUnit("°");
    vcAnkleAngleSideways->setText(tr("Ankle sideways angle"));
    vcAnkleAngleSideways->setValues(-45, 45, ANKLE_ANGLE_SIDEWAYS_VALUES, QString(tr("ankle_angle_sideways_icon_path")));
    connect(vcAnkleAngleSideways, SIGNAL(valueChanged(int)), this, SLOT(vcAnkleAngleSidewaysValueChanged(int)));

    vcHeadTilt->setUnit("°");
    vcHeadTilt->setText(tr("Head tilt"));
    vcHeadTilt->setValues(-90, 90, HEAD_TILT_VALUES, QString(tr("head_tilt_icon_path")));
    connect(vcHeadTilt, SIGNAL(valueChanged(int)), this, SLOT(vcHeadTiltValueChanged(int)));

    vcHeadTiltSideways->setUnit("°");
    vcHeadTiltSideways->setText(tr("Head sideways tilt"));
    vcHeadTiltSideways->setValues(0, 45, HEAD_TILT_SIDEWAYS_VALUES, QString(tr("head_tilt_sideways_icon_path")));
    connect(vcHeadTiltSideways, SIGNAL(valueChanged(int)), this, SLOT(vcHeadTiltSidewaysValueChanged(int)));

    vcHeadTwist->setUnit("°");
    vcHeadTwist->setText(tr("Head twist"));
    vcHeadTwist->setValues(0, 45, HEAD_TWIST_VALUES, QString(tr("head_twist_icon_path")));
    connect(vcHeadTwist, SIGNAL(valueChanged(int)), this, SLOT(vcHeadTwistValueChanged(int)));

    quickSelectionLayout->setName(tr("Quick Selection"));
    quickSelectionLayout->hideContent();
    connect(quickSelectionLayout, SIGNAL(requestShowContent(QString)), this, SLOT(varConRequestShowContent(QString)));
    connect(this, SIGNAL(showExclusiveContentByName(QString)), quickSelectionLayout, SLOT(setExclusiveDisplayByName(QString)));
    connect(quickSelectionLayout, SIGNAL(quickLegPostureChanged(int,int)), this, SLOT(qlpcQuickLegPostureChanged(int,int)));
    connect(quickSelectionLayout, SIGNAL(quickLegPostureSpecificationChanged(int)), this, SLOT(qlpcQuickLegPostureSpecificationChagend(int)));
    connect(quickSelectionLayout, SIGNAL(quickArmPostureChanged(int,int)), this, SLOT(voscQuickArmPostureChanged(int,int)));
    connect(quickSelectionLayout, SIGNAL(quickTrunkPostureChanged(int)), this, SLOT(voscQuickTrunkPostureChanged(int)));

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
    varConArms->setSelectedSpecification(AVType::BASIC);
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
    varConLegs->setSelectedSpecification(AVType::BASIC);
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
    categoryLayout->addWidget(quickSelectionLayout);
    categoryLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
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

//PUBLIC SLOTS
void BodyPostureView::setSelectedType(const AVType &type){
    varConLegs->setSelectedVariant(0);
    varConHead->setSelectedVariant(0);
    varConArms->setSelectedVariant(0);
    varConTrunk->setSelectedVariant(0);

    varConArms->setSelectedSpecification(type);
    varConLegs->setSelectedSpecification(type);
    switch(type){
    case AVType::LEFT: case AVType::RIGHT:
            emit showExclusiveContentByName(tr("Arms"));
            break;
    case AVType::BASIC:
            emit showExclusiveContentByName(tr("Trunk"));
            break;
    default:
            emit showExclusiveContentByName(tr("Nothing"));
        break;
    }
}

//PRIVATE SLOTS
void BodyPostureView::varConRequestShowContent(const QString &name){
    emit showExclusiveContentByName(name);
}

void BodyPostureView::armSpeciChanged(int type){
    armSpeci_Type = type;
    vcUpperArmAngle->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT).toInt());
    vcForearmAngle->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT).toInt());
    vcUpperArmTwist->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_UPPER_ARM_TWIST_LEFT : DBConstants::COL_BODY_POSTURE_UPPER_ARM_TWIST_RIGHT).toInt());
    vcForearmTwist->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_FOREARM_TWIST_LEFT : DBConstants::COL_BODY_POSTURE_FOREARM_TWIST_RIGHT).toInt());
    vcArmOpening->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_ARM_OPENING_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_ARM_OPENING_ANGLE_RIGHT).toInt());
    vcWristAngle->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_RIGHT).toInt());
    vcWristAngleSideways->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_LEFT : DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_RIGHT).toInt());
    vcWristMovement->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_WRIST_MOVEMENT_LEFT : DBConstants::COL_BODY_POSTURE_WRIST_MOVEMENT_RIGHT).toInt());
}

void BodyPostureView::legSpeciChanged(int type){
    legSpeci_Type = type;
    vcHipAngle->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT).toInt());
    vcHipAngleSideways->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_LEFT : DBConstants::COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_RIGHT).toInt());
    vcHipTwist->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_HIP_TWIST_LEFT : DBConstants::COL_BODY_POSTURE_HIP_TWIST_RIGHT).toInt());
    vcKneeAngle->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT).toInt());
    vcAnkleAngle->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT).toInt());
    vcAnkleAngleSideways->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_LEFT : DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_RIGHT).toInt());
}

void BodyPostureView::voscQuickTrunkPostureChanged(int id){
    //qDebug()<<id;

    switch(id){

    case 0:
            values.insert(DBConstants::COL_BODY_POSTURE_TRUNK_TILT,110);
            vcTrunkTilt->setValue(110);
            break;

    case 1:
            values.insert(DBConstants::COL_BODY_POSTURE_TRUNK_TILT,20);
            vcTrunkTilt->setValue(20);
            break;

    case 2:
            values.insert(DBConstants::COL_BODY_POSTURE_TRUNK_TILT,0);
            vcTrunkTilt->setValue(0);
            break;


    case 3:
            values.insert(DBConstants::COL_BODY_POSTURE_TRUNK_TILT,-20);
            vcTrunkTilt->setValue(-20);
            break;


    case 4:
            values.insert(DBConstants::COL_BODY_POSTURE_TRUNK_TILT,-45);
            vcTrunkTilt->setValue(-45);
            break;
    default:
        break;

    }
}

void BodyPostureView::voscQuickArmPostureChanged(int id, int sel){
qDebug()<<"Option"<<id<<"Spezifikation"<<sel;
    switch(id){
        case 0:
        switch(sel){
        case 0:
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,0);
            vcUpperArmAngle->setValue(0);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,90);
            vcForearmAngle->setValue(90);
            break;

        case 1:
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,0);
            vcUpperArmAngle->setValue(0);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,90);
            vcForearmAngle->setValue(90);
            break;

        case 2:
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,0);
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,0);
            vcUpperArmAngle->setValue(0);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,90);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,90);
            vcForearmAngle->setValue(90);
            break;
        default:
            break;
        }

        break;

        case 1:
        switch(sel){
        case 0:
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,90);
            vcUpperArmAngle->setValue(90);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,180);
            vcForearmAngle->setValue(180);
            break;

        case 1:
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,90);
            vcUpperArmAngle->setValue(90);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,180);
            vcForearmAngle->setValue(180);
            break;

        case 2:
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,90);
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,90);
            vcUpperArmAngle->setValue(90);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,180);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,180);
            vcForearmAngle->setValue(180);
            break;
        default:
            break;
        }
        break;

        case 2:
        switch(sel){
        case 0:
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,135);
            vcUpperArmAngle->setValue(135);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,180);
            vcForearmAngle->setValue(180);
            break;

        case 1:
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,135);
            vcUpperArmAngle->setValue(135);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,180);
            vcForearmAngle->setValue(180);
            break;

        case 2:
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,135);
            values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,135);
            vcUpperArmAngle->setValue(135);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,180);
            values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,180);
            vcForearmAngle->setValue(180);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

/*void BodyPostureView::voscQuickArmPostureSpecificationChanged(int id){
qDebug()<<"Spezifikation"<<id;
}*/

void BodyPostureView::qlpcQuickLegPostureChanged(int id, int speci){
    qDebug()<<"Bein Option"<<id<<"Bein Spezifikation"<<speci;
    switch (id) {
    case 0:
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,180);
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,180);
        vcHipAngle->setValue(180);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,180);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,180);
        vcKneeAngle->setValue(180);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    case 1:
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,90);
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,90);
        vcHipAngle->setValue(90);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,90);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,90);
        vcKneeAngle->setValue(90);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    case 2:
        switch(speci){
        case 0:
            values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,135);
            values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,90);
            vcHipAngle->setValue(90);
            values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,0);
            values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,45);
            vcKneeAngle->setValue(45);
            values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
            values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
            vcAnkleAngle->setValue(90);
            break;
        case 1:
            values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,90);
            values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,135);
            vcHipAngle->setValue(90);
            values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,45);
            values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,0);
            vcKneeAngle->setValue(45);
            values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
            values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
            vcAnkleAngle->setValue(90);
            break;
        case 2:
            values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,135);
            values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,135);
            vcHipAngle->setValue(135);
            values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,0);
            values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,0);
            vcKneeAngle->setValue(0);
            values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
            values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
            vcAnkleAngle->setValue(90);
            break;
        }

        break;
    case 3:
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,180);
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,180);
        vcHipAngle->setValue(180);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,180);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,180);
        vcKneeAngle->setValue(180);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    case 4:
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,180);
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,180);
        vcHipAngle->setValue(180);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,180);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,180);
        vcKneeAngle->setValue(180);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;

    default:
        break;
    }
}

void BodyPostureView::qlpcQuickLegPostureSpecificationChagend(int id){
    qDebug()<<"Bein Spezifikation"<<id;
    switch(id){
    case 0:
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,135);
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,90);
        vcHipAngle->setValue(90);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,0);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,45);
        vcKneeAngle->setValue(45);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    case 1:
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,90);
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,135);
        vcHipAngle->setValue(90);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,45);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,0);
        vcKneeAngle->setValue(45);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    case 2:
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,135);
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,135);
        vcHipAngle->setValue(135);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,0);
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,0);
        vcKneeAngle->setValue(0);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    }
}

void BodyPostureView::vcTrunkTiltValueChanged(int value){
    values.insert(DBConstants::COL_BODY_POSTURE_TRUNK_TILT, value);
}

void BodyPostureView::vcTrunkTiltSidewaysValueChanged(int value){
    values.insert(DBConstants::COL_BODY_POSTURE_TRUNK_TILT_SIDEWAYS, value);
}

void BodyPostureView::vcTrunkTwistValueChanged(int value){
    values.insert(DBConstants::COL_BODY_POSTURE_TRUNK_TWIST, value);
}

void BodyPostureView::vcUpperArmAngleValueChanged(int value){
    if(armSpeci_Type == 1 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT, value);
    if(armSpeci_Type == 2 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT, value);
}

void BodyPostureView::vcForearmAngleValueChanged(int value){
    if(armSpeci_Type == 1 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT, value);
    if(armSpeci_Type == 2 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT, value);
}

void BodyPostureView::vcUpperArmTwistValueChanged(int value){
    if(armSpeci_Type == 1 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_TWIST_LEFT, value);
    if(armSpeci_Type == 2 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_UPPER_ARM_TWIST_RIGHT, value);
}

void BodyPostureView::vcForearmTwistValueChanged(int value){
    if(armSpeci_Type == 1 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_TWIST_LEFT, value);
    if(armSpeci_Type == 2 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_FOREARM_TWIST_RIGHT, value);
}

void BodyPostureView::vcArmOpeningValueChanged(int value){
    if(armSpeci_Type == 1 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_ARM_OPENING_ANGLE_LEFT, value);
    if(armSpeci_Type == 2 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_ARM_OPENING_ANGLE_RIGHT, value);
}

void BodyPostureView::vcWristAngleValueChanged(int value){
    if(armSpeci_Type == 1 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_LEFT, value);
    if(armSpeci_Type == 2 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_RIGHT, value);
}

void BodyPostureView::vcWristAngleSidewaysValueChanged(int value){
    if(armSpeci_Type == 1 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_LEFT, value);
    if(armSpeci_Type == 2 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_RIGHT, value);
}

void BodyPostureView::vcWristMovementValueChanged(int value){
    if(armSpeci_Type == 1 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_WRIST_MOVEMENT_LEFT, value);
    if(armSpeci_Type == 2 || armSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_WRIST_MOVEMENT_RIGHT, value);
}


void BodyPostureView::vcHipAngleValueChanged(int value){
    if(legSpeci_Type == 1 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT, value);
    if(legSpeci_Type == 2 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT, value);
}

void BodyPostureView::vcHipAngleSidewaysValueChanged(int value){
    if(legSpeci_Type == 1 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_LEFT, value);
    if(legSpeci_Type == 2 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_RIGHT, value);
}

void BodyPostureView::vcHipTwistValueChanged(int value){
    if(legSpeci_Type == 1 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_TWIST_LEFT, value);
    if(legSpeci_Type == 2 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_HIP_TWIST_RIGHT, value);
}

void BodyPostureView::vcKneeAngleValueChanged(int value){
    if(legSpeci_Type == 1 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT, value);
    if(legSpeci_Type == 2 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT, value);
}

void BodyPostureView::vcAnkleAngleValueChanged(int value){
    if(legSpeci_Type == 1 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT, value);
    if(legSpeci_Type == 2 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT, value);
}

void BodyPostureView::vcAnkleAngleSidewaysValueChanged(int value){
    if(legSpeci_Type == 1 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_LEFT, value);
    if(legSpeci_Type == 2 || legSpeci_Type == 3)
        values.insert(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_RIGHT, value);
}

void BodyPostureView::vcHeadTiltValueChanged(int value){
    values.insert(DBConstants::COL_BODY_POSTURE_HEAD_TILT, value);
}

void BodyPostureView::vcHeadTiltSidewaysValueChanged(int value){
    values.insert(DBConstants::COL_BODY_POSTURE_HEAD_TILT_SIDEWAYS, value);
}

void BodyPostureView::vcHeadTwistValueChanged(int value){
    values.insert(DBConstants::COL_BODY_POSTURE_HEAD_TWIST, value);
}


//GETTER SETTER
/*QSqlRecord BodyPostureView::getRecord() const{
    return this->record;
}*/

void BodyPostureView::setBodyPostureView(QHash<QString, QVariant> values){
    vcTrunkTilt->setValue(values.value(DBConstants::COL_BODY_POSTURE_TRUNK_TILT).toInt());
    vcTrunkSidewaysTilt->setValue(values.value(DBConstants::COL_BODY_POSTURE_TRUNK_TILT_SIDEWAYS).toInt());
    vcTrunkTwist->setValue(values.value(DBConstants::COL_BODY_POSTURE_TRUNK_TWIST).toInt());

    vcUpperArmAngle->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT).toInt());
    vcForearmAngle->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT).toInt());
    vcUpperArmTwist->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_UPPER_ARM_TWIST_LEFT : DBConstants::COL_BODY_POSTURE_UPPER_ARM_TWIST_RIGHT).toInt());
    vcForearmTwist->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_FOREARM_TWIST_LEFT : DBConstants::COL_BODY_POSTURE_FOREARM_TWIST_RIGHT).toInt());
    vcArmOpening->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_ARM_OPENING_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_ARM_OPENING_ANGLE_RIGHT).toInt());
    vcWristAngle->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_RIGHT).toInt());
    vcWristAngleSideways->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_LEFT : DBConstants::COL_BODY_POSTURE_WRIST_ANGLE_SIDEWAYS_RIGHT).toInt());
    vcWristMovement->setValue(values.value((armSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_WRIST_MOVEMENT_LEFT : DBConstants::COL_BODY_POSTURE_WRIST_MOVEMENT_RIGHT).toInt());

    vcHipAngle->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT).toInt());
    vcHipAngleSideways->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_LEFT : DBConstants::COL_BODY_POSTURE_HIP_ANGLE_SIDEWAYS_RIGHT).toInt());
    vcHipTwist->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_HIP_TWIST_LEFT : DBConstants::COL_BODY_POSTURE_HIP_TWIST_RIGHT).toInt());
    vcKneeAngle->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT).toInt());
    vcAnkleAngle->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT : DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT).toInt());
    vcAnkleAngleSideways->setValue(values.value((legSpeci_Type == AVType::LEFT) ? DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_LEFT : DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_SIDEWAYS_RIGHT).toInt());

    vcHeadTilt->setValue(values.value(DBConstants::COL_BODY_POSTURE_HEAD_TILT).toInt());;
    vcHeadTiltSideways->setValue(values.value(DBConstants::COL_BODY_POSTURE_HEAD_TILT_SIDEWAYS).toInt());;
    vcHeadTwist->setValue(values.value(DBConstants::COL_BODY_POSTURE_HEAD_TWIST).toInt());;
}

void BodyPostureView::onLeaving(){
    emit saveBodyPostureView(values);
}

