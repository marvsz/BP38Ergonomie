#include "bodymeasurementview.h"
#include "separator.h"

BodyMeasurementView::BodyMeasurementView(QWidget *parent) :
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
    btnLegs(new SelectableValueButton(2, 2, this)),
    btnBack(new QPushButton()),
    lblViewName(new QLabel(tr("Body Measurement"))),
    btnFeedback(new QPushButton())
{
    lblUpperBody->setObjectName("lblHeader");
    lblLowerBody->setObjectName("lblHeader");

    btnBack->setFixedSize(45, 45);
    btnBack->setObjectName("leftIcon");

    btnFeedback->setFixedSize(45, 45);
    btnFeedback->setObjectName("feedbackIcon");


    btnHead->setFixedSize(300, 100);
    btnHead->setStyleSheet("SelectableValueButton {border : none}");
    btnHead->setObjectName("headIcon");
    btnHead->setText("Head");
    btnTorso->setFixedSize(300, 300);
    btnTorso->setStyleSheet("SelectableValueButton {border : none}");
    btnTorso->setObjectName("torsoIcon");
    btnTorso->setText("Torso");
    btnLegs->setFixedSize(300, 300);
    btnLegs->setStyleSheet("SelectableValueButton {border : none}");
    btnLegs->setObjectName("legsIcon");
    btnLegs->setText("Legs");

    connect(btnBack, SIGNAL(clicked()), this, SIGNAL(back()));
    connect(btnHead, SIGNAL(clicked()), this, SLOT(btnHeadClicked()));
    connect(btnTorso, SIGNAL(clicked()), this, SLOT(btnTorsoClicked()));
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


    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(btnFeedback, 0, 2, 1, 1, Qt::AlignRight);

    QGridLayout *rightLayout = new QGridLayout;
    rightLayout->setContentsMargins(0,0,0,0);
    rightLayout->addWidget(head, 0, 0, 1, 2, 0);
    rightLayout->addWidget(torso, 1, 0, 1, 2, 0);
    rightLayout->addWidget(legs, 2, 0, 1, 2, 0);
    rightLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 0, 1, 2, 0);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(btnHead);
    leftLayout->addWidget(btnTorso);
    leftLayout->addWidget(btnLegs);
    leftLayout->setSpacing(0);

    QHBoxLayout *splitLayout = new QHBoxLayout;
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addLayout(leftLayout);
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addWidget(new Separator(Qt::Vertical, 3, 0));
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addLayout(rightLayout);
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addLayout(splitLayout);

    setLayout(mainLayout);
}

void BodyMeasurementView::btnHeadClicked(){
    head->show();
    torso->hide();
    legs->hide();
    btnHead->setSelected(true);
    btnTorso->setSelected(false);
    btnLegs->setSelected(false);
}

void BodyMeasurementView::btnTorsoClicked(){
    head->hide();
    torso->show();
    legs->hide();
    btnHead->setSelected(false);
    btnTorso->setSelected(true);
    btnLegs->setSelected(false);
}

void BodyMeasurementView::btnLegsClicked(){
    head->hide();
    torso->hide();
    legs->show();
    btnHead->setSelected(false);
    btnTorso->setSelected(false);
    btnLegs->setSelected(true);
}
