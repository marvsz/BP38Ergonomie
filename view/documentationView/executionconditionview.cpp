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
void ExecutionConditionView::setExecutionCondition(QHash<QString, QVariant> values){
    oscRightUpperArmSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_RIGHT_UPPER_ARM_SUPPORTED).toInt());
    oscLeftUpperArmSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_LEFT_UPPER_ARM_SUPPORTED).toInt());
    oscRightForearmSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_RIGHT_FOREARM_SUPPORTED).toInt());
    oscLeftForearmSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_LEFT_FOREARM_SUPPORTED).toInt());
    oscRightHandSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_RIGHT_HAND_SUPPORTED).toInt());
    oscLeftHandSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_LEFT_HAND_SUPPORTED).toInt());

    oscHeadSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_HEAD_SUPPORTED).toInt());
    oscTrunkSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_TRUNK_SUPPORT).toInt());

    oscRightThighSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_RIGHT_THIGH_SUPPORTED).toInt());
    oscLeftThighSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_LEFT_THIGH_SUPPORTED).toInt());
    oscRightLowerLegSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_RIGHT_LOWER_LEG_SUPPORTED).toInt());
    oscLeftLowerLegSupport->setSelectedByValue(values.value(DBConstants::COL_WORK_CONDITION_LEFT_LOWER_LEG_SUPPORTED).toInt());

    scGripCondition->setValue(values.value(DBConstants::COL_WORK_CONDITION_GRIP_CONDITION).toInt());
    scAccessibility->setValue(values.value(DBConstants::COL_WORK_CONDITION_ACCESSIBILITY).toInt());
    scGround->setValue(values.value(DBConstants::COL_WORK_CONDITION_GROUND).toInt());
    scLighting->setValue(values.value(DBConstants::COL_WORK_CONDITION_LIGHTING).toInt());
    scClimate->setValue(values.value(DBConstants::COL_WORK_CONDITION_CLIMATE).toInt());
    scWind->setValue(values.value(DBConstants::COL_WORK_CONDITION_WIND).toInt());
    scClothing->setValue(values.value(DBConstants::COL_WORK_CONDITION_CLOTHING).toInt());
    scRoomToMove->setValue(values.value(DBConstants::COL_WORK_CONDITION_ROOM_TO_MOVE).toInt());

    scPrecision->setValue(values.value(DBConstants::COL_WORK_CONDITION_PRECISION).toInt());
    scVelocity->setValue(values.value(DBConstants::COL_WORK_CONDITION_VELOCITY).toInt());
    scAcceleration->setValue(values.value(DBConstants::COL_WORK_CONDITION_ACCELERATION).toInt());
    scVibration->setValue(values.value(DBConstants::COL_WORK_CONDITION_VIBRATION).toInt());
}

void ExecutionConditionView::onLeaving(){

    QHash<QString, QVariant> values = QHash<QString, QVariant>();

    values.insert(DBConstants::COL_WORK_CONDITION_RIGHT_UPPER_ARM_SUPPORTED, oscRightUpperArmSupport->getSelectedValue().toInt());
    values.insert(DBConstants::COL_WORK_CONDITION_LEFT_UPPER_ARM_SUPPORTED, oscLeftUpperArmSupport->getSelectedValue().toInt());
    values.insert(DBConstants::COL_WORK_CONDITION_RIGHT_FOREARM_SUPPORTED, oscRightForearmSupport->getSelectedValue().toInt());
    values.insert(DBConstants::COL_WORK_CONDITION_LEFT_FOREARM_SUPPORTED, oscLeftForearmSupport->getSelectedValue().toInt());
    values.insert(DBConstants::COL_WORK_CONDITION_RIGHT_HAND_SUPPORTED, oscRightHandSupport->getSelectedValue().toInt());
    values.insert(DBConstants::COL_WORK_CONDITION_LEFT_HAND_SUPPORTED, oscLeftHandSupport->getSelectedValue().toInt());

    values.insert(DBConstants::COL_WORK_CONDITION_HEAD_SUPPORTED, oscHeadSupport->getSelectedValue().toInt());
    values.insert(DBConstants::COL_WORK_CONDITION_TRUNK_SUPPORT, oscTrunkSupport->getSelectedValue().toInt());
    values.insert(DBConstants::COL_WORK_CONDITION_RIGHT_THIGH_SUPPORTED, oscRightThighSupport->getSelectedValue().toInt());
    values.insert(DBConstants::COL_WORK_CONDITION_LEFT_THIGH_SUPPORTED, oscLeftThighSupport->getSelectedValue().toInt());
    values.insert(DBConstants::COL_WORK_CONDITION_RIGHT_LOWER_LEG_SUPPORTED, oscRightLowerLegSupport->getSelectedValue().toInt());
    values.insert(DBConstants::COL_WORK_CONDITION_LEFT_LOWER_LEG_SUPPORTED, oscLeftLowerLegSupport->getSelectedValue().toInt());

    values.insert(DBConstants::COL_WORK_CONDITION_GRIP_CONDITION, scGripCondition->getValue());
    values.insert(DBConstants::COL_WORK_CONDITION_ACCESSIBILITY, scAccessibility->getValue());
    values.insert(DBConstants::COL_WORK_CONDITION_GROUND, scGround->getValue());
    values.insert(DBConstants::COL_WORK_CONDITION_LIGHTING, scLighting->getValue());
    values.insert(DBConstants::COL_WORK_CONDITION_CLIMATE, scClimate->getValue());
    values.insert(DBConstants::COL_WORK_CONDITION_WIND, scWind->getValue());
    values.insert(DBConstants::COL_WORK_CONDITION_CLOTHING, scClothing->getValue());
    values.insert(DBConstants::COL_WORK_CONDITION_ROOM_TO_MOVE, scRoomToMove->getValue());

    values.insert(DBConstants::COL_WORK_CONDITION_PRECISION, scPrecision->getValue());
    values.insert(DBConstants::COL_WORK_CONDITION_VELOCITY, scVelocity->getValue());
    values.insert(DBConstants::COL_WORK_CONDITION_ACCELERATION, scAcceleration->getValue());
    values.insert(DBConstants::COL_WORK_CONDITION_VIBRATION, scVibration->getValue());

    emit saveExecutionCondition(values);
}
