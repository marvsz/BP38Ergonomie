#include "bodymeasurementview.h"
#include "separator.h"
#include <QScrollArea>
#include "flickcharm.h"

BodyMeasurementView::BodyMeasurementView(QWidget *parent) : SimpleNavigateableWidget(tr("Body Measurements"), parent),
    vcHeadNeck(new ValueControl(VALUE)),
    vcThighLength(new ValueControl(VALUE)),
    vcTibialHeight(new ValueControl(VALUE)),
    vcFootLength(new ValueControl(VALUE)),
    vcShoulderWidth(new ValueControl(VALUE)),
    vcShoulderBiacromial(new ValueControl(VALUE)),
    vcShoulderBideltoid(new ValueControl(VALUE)),
    vcUpperArmLength(new ValueControl(VALUE)),
    vcForearmLength(new ValueControl(VALUE)),
    vcHandLength(new ValueControl(VALUE)),
    vcTorsoHeight(new ValueControl(VALUE)),
    lblHeadNeck(new QLabel(tr("Head and neck:"))),
    lblUpperBody(new QLabel(tr("Upper part of the body:"))),
    lblArmsHands(new QLabel(tr("Arms and hands:"))),
    lblLowerBody(new QLabel(tr("Lower part of the body:"))),
    lblSelectBodyPart(new QLabel(tr("Tap to select body part:"))),
    head(new QWidget()),
    torso(new QWidget()),
    arms(new QWidget()),
    legs(new QWidget()),
    btnHead(new SelectableValueButton(0, 0, this)),
    btnTorso(new SelectableValueButton(1, 1, this)),
    btnArmLeft(new SelectableValueButton(2, 2, this)),
    btnArmRight(new SelectableValueButton(2, 2, this)),
    btnLegs(new SelectableValueButton(3, 2, this))
{
    lblHeadNeck->setObjectName("lblHeader");
    lblUpperBody->setObjectName("lblHeader");
    lblArmsHands->setObjectName("lblHeader");
    lblLowerBody->setObjectName("lblHeader");
    lblSelectBodyPart->setObjectName("lblHeader");

    btnHead->setFixedSize(200, 80);
    btnHead->setObjectName("headIcon");

    btnArmLeft->setFixedSize(40, 240);
    btnArmLeft->setObjectName("armLeftIcon");

    btnArmRight->setFixedSize(40, 240);
    btnArmRight->setObjectName("armRightIcon");

    btnTorso->setFixedSize(120, 240);
    btnTorso->setObjectName("torsoIcon");

    btnLegs->setFixedSize(200, 240);
    btnLegs->setObjectName("legsIcon");


    connect(btnHead, SIGNAL(clicked()), this, SLOT(btnHeadClicked()));
    connect(btnTorso, SIGNAL(clicked()), this, SLOT(btnTorsoClicked()));
    connect(btnArmLeft, SIGNAL(clicked()), this, SLOT(btnArmClicked()));
    connect(btnArmRight, SIGNAL(clicked()), this, SLOT(btnArmClicked()));
    connect(btnLegs, SIGNAL(clicked()), this, SLOT(btnLegsClicked()));

    vcHeadNeck->setText(tr("Head neck height [mm]"));
    vcHeadNeck->setValues(200, 500, QVector<int>()<<250<<300<<350<<400<<450, QString(""));
    vcHeadNeck->setValue(300);

    vcShoulderWidth->setText(tr("Shoulder width [mm]"));
    vcShoulderWidth->setValues(350, 550, QVector<int>()<<400<<420<<440<<460<<480, QString(""));
    vcShoulderWidth->setValue(442);
    vcShoulderBiacromial->setText(tr("Shoulder biacromial [mm]"));
    vcShoulderBiacromial->setValues(300, 500, QVector<int>()<<350<<375<<400<<425<<450, QString(""));
    vcShoulderBiacromial->setValue(405);
    vcShoulderBideltoid->setText(tr("Shoulder bideltoid [mm]"));
    vcShoulderBideltoid->setValues(400, 600, QVector<int>()<<450<<475<<500<<525<<550, QString(""));
    vcShoulderBideltoid->setValue(480);
    vcTorsoHeight->setText("Torso Height [mm]");
    vcTorsoHeight->setValues(500, 800, QVector<int>()<<550<<600<<650<<700<<750, QString(""));
    vcTorsoHeight->setValue(620);

    vcUpperArmLength->setText(tr("Upper arm length [mm]"));
    vcUpperArmLength->setValues(200, 500, QVector<int>()<<250<<300<<350<<400<<450, QString(""));
    vcUpperArmLength->setValue(365);
    vcForearmLength->setText(tr("Forearm length [mm]"));
    vcForearmLength->setValues(200, 500, QVector<int>()<<250<<300<<350<<400<<450, QString(""));
    vcForearmLength->setValue(286);
    vcHandLength->setText(tr("Hand length [mm]"));
    vcHandLength->setValues(50, 80, QVector<int>()<<55<<60<<65<<70<<75, QString(""));
    vcHandLength->setValue(64);

    vcThighLength->setText(tr("Thigh Length [mm]"));
    vcThighLength->setValues(300, 600, QVector<int>()<<350<<400<<450<<500<<550, QString(""));
    vcThighLength->setValue(460);
    vcTibialHeight->setText(tr("Tibial height [mm]"));
    vcTibialHeight->setValues(300, 600, QVector<int>()<<350<<400<<450<<500<<550, QString(""));
    vcTibialHeight->setValue(460);
    vcFootLength->setText(tr("Foot Length [mm]"));
    vcFootLength->setValues(150, 350, QVector<int>()<<150<<200<<250<<300<<350, QString(""));
    vcFootLength->setValue(265);


    QGridLayout *headLayout = new QGridLayout;
    headLayout->addWidget(lblHeadNeck, 0, 0, 1, 1, Qt::AlignLeft);
    headLayout->addWidget(vcHeadNeck, 1, 0, 1, 1, Qt::AlignLeft);
    head->setLayout(headLayout);

    btnHead->setSelected(true);

    QGridLayout *torsoLayout = new QGridLayout;
    torsoLayout->addWidget(lblUpperBody, 0, 0, 1, 1, Qt::AlignLeft);
    torsoLayout->addWidget(vcShoulderWidth, 1, 0, 1, 1, Qt::AlignLeft);
    torsoLayout->addWidget(vcShoulderBiacromial, 2, 0, 1, 1, Qt::AlignLeft);
    torsoLayout->addWidget(vcTorsoHeight, 3, 0, 1, 1, Qt::AlignLeft);
    torso->setLayout(torsoLayout);
    torso->hide();

    QGridLayout *armsLayout = new QGridLayout;
    armsLayout->addWidget(lblArmsHands, 0, 0, 1, 1, Qt::AlignLeft);
    armsLayout->addWidget(vcUpperArmLength, 1, 0, 1, 1, Qt::AlignLeft);
    armsLayout->addWidget(vcForearmLength, 2, 0, 1, 1, Qt::AlignLeft);
    armsLayout->addWidget(vcHandLength, 3, 0, 1, 1, Qt::AlignLeft);
    arms->setLayout(armsLayout);
    arms->hide();

    QGridLayout *legsLayout = new QGridLayout;
    legsLayout->addWidget(lblLowerBody, 0, 0, 1, 1, Qt::AlignLeft);
    legsLayout->addWidget(vcThighLength, 1, 0, 1, 1, Qt::AlignLeft);
    legsLayout->addWidget(vcTibialHeight, 2, 0, 1, 1, Qt::AlignLeft);
    legsLayout->addWidget(vcFootLength, 3, 0, 1, 1, Qt::AlignLeft);
    legs->setLayout(legsLayout);
    legs->hide();

    QGridLayout *rightLayout = new QGridLayout;
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->addWidget(head, 0, 0, 1, 2, 0);
    rightLayout->addWidget(torso, 1, 0, 1, 2, 0);
    rightLayout->addWidget(arms, 2, 0, 1, 2, 0);
    rightLayout->addWidget(legs, 3, 0, 1, 2, 0);
    rightLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 4, 0, 1, 2, 0);

    QWidget *rightContent = new QWidget();
    rightContent->setLayout(rightLayout);

    QScrollArea *saRightLayout = new QScrollArea();
    saRightLayout->setMinimumWidth(800);
    saRightLayout->setWidget(rightContent);
    saRightLayout->setWidgetResizable(true);
    FlickCharm *flick = new FlickCharm();
    flick->activateOn(saRightLayout);

    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->addWidget(lblSelectBodyPart, 0, 0, 1, 3, Qt::AlignLeft);
    leftLayout->addItem(new QSpacerItem(0, 30, QSizePolicy::Fixed, QSizePolicy::Fixed), 1, 0, 1, 3, 0);
    leftLayout->addWidget(btnHead, 2, 0, 1, 3, Qt::AlignBottom);
    leftLayout->addWidget(btnArmLeft, 3, 0, 1, 1, 0);
    leftLayout->addWidget(btnTorso, 3, 1, 1, 1, 0);
    leftLayout->addWidget(btnArmRight, 3, 2, 1, 1, 0);
    leftLayout->addWidget(btnLegs, 4, 0, 1, 3, Qt::AlignTop);
    leftLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 5, 0, 1, 3, 0);

    QHBoxLayout *splitLayout = new QHBoxLayout;
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addLayout(leftLayout);
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addWidget(new Separator(Qt::Vertical, 3, 0));
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addWidget(saRightLayout);
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    setLayout(splitLayout);
}

