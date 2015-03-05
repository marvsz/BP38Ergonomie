#include "quickselectioncontrol.h"
#include "../../separator.h"

QuickSelectionControl::QuickSelectionControl(QWidget *parent) :
    QWidget(parent),
    mainContent(new QWidget()),
    btnName(new QPushButton()),
    verticalLayout(new QHBoxLayout()),
    qlpcQuickLegPosture(new QuickLegPostureControl),
    voscQuickArmPosture(new QuickArmPostureControl),
    voscQuickTrunkPosture(new VerticalOptionSelectionControl),
    mainLayout(new QVBoxLayout)
{
    //mainLayout->setContentsMargins(0,0,0,0);


    btnName->setMaximumWidth(150);
    connect(btnName, SIGNAL(clicked()), this, SLOT(btnNameClicked()));

    qlpcQuickLegPosture->setValues(QUICK_LEG_POSTURE_TEXTS,LEFT_RIGHT_TEXTS,tr("Quick Leg Posture"));
    //connect(qlpcQuickLegPosture, SIGNAL(selectionChanged(int,int)), this, SLOT(qlpcQuickLegPostureChanged(int,int)));
    //connect(qlpcQuickLegPosture, SIGNAL(specificationChanged(int)), this, SLOT(qlpcQuickLegPostureSpecificationChagend(int)));

    voscQuickArmPosture->setValues(QUICK_ARM_POSTURE_TEXTS,LEFT_RIGHT_TEXTS, tr("Quick Arm Posture"));
    //connect(voscQuickArmPosture, SIGNAL(selectionChanged(int,int)), this, SLOT(voscQuickArmPostureChanged(int,int)));
    //connect(voscQuickArmPosture, SIGNAL(specificationChanged(int)), this, SLOT(voscQuickArmPostureSpecificationChanged(int)));

    voscQuickTrunkPosture->setValues(QUICK_TRUNK_POSTURE_TEXTS, tr("Quick Trunk Posture") );
    //connect(voscQuickTrunkPosture, SIGNAL(selectionChanged(int)), this, SLOT(voscQuickTrunkPostureChanged(int)));


    verticalLayout->addWidget(qlpcQuickLegPosture);
    verticalLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    verticalLayout->addWidget(voscQuickArmPosture);
    verticalLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    verticalLayout->addWidget(voscQuickTrunkPosture);

    mainContent->setLayout(verticalLayout);

    mainLayout->addWidget(btnName);
    mainLayout->addWidget(mainContent);

    this->setLayout(mainLayout);
}

// PRIVATE SLOTS

void QuickSelectionControl::hideContent(){
    mainContent->hide();
}

void QuickSelectionControl::showContent(){
    mainContent->show();
}

void QuickSelectionControl::setExclusiveDisplayByName(const QString &name){
    if(name.compare(btnName->text()) == 0)
        showContent();
    else
        hideContent();
}

void QuickSelectionControl::setName(const QString &name){
    btnName->setText(name);
}

