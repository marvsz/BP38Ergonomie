#include "bodymeasurementview.h"
#include "separator.h"

BodyMeasurementView::BodyMeasurementView(QWidget *parent) : SimpleNavigateableWidget(tr("Body Measurements"), parent),
    vcHeadNeck(new ValueControl(VALUE)),
    vcThighLength(new ValueControl(VALUE)),
    vcTibialHeight(new ValueControl(VALUE)),
    vcFootLength(new ValueControl(VALUE)),

    lblUpperBody(new QLabel(tr("Upper part of the body"))),
    lblLowerBody(new QLabel(tr("Lower part of the body"))),
    lblShoulderWidth(new QLabel(tr("Shoulder width:"))),
    lblShoulderBiacromial(new QLabel(tr("Shoulder width biacromial:"))),
    lblShoulderBideltoid(new QLabel(tr("Shoulder width bideltoid:"))),
    lblUpperArmLength(new QLabel(tr("Upper arme lenght:"))),
    lblForearmLength(new QLabel(tr("Forearm length:"))),
    lblHandLength(new QLabel(tr("Hand length:"))),
    lblTorsoHeight(new QLabel(tr("Torso height:"))),

    head(new QWidget()),
    torso(new QWidget()),
    legs(new QWidget()),
    btnHead(new SelectableValueButton(0, 0, this)),
    btnTorso(new SelectableValueButton(1, 1, this)),
    btnArmLeft(new SelectableValueButton(2, 2, this)),
    btnArmRight(new SelectableValueButton(2, 2, this)),
    btnLegs(new SelectableValueButton(3, 2, this))
{
    lblUpperBody->setObjectName("lblHeader");
    lblLowerBody->setObjectName("lblHeader");

    btnHead->setFixedSize(250, 100);
    btnHead->setObjectName("headIcon");

    btnArmLeft->setFixedSize(50, 300);
    btnArmLeft->setObjectName("armLeftIcon");

    btnArmRight->setFixedSize(50, 300);
    btnArmRight->setObjectName("armRightIcon");

    btnTorso->setFixedSize(150, 300);
    btnTorso->setObjectName("torsoIcon");

    btnLegs->setFixedSize(250, 300);
    btnLegs->setObjectName("legsIcon");


    connect(btnHead, SIGNAL(clicked()), this, SLOT(btnHeadClicked()));
    connect(btnTorso, SIGNAL(clicked()), this, SLOT(btnTorsoClicked()));
    connect(btnArmLeft, SIGNAL(clicked()), this, SLOT(btnArmClicked()));
    connect(btnArmRight, SIGNAL(clicked()), this, SLOT(btnArmClicked()));
    connect(btnLegs, SIGNAL(clicked()), this, SLOT(btnLegsClicked()));

    vcHeadNeck->setText(tr("Head neck height"));
    vcHeadNeck->setValues(20, 50, QVector<int>()<<30<<40, QString(""));
    vcHeadNeck->setValue(30);

    vcThighLength->setText(tr("Thigh Length"));
    vcThighLength->setValues(30, 60, QVector<int>()<<40<<50, QString(""));
    vcThighLength->setValue(45);

    vcTibialHeight->setText(tr("Tibial height"));
    vcTibialHeight->setValues(30, 60, QVector<int>()<<40<<50, QString(""));
    vcTibialHeight->setValue(45);

    vcFootLength->setText(tr("Foot Length"));
    vcFootLength->setValues(15, 35, QVector<int>()<<20<<30, QString(""));
    vcFootLength->setValue(25);


    QGridLayout *headLayout = new QGridLayout;
    headLayout->addWidget(vcHeadNeck, 0, 0, 1, 1, Qt::AlignLeft);
    head->setLayout(headLayout);
    head->hide();

    QGridLayout *torsoLayout = new QGridLayout;
    torsoLayout->addWidget(lblUpperBody, 0, 0, 1, 1, Qt::AlignLeft);
    torsoLayout->addWidget(lblShoulderWidth, 1, 0, 1, 1, Qt::AlignLeft);
    torsoLayout->addWidget(lblShoulderBiacromial, 2, 0, 1, 1, Qt::AlignLeft);
    torsoLayout->addWidget(lblUpperArmLength, 3, 0, 1, 1, Qt::AlignLeft);
    torsoLayout->addWidget(lblForearmLength, 4, 0, 1, 1, Qt::AlignLeft);
    torsoLayout->addWidget(lblHandLength, 5, 0, 1, 1, Qt::AlignLeft);
    torso->setLayout(torsoLayout);
    torso->hide();

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
    rightLayout->addWidget(legs, 2, 0, 1, 2, 0);
    rightLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 0, 1, 2, 0);

    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->addWidget(btnHead, 0, 0, 1, 3, Qt::AlignBottom);
    leftLayout->addWidget(btnArmLeft, 1, 0, 1, 1, 0);
    leftLayout->addWidget(btnTorso, 1, 1, 1, 1, 0);
    leftLayout->addWidget(btnArmRight, 1, 2, 1, 1, 0);
    leftLayout->addWidget(btnLegs, 2, 0, 1, 3, Qt::AlignTop);

    QHBoxLayout *splitLayout = new QHBoxLayout;
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addLayout(leftLayout);
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addWidget(new Separator(Qt::Vertical, 3, 0));
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addLayout(rightLayout);
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    setLayout(splitLayout);
}

void BodyMeasurementView::btnHeadClicked(){
    head->show();
    torso->hide();
    //arms->hide();
    legs->hide();
    btnHead->setSelected(true);
    btnArmLeft->setSelected(false);
    btnArmRight->setSelected(false);
    btnTorso->setSelected(false);
    btnLegs->setSelected(false);
}

void BodyMeasurementView::btnTorsoClicked(){
    head->hide();
    torso->show();
    //arms->hide();
    legs->hide();
    btnHead->setSelected(false);
    btnArmLeft->setSelected(false);
    btnArmRight->setSelected(false);
    btnTorso->setSelected(true);
    btnLegs->setSelected(false);
}

void BodyMeasurementView::btnLegsClicked(){
    head->hide();
    torso->hide();
    //arms->hide();
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
    //arms->show();
    btnHead->setSelected(false);
    btnTorso->setSelected(false);
    btnLegs->setSelected(false);
    btnArmLeft->setSelected(true);
    btnArmRight->setSelected(true);
}
