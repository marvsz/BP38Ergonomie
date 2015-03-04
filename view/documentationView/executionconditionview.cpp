#include "executionconditionview.h"
#include "../separator.h"
#include "../flickcharm.h"
#include <QScrollArea>


const QVector<QVariant> ExecutionConditionView::YES_NO_VALUE = QVector<QVariant>()<<1<<0;

ExecutionConditionView::ExecutionConditionView(QWidget *parent) :
    TitledWidget(tr("Working conditions"), parent),
    scPrecision(new SliderControl()),
    scVelocity(new SliderControl()),
    scAcceleration(new SliderControl()),
    scGripCondition(new SliderControl()),
    scAccessibility(new SliderControl()),
    scGround(new SliderControl()),
    scLighting(new SliderControl()),
    scClimate(new SliderControl()),
    scWind(new SliderControl()),
    scClothing(new SliderControl()),
    scVibration(new SliderControl()),
    scRoomToMove(new SliderControl()),
    oscHeadSupport(new OptionSelectionControl()),
    oscRightUpperArmSupport(new OptionSelectionControl()),
    oscLeftUpperArmSupport(new OptionSelectionControl()),
    oscRightForearmSupport(new OptionSelectionControl()),
    oscLeftForearmSupport(new OptionSelectionControl()),
    oscRightHandSupport(new OptionSelectionControl()),
    oscLeftHandSupport(new OptionSelectionControl()),
    oscTrunkSupport(new OptionSelectionControl()),
    oscRightThighSupport(new OptionSelectionControl()),
    oscLeftThighSupport(new OptionSelectionControl()),
    oscRightLowerLegSupport(new OptionSelectionControl()),
    oscLeftLowerLegSupport(new OptionSelectionControl())
{
    oscHeadSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscRightUpperArmSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscLeftUpperArmSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscRightForearmSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscLeftForearmSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscRightHandSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscLeftHandSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscTrunkSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscRightThighSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscLeftThighSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscRightLowerLegSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscLeftLowerLegSupport->setValues(YES_NO_TEXTS, YES_NO_VALUE);

    QLabel *lblSupports = new QLabel(tr("Supports"));
    lblSupports->setObjectName("lblHeader");

    QLabel *lblConstraints = new QLabel(tr("Resulting constraints by:"));
    lblConstraints->setObjectName("lblHeader");

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(lblSupports, 0, 0, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Head:")), 1, 0, 1, 1, 0);
    mainLayout->addWidget(oscHeadSupport, 1, 1, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Fixed), 1, 2, 1, 2, 0);
    mainLayout->addWidget(new QLabel(tr("trunk:")), 1, 3, 1, 1, 0);
    mainLayout->addWidget(oscTrunkSupport, 1, 4, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Left upper arm:")), 2, 0, 1, 1, 0);
    mainLayout->addWidget(oscLeftUpperArmSupport, 2, 1, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Fixed), 2, 2, 1, 2, 0);
    mainLayout->addWidget(new QLabel(tr("Right upper arm:")), 2, 3, 1, 1, 0);
    mainLayout->addWidget(oscRightUpperArmSupport, 2, 4, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Left forearm:")), 3, 0, 1, 1, 0);
    mainLayout->addWidget(oscLeftForearmSupport, 3, 1, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Fixed), 3, 2, 1, 2, 0);
    mainLayout->addWidget(new QLabel(tr("Right forearm:")), 3, 3, 1, 1, 0);
    mainLayout->addWidget(oscRightForearmSupport, 3, 4, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Left hand:")), 4, 0, 1, 1, 0);
    mainLayout->addWidget(oscLeftHandSupport, 4, 1, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Fixed), 4, 2, 1, 2, 0);
    mainLayout->addWidget(new QLabel(tr("Right hand:")), 4, 3, 1, 1, 0);
    mainLayout->addWidget(oscRightHandSupport, 4, 4, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Left thigh:")), 5, 0, 1, 1, 0);
    mainLayout->addWidget(oscLeftThighSupport, 5, 1, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Fixed), 5, 2, 1, 2, 0);
    mainLayout->addWidget(new QLabel(tr("Right thigh:")), 5, 3, 1, 1, 0);
    mainLayout->addWidget(oscRightThighSupport, 5, 4, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Left lower leg:")), 6, 0, 1, 1, 0);
    mainLayout->addWidget(oscLeftLowerLegSupport, 6, 1, 1, 1, 0);
    mainLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Fixed), 6, 2, 1, 2, 0);
    mainLayout->addWidget(new QLabel(tr("Right lower leg:")), 6, 3, 1, 1, 0);
    mainLayout->addWidget(oscRightLowerLegSupport, 6, 4, 1, 1, 0);

    mainLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 7, 0, 1, 2, 0);
    mainLayout->addWidget(new QLabel(tr("Needed precision:")), 8, 0, 1, 1, 0);
    mainLayout->addWidget(scPrecision, 8, 1, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Needed velocity:")), 9, 0, 1, 1, 0);
    mainLayout->addWidget(scVelocity, 9, 1, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Needed acceleration:")), 10, 0, 1, 1, 0);
    mainLayout->addWidget(scAcceleration, 10, 1, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Present vibration:")), 11, 0, 1, 1, 0);
    mainLayout->addWidget(scVibration, 11, 1, 1, 4, 0);

    mainLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed), 12, 0, 1, 2, 0);
    mainLayout->addWidget(lblConstraints, 13, 0, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Grasping condition:")), 14, 0, 1, 1, 0);
    mainLayout->addWidget(scGripCondition, 14, 1, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Accessibility:")), 15, 0, 1, 1, 0);
    mainLayout->addWidget(scAccessibility, 15, 1, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Ground:")), 16, 0, 1, 1, 0);
    mainLayout->addWidget(scGround, 16, 1, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Lighting:")), 17, 0, 1, 1, 0);
    mainLayout->addWidget(scLighting, 17, 1, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Climate:")), 18, 0, 1, 1, 0);
    mainLayout->addWidget(scClimate, 18, 1, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Wind:")), 19, 0, 1, 1, 0);
    mainLayout->addWidget(scWind, 19, 1, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Clothing:")), 20, 0, 1, 1, 0);
    mainLayout->addWidget(scClothing, 20, 1, 1, 4, 0);
    mainLayout->addWidget(new QLabel(tr("Elbowroom:")), 21, 0, 1, 1, 0);
    mainLayout->addWidget(scRoomToMove, 21, 1, 1, 4, 0);

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);

    QScrollArea *scMainContent = new QScrollArea();
    scMainContent->setWidget(mainWidget);
    scMainContent->setWidgetResizable(true);

    FlickCharm *fc = new FlickCharm();
    fc->activateOn(scMainContent);

    QVBoxLayout *scLayout = new QVBoxLayout;
    scLayout->addWidget(scMainContent);
    this->setLayout(scLayout);

}

//PUBLIC SLOTS
void ExecutionConditionView::setArmSupports(int ruas, int luas, int rfs, int lfs, int rhs, int lhs){
    oscRightUpperArmSupport->setSelectedByValue(ruas);
    oscLeftUpperArmSupport->setSelectedByValue(luas);
    oscRightForearmSupport->setSelectedByValue(rfs);
    oscLeftForearmSupport->setSelectedByValue(lfs);
    oscRightHandSupport->setSelectedByValue(rhs);
    oscLeftHandSupport->setSelectedByValue(lhs);
}
void ExecutionConditionView::setBodySupports(int head, int trunk){
    oscHeadSupport->setSelectedByValue(head);
    oscTrunkSupport->setSelectedByValue(trunk);
}
void ExecutionConditionView::setLegSupports(int rts, int lts, int rlls, int llls){
    oscRightThighSupport->setSelectedByValue(rts);
    oscLeftThighSupport->setSelectedByValue(lts);
    oscRightLowerLegSupport->setSelectedByValue(rlls);
    oscLeftLowerLegSupport->setSelectedByValue(llls);
}
void ExecutionConditionView::setResultingConstraints(int graspingType, int access, int ground, int lighting, int climate, int wind, int clothing, int roomToMove){
    scGripCondition->setValue(graspingType);
    scAccessibility->setValue(access);
    scGround->setValue(ground);
    scLighting->setValue(lighting);
    scClimate->setValue(climate);
    scWind->setValue(wind);
    scClothing->setValue(clothing);
    scRoomToMove->setValue(roomToMove);
}
void ExecutionConditionView::setConditionAttributes(int precision, int velocity, int acceleration, int vibration){
    scPrecision->setValue(precision);
    scVelocity->setValue(velocity);
    scAcceleration->setValue(acceleration);
    scVibration->setValue(vibration);
}


//GETTER
int ExecutionConditionView::getHeadSupport() const{
    return oscHeadSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getRightUpperArmSupport() const{
    return oscRightUpperArmSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getLeftUpperArmSupport() const{
    return oscLeftUpperArmSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getRightForearmSupport() const{
    return oscRightForearmSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getLeftForearmSupport() const{
    return oscLeftForearmSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getRightHandSupport() const{
    return oscRightHandSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getLeftHandSupport() const{
    return oscLeftHandSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getTrunkSupport() const{
    return oscTrunkSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getRightThighSupport() const{
    return oscRightThighSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getLeftThighSupport() const{
    return oscLeftThighSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getRightLowerLegSupport() const{
    return oscRightLowerLegSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getLeftLowerLegSupport() const{
    return oscLeftLowerLegSupport->getSelectedValue().toInt();
}
int ExecutionConditionView::getPrecision() const{
    return scPrecision->getValue();
}
int ExecutionConditionView::getVelocity() const{
    return scVelocity->getValue();
}
int ExecutionConditionView::getAcceleration() const{
    return scAcceleration->getValue();
}
int ExecutionConditionView::getGraspingType() const{
    return scGripCondition->getValue();
}
int ExecutionConditionView::getAccessibility() const{
    return scAccessibility->getValue();
}
int ExecutionConditionView::getGround() const{
    return scGround->getValue();
}
int ExecutionConditionView::getLighting() const{
    return scLighting->getValue();
}
int ExecutionConditionView::getClimate() const{
    return scClimate->getValue();
}
int ExecutionConditionView::getWind() const{
    return scWind->getValue();
}
int ExecutionConditionView::getClothing() const{
    return scClothing->getValue();
}
int ExecutionConditionView::getVibration() const{
    return scVibration->getValue();
}
int ExecutionConditionView::getRoomToMove() const{
    return scRoomToMove->getValue();
}
