#include "mainwindow.h"
#include "owncon.h"
#include <QPushButton>
#include <QGroupBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QResizeEvent>
#include <QScroller>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    main = new QWidget(this);
    control = new QWidget();
    timer = new QWidget();
    QVBoxLayout *categoryLayout = new QVBoxLayout;
    QScrollArea *categoryScrollArea = new QScrollArea;

    QGridLayout *mainLayout = new QGridLayout;


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

    angleLegHip = new QVector<int>();
    (*angleLegHip)<<45<<90<<135<<180;
    angleLegKnee = new QVector<int>();
    (*angleLegKnee)<<0<<45<<90<<135<<180;
    angleLegAnkle = new QVector<int>();
    (*angleLegAnkle)<<90<<135<<180;

    varSpeciArms = new VariantSpecification();
    varSpeciArms->addSpezification(new QString("Beide")); varSpeciArms->addSpezification(new QString("Links")); varSpeciArms->addSpezification(new QString("Rechts"));
    varSpeciLegs = new VariantSpecification();
    varSpeciLegs->addSpezification(new QString("Beide")); varSpeciLegs->addSpezification(new QString("Links")); varSpeciLegs->addSpezification(new QString("Rechts"));

    torsoFlextion = new Variant(new QString("Beugung"), new SubVariant(new QString("Beugungswinkel [°]:"), -60, 120, angleTorsoFlextion, new QString(":/Icons/TorsoFlextion/TorsoFlextion_"), VALUE_CONTROL));
    torsoTilt = new Variant(new QString("Seitl. Neigung"), new SubVariant(new QString("Seitliche Neigung [°]:"), 0, 90, angleTorsoTilt, new QString(":/Icons/TorsoTilt/TorsoTilt_"), VALUE_CONTROL));
    torsoRotation = new Variant(new QString("Drehung"), new SubVariant(new QString("Drehung [°]:"), 0, 90, angleTorsoRotation, new QString(":/Icons/TorsoRotation/TorsoRotation_"), VALUE_CONTROL));

    headTilt = new Variant(new QString("Neigung"), new SubVariant(new QString("Kopfneigung [°]:"), -90, 90, angleHeadTilt, new QString(":/Icons/HeadTilt/HeadTilt_"), VALUE_CONTROL));
    headRotation = new Variant(new QString("Drehung"), new SubVariant(new QString("Kopfdrehung [°]:"), 0, 45, angleHeadRotation, new QString(":/Icons/HeadRotation/HeadRotation_"), VALUE_CONTROL));
    headSidewiseTilt = new Variant(new QString("Seitl. Neigung"), new SubVariant(new QString("Kopfneigung [°]:"), 0, 45, angleHeadSidewiseTilt, new QString(":/Icons/HeadSidewiseTilt/HeadSidewiseTilt_"), VALUE_CONTROL));

    armsPosition = new Variant(new QString("Stellung"), new SubVariant(new QString("Oberarmwinkel [°]:"), -90, 180, angleUpperArmPosition, new QString(":/Icons/UpperArmPosition/UpperArmPosition_"), VALUE_CONTROL));
    armsUnderPosition = new SubVariant(new QString("Unterarmwinkel [°]:"), 0, 180, angleUnderArmPosition, new QString(":/Icons/UnderArmPosition/UnderArmPosition_"), VALUE_CONTROL);
    armsRotation = new Variant(new QString("Drehung"), new SubVariant(new QString("Oberarmdrehungswinkel [°]:"), -45, 90, angleUpperArmRotation, new QString(":/Icons/UpperArmRotation/UpperArmRotation_"), VALUE_CONTROL));
    armsUnderRotation = new SubVariant(new QString("Underarmdrehungswinkel [°]:"), -90, 90, angleUnderArmRotation, new QString(":/Icons/UnderArmRotation/UnderArmRotation_"), VALUE_CONTROL);
    armsOpening = new Variant(new QString("Öffnung"), new SubVariant(new QString("Oberarmöffnungswinkel [°]:"), -90, 90, angleUpperArmOpening, new QString(":/Icons/UpperArmOpening/UpperArmOpening_"), VALUE_CONTROL));

    legAngle = new Variant(new QString("Beinwinkel"), new SubVariant(new QString("Hüftwinkel [°]:"), 45, 180, angleLegHip, new QString(":/Icons/LegHip/LegHip_"), VALUE_CONTROL));
    legKnee = new SubVariant(new QString("Kniewinkel [°]:"), 0, 180, angleLegKnee, new QString(":/Icons/LegKnee/LegKnee_"), VALUE_CONTROL);
    legAnkle = new SubVariant(new QString("Sprunggelenkwinkel [°]:"), 90, 180, angleLegAnkle, new QString(":/Icons/LegAnkle/LegAnkle_"), VALUE_CONTROL);

    ac1 = new AngleControl(new QString("Rumpf"), torsoFlextion, NULL, categoryScrollArea);
    ac1->addVariant(torsoTilt);
    ac1->addVariant(torsoRotation);

    ac2 = new AngleControl(new QString("Arme"), armsPosition, varSpeciArms, categoryScrollArea);
    armsPosition->addSubVariant(armsUnderPosition);
    ac2->addVariant(armsRotation);
    armsRotation->addSubVariant(armsUnderRotation);
    ac2->addVariant(armsOpening);


    ac4 = new AngleControl(new QString("Beine"), legAngle, varSpeciLegs, categoryScrollArea);
    legAngle->addSubVariant(legKnee);
    legAngle->addSubVariant(legAnkle);
    ac4->selectVariant(0);

    ac3 = new AngleControl(new QString("Kopf"), headRotation, NULL, categoryScrollArea);
    ac3->addVariant(headTilt);
    ac3->addVariant(headSidewiseTilt);

    btnBack = new QPushButton("< Zurück");
    btnBack->setFixedSize(120,45);
    lblViewName = new QLabel("Körperhaltung");

    stopWatch = new StopWatch(timer);

    categoryLayout->addWidget(ac1);
    categoryLayout->addWidget(ac2);
    categoryLayout->addWidget(ac4);
    categoryLayout->addWidget(ac3);
    control->setLayout(categoryLayout);

    categoryScrollArea->setWidget(control);
    categoryScrollArea->setWidgetResizable(true);
    QScroller::grabGesture(categoryScrollArea->viewport(), QScroller::LeftMouseButtonGesture);

    mainLayout->addWidget(btnBack, 0, 0, 1, 1, 0);
    mainLayout->addWidget(lblViewName, 0, 1, 1, 1, 0);
    mainLayout->addWidget(categoryScrollArea, 1, 0, 1, 2, 0);
    mainLayout->addWidget(stopWatch, 2, 0, 1, 2, 0);
    mainLayout->setAlignment(lblViewName, Qt::AlignCenter);

    main->setLayout(mainLayout);

    this->setCentralWidget(main);

    connect(btnBack, SIGNAL(clicked()) , SLOT(openMenuView()));
}

MainWindow::~MainWindow()
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

    void MainWindow::openMenuView(){
        emit menuViewSelected();
    }