void BodyMeasurementView::btnHeadClicked(){
    torso->hide();
    arms->hide();
    legs->hide();
    head->show();
    btnHead->setSelected(true);
    btnArmLeft->setSelected(false);
    btnArmRight->setSelected(false);
    btnTorso->setSelected(false);
    btnLegs->setSelected(false);
}

void BodyMeasurementView::btnTorsoClicked(){
    head->hide();
    arms->hide();
    legs->hide();
    torso->show();
    btnHead->setSelected(false);
    btnArmLeft->setSelected(false);
    btnArmRight->setSelected(false);
    btnTorso->setSelected(true);
    btnLegs->setSelected(false);
}

void BodyMeasurementView::btnLegsClicked(){
    head->hide();
    torso->hide();
    arms->hide();
    legs->show();
    btnHead->setSelected(false);
    btnTorso->setSelected(false);
    btnArmLeft->setSelected(false);
    btnArmRight->setSelected(false);
    btnLegs->setSelected(true);
}

void BodyMeasurementView::btnArmClicked(){
    head->hide();
    torso->hide();
    legs->hide();
    arms->show();
    btnHead->setSelected(false);
    btnTorso->setSelected(false);
    btnLegs->setSelected(false);
    btnArmLeft->setSelected(true);
    btnArmRight->setSelected(true);
}