void QuickSelectionControl::btnNameClicked() {
    emit requestShowContent(btnName->text());
}
/*void BodyPostureView::voscQuickTrunkPostureChanged(int id){
    //qDebug()<<id;

    switch(id){

    case 0:
            record.setValue(DBConstants::COL_BODY_POSTURE_TRUNK_TILT,110);
            vcTrunkTilt->setValue(110);
            break;

    case 1:
            record.setValue(DBConstants::COL_BODY_POSTURE_TRUNK_TILT,20);
            vcTrunkTilt->setValue(20);
            break;

    case 2:
            record.setValue(DBConstants::COL_BODY_POSTURE_TRUNK_TILT,0);
            vcTrunkTilt->setValue(0);
            break;


    case 3:
            record.setValue(DBConstants::COL_BODY_POSTURE_TRUNK_TILT,-20);
            vcTrunkTilt->setValue(-20);
            break;


    case 4:
            record.setValue(DBConstants::COL_BODY_POSTURE_TRUNK_TILT,-45);
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
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,0);
            vcUpperArmAngle->setValue(0);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,90);
            vcForearmAngle->setValue(90);
            break;

        case 1:
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,0);
            vcUpperArmAngle->setValue(0);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,90);
            vcForearmAngle->setValue(90);
            break;

        case 2:
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,0);
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,0);
            vcUpperArmAngle->setValue(0);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,90);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,90);
            vcForearmAngle->setValue(90);
            break;
        default:
            break;
        }

        break;

        case 1:
        switch(sel){
        case 0:
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,90);
            vcUpperArmAngle->setValue(90);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,180);
            vcForearmAngle->setValue(180);
            break;

        case 1:
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,90);
            vcUpperArmAngle->setValue(90);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,180);
            vcForearmAngle->setValue(180);
            break;

        case 2:
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,90);
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,90);
            vcUpperArmAngle->setValue(90);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,180);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,180);
            vcForearmAngle->setValue(180);
            break;
        default:
            break;
        }
        break;

        case 2:
        switch(sel){
        case 0:
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,135);
            vcUpperArmAngle->setValue(135);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,180);
            vcForearmAngle->setValue(180);
            break;

        case 1:
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,135);
            vcUpperArmAngle->setValue(135);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,180);
            vcForearmAngle->setValue(180);
            break;

        case 2:
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_RIGHT,135);
            record.setValue(DBConstants::COL_BODY_POSTURE_UPPER_ARM_ANGLE_LEFT,135);
            vcUpperArmAngle->setValue(135);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_RIGHT,180);
            record.setValue(DBConstants::COL_BODY_POSTURE_FOREARM_ANGLE_LEFT,180);
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

void BodyPostureView::voscQuickArmPostureSpecificationChanged(int id){
qDebug()<<"Spezifikation"<<id;
}

void BodyPostureView::qlpcQuickLegPostureChanged(int id, int speci){
    qDebug()<<"Bein Option"<<id<<"Bein Spezifikation"<<speci;
    switch (id) {
    case 0:
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,180);
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,180);
        vcHipAngle->setValue(180);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,180);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,180);
        vcKneeAngle->setValue(180);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    case 1:
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,90);
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,90);
        vcHipAngle->setValue(90);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,45);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,45);
        vcKneeAngle->setValue(45);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    case 2:
        switch(speci){
        case 0:
            record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,135);
            record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,90);
            vcHipAngle->setValue(90);
            record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,0);
            record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,45);
            vcKneeAngle->setValue(45);
            record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
            record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
            vcAnkleAngle->setValue(90);
            break;
        case 1:
            record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,90);
            record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,135);
            vcHipAngle->setValue(90);
            record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,45);
            record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,0);
            vcKneeAngle->setValue(45);
            record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
            record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
            vcAnkleAngle->setValue(90);
            break;
        case 2:
            record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,135);
            record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,135);
            vcHipAngle->setValue(135);
            record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,0);
            record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,0);
            vcKneeAngle->setValue(0);
            record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
            record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
            vcAnkleAngle->setValue(90);
            break;
        }

        break;
    case 3:
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,180);
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,180);
        vcHipAngle->setValue(180);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,180);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,180);
        vcKneeAngle->setValue(180);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    case 4:
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,180);
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,180);
        vcHipAngle->setValue(180);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,180);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,180);
        vcKneeAngle->setValue(180);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
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
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,135);
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,90);
        vcHipAngle->setValue(90);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,0);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,45);
        vcKneeAngle->setValue(45);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    case 1:
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,90);
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,135);
        vcHipAngle->setValue(90);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,45);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,0);
        vcKneeAngle->setValue(45);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    case 2:
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_LEFT,135);
        record.setValue(DBConstants::COL_BODY_POSTURE_HIP_ANGLE_RIGHT,135);
        vcHipAngle->setValue(135);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_LEFT,0);
        record.setValue(DBConstants::COL_BODY_POSTURE_KNEE_ANGLE_RIGHT,0);
        vcKneeAngle->setValue(0);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_LEFT,90);
        record.setValue(DBConstants::COL_BODY_POSTURE_ANKLE_ANGLE_RIGHT,90);
        vcAnkleAngle->setValue(90);
        break;
    }
}*/

//GETTER/SETTER

QString QuickSelectionControl::getName() const{
    return btnName->text();
}
