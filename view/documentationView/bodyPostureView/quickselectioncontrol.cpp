#include "quickselectioncontrol.h"
#include "../../separator.h"
QuickSelectionControl::QuickSelectionControl(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QVBoxLayout),
    verticalLayout(new QHBoxLayout()),
    mainContent(new QWidget()),
    btnName(new QPushButton()),
    qlpcQuickLegPosture(new QuickLegPostureControl),
    voscQuickArmPosture(new QuickArmPostureControl),
    voscQuickTrunkPosture(new VerticalOptionSelectionControl),
    //hans(new QPixmap),
    hansHolder(new QLabel)
{

    btnName->setMaximumWidth(150);
    connect(btnName, SIGNAL(clicked()), this, SLOT(btnNameClicked()));

    qlpcQuickLegPosture->setValues(QUICK_LEG_POSTURE_TEXTS,LEFT_RIGHT_TEXTS,tr("Quick Leg Posture"));
    connect(qlpcQuickLegPosture, SIGNAL(selectionChanged(int,int)), this, SLOT(qlpcQuickLegPostureChanged(int,int)));
    connect(qlpcQuickLegPosture, SIGNAL(specificationChanged(int)), this, SLOT(qlpcQuickLegPostureSpecificationChagend(int)));

    voscQuickArmPosture->setValues(QUICK_ARM_POSTURE_TEXTS,LEFT_RIGHT_TEXTS, tr("Quick Arm Posture"));
    connect(voscQuickArmPosture, SIGNAL(selectionChanged(int,int)), this, SLOT(voscQuickArmPostureChanged(int,int)));

    voscQuickTrunkPosture->setValues(QUICK_TRUNK_POSTURE_TEXTS, tr("Quick Trunk Posture") );
    connect(voscQuickTrunkPosture, SIGNAL(selectionChanged(int)), this, SLOT(voscQuickTrunkPostureChanged(int)));



    hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_noBending);
    hansHolder->setFixedSize(QSize(275,313));

    verticalLayout->addWidget(qlpcQuickLegPosture);
    verticalLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    verticalLayout->addWidget(voscQuickArmPosture);
    verticalLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    verticalLayout->addWidget(voscQuickTrunkPosture);
    verticalLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    verticalLayout->addWidget(hansHolder);

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
    if((name.compare(this->name) == 0) && !shown){
        showContent();
        shown = true;
    }
    else{
        hideContent();
        shown = false;
    }
}

void QuickSelectionControl::setName(const QString &name){
    this->name = name;
}

void QuickSelectionControl::setButtonIcon(const QString &objectName, const QSize &size){
    btnName->setObjectName(objectName);
    btnName->setFixedSize(size);
}

void QuickSelectionControl::btnNameClicked() {  
    emit requestShowContent(this->name);
}

void QuickSelectionControl::voscQuickTrunkPostureChanged(int id){
    emit quickTrunkPostureChanged(id);
    switch (id) {
    case 0:
        hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_strongBendingFront);
        break;
    case 1:
        hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_lightBendingFront);
        break;
    case 2:
        hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_noBending);
        break;
    case 3:
        hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_lightBendingBack);
        break;
    case 4:
        hansHolder->setPixmap(hans_standing_bothArms_atElbowHeight_strongBendingBack);
        break;
    default:
        hansHolder->setPixmap(hans);
        break;
    }
}

void QuickSelectionControl::voscQuickArmPostureChanged(int id, int sel){
    emit quickArmPostureChanged(id,sel);
}

void QuickSelectionControl::qlpcQuickLegPostureChanged(int id,int sel){
    emit quickLegPostureChanged(id,sel);
}

void QuickSelectionControl::qlpcQuickLegPostureSpecificationChagend(int sel){
    emit quickLegPostureSpecificationChanged(sel);
}


//GETTER/SETTER

QString QuickSelectionControl::getName() const{
    return this->name;
}
