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

    angleTorsoFlextion = new QVector<int>();
    (*angleTorsoFlextion)<<-45<<-20<<0<<20<<45<<90<<110;
    angleTorsoTilt = new QVector<int>();
    (*angleTorsoTilt)<<0<<20<<45<<60<<90;
    angleTorsoRotation = new QVector<int>();
    (*angleTorsoRotation)<<0<<20<<45<<60<<90;

    angleHeadTilt = new QVector<int>();
    (*angleHeadTilt)<<-90<<-45<<0<<45<<90;
    angleHeadRotation = new QVector<int>();
    (*angleHeadRotation)<<0<<20<<45;
    angleHeadSidewiseTilt = new QVector<int>();
    (*angleHeadSidewiseTilt)<<0<<20<<45;

    angleUpperArmPosition = new QVector<int>();
    (*angleUpperArmPosition)<<-90<<0<<45<<90<<135<<180;
    angleUnderArmPosition = new QVector<int>();
    (*angleUnderArmPosition)<<0<<45<<90<<135<<180;
    angleUpperArmRotation = new QVector<int>();
    (*angleUpperArmRotation)<<-45<<0<<45<<90;
    angleUnderArmRotation = new QVector<int>();
    (*angleUnderArmRotation)<<-90<<-45<<0<<45<<90;
    angleUpperArmOpening = new QVector<int>();
    (*angleUpperArmOpening)<<-90<<-45<<0<<45<<90;
    textsWrist = new QVector<QString*>();
    (*textsWrist)<<new QString("Plamarflexion")<<new QString("Dorsalextension")<<new QString("Ularabduktion")<<new QString("Radialabduktion");

    angleLegHip = new QVector<int>();
    (*angleLegHip)<<45<<90<<135<<180;
    angleLegKnee = new QVector<int>();
    (*angleLegKnee)<<0<<45<<90<<135<<180;
    angleLegAnkle = new QVector<int>();
    (*angleLegAnkle)<<90<<135<<180;
    textsLegPosition = new QVector<QString*>;
    (*textsLegPosition)<<new QString("stehend")<<new QString("sitzend")<<new QString("gehend")<<new QString("laufend")<<new QString("kniend&&hockend")<<new QString("liegend")<<new QString("kletternd");

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
    armsUnderRotation = new SubVariant(new QString("Underarmdrehungswinkel"), -90, 90, angleUnderArmRotation, new QString(":/Icons/UnderArmRotation/UnderArmRotation_"));
    armsOpening = new Variant(new QString("Öffnung"), new SubVariant(new QString("Oberarmöffnungswinkel"), -90, 90, angleUpperArmOpening, new QString(":/Icons/UpperArmOpening/UpperArmOpening_")));
    armsWrist = new Variant(new QString("Handgelenk"), new SubVariant(new QString("Handgelenkbewegung"), textsWrist, new QString(":/Icons/ArmsWrist/ArmsWrist_")));

    legAngle = new Variant(new QString("Beinwinkel"), new SubVariant(new QString("Hüftwinkel"), 45, 180, angleLegHip, new QString(":/Icons/LegHip/LegHip_")));
    legKnee = new SubVariant(new QString("Kniewinkel"), 0, 180, angleLegKnee, new QString(":/Icons/LegKnee/LegKnee_"));
    legAnkle = new SubVariant(new QString("Sprunggelenkwinkel"), 90, 180, angleLegAnkle, new QString(":/Icons/LegAnkle/LegAnkle_"));
    legPosition = new Variant(new QString("Haltung"), new SubVariant(new QString("Beinhaltung:"), textsLegPosition, new QString(":/Icons/LegPosition/LegPosition_")));

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

    acTorso->showContent();
    acArms->hideContent();
    acLegs->hideContent();
    acHead->hideContent();
}

AngleView::~AngleView()
{
    delete headRotation;
    delete headSidewiseTilt;
    delete headTilt;
    delete torsoFlextion;
    delete torsoRotation;
    delete torsoTilt;
    delete armsUnderPosition;
    delete armsUnderRotation;
    delete armsRotation;
    delete armsPosition;
    delete armsOpening;
    delete legAnkle;
    delete legKnee;
    delete legAngle;
    delete varSpeciArms;
    delete varSpeciLegs;

}

