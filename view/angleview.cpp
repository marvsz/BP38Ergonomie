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
    varSpeciArms->addSpezification(new QString("Beide")); varSpeciArms->addSpezification(new QString("Links")); varSpeciArms->addSpezification(new QString("Rechts"));
    varSpeciLegs = new VariantSpecification();
    varSpeciLegs->addSpezification(new QString("Beide")); varSpeciLegs->addSpezification(new QString("Links")); varSpeciLegs->addSpezification(new QString("Rechts"));

    torsoFlextion = new Variant(new QString("Beugung"), new SubVariant(new QString("Beugungswinkel"), -60, 120, angleTorsoFlextion, new QString(":/Icons/TorsoFlextion/TorsoFlextion_")));
    torsoTilt = new Variant(new QString("Seitl. Neigung"), new SubVariant(new QString("Seitliche Neigung"), 0, 90, angleTorsoTilt, new QString(":/Icons/TorsoTilt/TorsoTilt_")));
    torsoRotation = new Variant(new QString("Drehung"), new SubVariant(new QString("Drehung"), 0, 90, angleTorsoRotation, new QString(":/Icons/TorsoRotation/TorsoRotation_")));

    headTilt = new Variant(new QString("Neigung"), new SubVariant(new QString("Kopfneigung"), -90, 90, angleHeadTilt, new QString(":/Icons/HeadTilt/HeadTilt_")));
    headRotation = new Variant(new QString("Drehung"), new SubVariant(new QString("Kopfdrehung"), 0, 45, angleHeadRotation, new QString(":/Icons/HeadRotation/HeadRotation_")));
    headSidewiseTilt = new Variant(new QString("Seitl. Neigung"), new SubVariant(new QString("Kopfneigung"), 0, 45, angleHeadSidewiseTilt, new QString(":/Icons/HeadSidewiseTilt/HeadSidewiseTilt_")));

    armsPosition = new Variant(new QString("Stellung"), new SubVariant(new QString("Oberarmwinkel"), -90, 180, angleUpperArmPosition, new QString(":/Icons/UpperArmPosition/UpperArmPosition_")));
    armsUnderPosition = new SubVariant(new QString("Unterarmwinkel"), 0, 180, angleUnderArmPosition, new QString(":/Icons/UnderArmPosition/UnderArmPosition_"));
    armsRotation = new Variant(new QString("Drehung"), new SubVariant(new QString("Oberarmdrehungswinkel"), -45, 90, angleUpperArmRotation, new QString(":/Icons/UpperArmRotation/UpperArmRotation_")));
    armsUnderRotation = new SubVariant(new QString("Underarmdrehungswinkel"), -90, 90, angleUnderArmRotation, new QString(":/icons/UnderArmRotation/UnderArmRotation_"));
    armsOpening = new Variant(new QString("Öffnung"), new SubVariant(new QString("Oberarmöffnungswinkel"), -90, 90, angleUpperArmOpening, new QString(":/Icons/UpperArmOpening/UpperArmOpening_")));
    armsWrist = new Variant(new QString("Handgelenk"), new SubVariant(new QString("Handgelenkbewegung"), true, textsWrist, new QString(":/icons/ArmsWrist/ArmsWrist_")));

    legAngle = new Variant(new QString("Beinwinkel"), new SubVariant(new QString("Hüftwinkel"), 45, 180, angleLegHip, new QString(":/Icons/LegHip/LegHip_")));
    legKnee = new SubVariant(new QString("Kniewinkel"), 0, 180, angleLegKnee, new QString(":/Icons/LegKnee/LegKnee_"));
    legAnkle = new SubVariant(new QString("Sprunggelenkwinkel"), 90, 180, angleLegAnkle, new QString(":/Icons/LegAnkle/LegAnkle_"));
    legPosition = new Variant(new QString("Haltung"), new SubVariant(new QString("Beinhaltung:"), false, textsLegPosition, new QString(":/icons/LegPosition/LegPosition_")));

    acTorso = new AngleControl(new QString("Rumpf"), torsoFlextion, NULL, categoryScrollArea);
    acTorso->addVariant(torsoTilt);
    acTorso->addVariant(torsoRotation);

    acArms = new AngleControl(new QString("Arme"), armsPosition, varSpeciArms, categoryScrollArea);
    armsPosition->addSubVariant(armsUnderPosition);
    acArms->addVariant(armsRotation);
    armsRotation->addSubVariant(armsUnderRotation);
    acArms->addVariant(armsOpening);
    acArms->addVariant(armsWrist);


    acLegs = new AngleControl(new QString("Beine"), legPosition, varSpeciLegs, categoryScrollArea);
    legAngle->addSubVariant(legKnee);
    legAngle->addSubVariant(legAnkle);
    acLegs->addVariant(legAngle);

    acHead = new AngleControl(new QString("Kopf"), headRotation, NULL, categoryScrollArea);
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
