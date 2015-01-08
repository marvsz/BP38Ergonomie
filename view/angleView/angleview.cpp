#include "angleview.h"
#include "flickcharm.h"
#include <QPushButton>
#include <QGroupBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QResizeEvent>
#include <QScroller>


AngleView::AngleView(QWidget *parent) :
    QMainWindow(parent)
{
    main = new QWidget();

    QVBoxLayout *categoryLayout = new QVBoxLayout;
    QScrollArea *categoryScrollArea = new QScrollArea;

    varSpeciArms = new VariantSpecification();
    varSpeciArms->addSpezification(new QString(tr("both"))); varSpeciArms->addSpezification(new QString(tr("left"))); varSpeciArms->addSpezification(new QString(tr("right")));
    varSpeciLegs = new VariantSpecification();
    varSpeciLegs->addSpezification(new QString(tr("both"))); varSpeciLegs->addSpezification(new QString(tr("left"))); varSpeciLegs->addSpezification(new QString(tr("right")));

    torsoFlextion = new Variant(new QString(tr("flexion")), new SubVariant(new QString(tr("flexion angle")), -60, 120, angleTorsoFlextion, new QString(tr("torso_Flexion_Icon"))));
    torsoTilt = new Variant(new QString(tr("sidewise tilt")), new SubVariant(new QString(tr("sidewise tilt")), 0, 90, angleTorsoTilt, new QString(tr("torso_Tilt_Icon"))));
    torsoRotation = new Variant(new QString(tr("rotation")), new SubVariant(new QString(tr("rotation")), 0, 90, angleTorsoRotation, new QString(tr("torso_Rotation_Icon"))));

    headTilt = new Variant(new QString(tr("inclination")), new SubVariant(new QString(tr("head inclination")), -90, 90, angleHeadTilt, new QString(tr("head_Tilt_Icon"))));
    headRotation = new Variant(new QString(tr("rotation")), new SubVariant(new QString(tr("head rotation")), 0, 45, angleHeadRotation, new QString(tr("head_Rotation_Icon"))));
    headSidewiseTilt = new Variant(new QString(tr("sidewise inclination")), new SubVariant(new QString(tr("head inclination")), 0, 45, angleHeadSidewiseTilt, new QString(tr("head_Sidewise_Tilt_Icon"))));

    armsPosition = new Variant(new QString(tr("stance")), new SubVariant(new QString(tr("upper arm angle")), -90, 180, angleUpperArmPosition, new QString(tr("upper_Arm_Position_Icon"))));
    armsUnderPosition = new SubVariant(new QString(tr("forearm angle")), 0, 180, angleUnderArmPosition, new QString(tr("forearm_Position_Icon")));
    armsRotation = new Variant(new QString(tr("rotation")), new SubVariant(new QString(tr("upper arm rotation angle")), -45, 90, angleUpperArmRotation, new QString(tr("Upper_Arm_Rotation_Icon"))));
    armsUnderRotation = new SubVariant(new QString(tr("forearm rotation angle")), -90, 90, angleUnderArmRotation, new QString(tr("forearm_Rotation_Icon")));
    armsOpening = new Variant(new QString(tr("opening")), new SubVariant(new QString(tr("upper arm opening angle")), -90, 90, angleUpperArmOpening, new QString(tr("upper_Arm_Opening_Icon"))));
    armsWrist = new Variant(new QString(tr("wrist")), new SubVariant(new QString(tr("wrist movement")), true, textsWrist, new QString(tr("wrist_Movement_Icon"))));

    legAngle = new Variant(new QString(tr("leg angle")), new SubVariant(new QString(tr("hip angle")), 45, 180, angleLegHip, new QString(tr("leg_Hip_Icon"))));
    legKnee = new SubVariant(new QString(tr("knee angle")), 0, 180, angleLegKnee, new QString(tr("leg_Knee_Icon")));
    legAnkle = new SubVariant(new QString(tr("ankle angle")), 90, 180, angleLegAnkle, new QString(tr("leg_Ankle_Icon")));
    legPosition = new Variant(new QString(tr("posture")), new SubVariant(new QString(tr("leg posture:")), false, textsLegPosition, new QString(tr("leg_Position_Icon"))));

    acTorso = new AngleControl(new QString(tr("torso")), torsoFlextion, NULL, categoryScrollArea);
    acTorso->addVariant(torsoTilt);
    acTorso->addVariant(torsoRotation);

    acArms = new AngleControl(new QString(tr("arms")), armsPosition, varSpeciArms, categoryScrollArea);
    armsPosition->addSubVariant(armsUnderPosition);
    acArms->addVariant(armsRotation);
    armsRotation->addSubVariant(armsUnderRotation);
    acArms->addVariant(armsOpening);
    acArms->addVariant(armsWrist);


    acLegs = new AngleControl(new QString(tr("legs")), legPosition, varSpeciLegs, categoryScrollArea);
    legAngle->addSubVariant(legKnee);
    legAngle->addSubVariant(legAnkle);
    acLegs->addVariant(legAngle);

    acHead = new AngleControl(new QString(tr("head")), headRotation, NULL, categoryScrollArea);
    acHead->addVariant(headTilt);
    acHead->addVariant(headSidewiseTilt);

    categoryLayout->addWidget(acTorso);
    categoryLayout->addWidget(acArms);
    categoryLayout->addWidget(acLegs);
    categoryLayout->addWidget(acHead);
    main->setLayout(categoryLayout);

    categoryScrollArea->setWidget(main);
    categoryScrollArea->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(categoryScrollArea);
    this->setCentralWidget(categoryScrollArea);

    connect(acTorso, SIGNAL(contentIsShown()), this, SLOT(showTorso()));
    connect(acArms, SIGNAL(contentIsShown()), this, SLOT(showArms()));
    connect(acLegs, SIGNAL(contentIsShown()), this, SLOT(showLegs()));
    connect(acHead, SIGNAL(contentIsShown()), this, SLOT(showHead()));
    selectAV();
}


//public slots

void AngleView::selectLeftAV(){
    showArms();
    acArms->selectSpecification(1);
    acLegs->selectSpecification(1);
}

void AngleView::selectRightAV(){
    showArms();
    acArms->selectSpecification(2);
    acLegs->selectSpecification(2);
}

void AngleView::selectAV(){
    showTorso();
    acArms->selectSpecification(0);
    acLegs->selectSpecification(0);
}

void AngleView::showTorso(){
    acTorso->showContent();
    acArms->hideContent();
    acLegs->hideContent();
    acHead->hideContent();
}
void AngleView::showArms(){
    acTorso->hideContent();
    acArms->showContent();
    acLegs->hideContent();
    acHead->hideContent();
}

void AngleView::showLegs(){
    acTorso->hideContent();
    acArms->hideContent();
    acLegs->showContent();
    acHead->hideContent();
}

void AngleView::showHead(){
    acTorso->hideContent();
    acArms->hideContent();
    acLegs->hideContent();
    acHead->showContent();
}

