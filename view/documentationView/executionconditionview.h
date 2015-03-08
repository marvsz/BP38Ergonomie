#ifndef EXECUTIONCONDITIONVIEW_H
#define EXECUTIONCONDITIONVIEW_H


#include "../navigation/titledwidget.h"
#include <QLabel>
#include "../slidercontrol.h"
#include "../optionselectioncontrol.h"
#include "../interfaces/iexecutioncondition.h"
#include "../../databaseHandler/dbconstants.h"

class ExecutionConditionView : public TitledWidget, IExecutionCondition
{
    Q_OBJECT
    Q_INTERFACES(IExecutionCondition)
public:
    explicit ExecutionConditionView(QWidget *parent = 0);

signals:
    void saveExecutionCondition(QHash<QString, QVariant> values);

public slots:
    void setExecutionCondition(QHash<QString, QVariant> values);
    void onLeaving();

private slots:

private:
    SliderControl *scPrecision;
    SliderControl *scVelocity;
    SliderControl *scAcceleration;
    SliderControl *scGripCondition;
    SliderControl *scAccessibility;
    SliderControl *scGround;
    SliderControl *scLighting;
    SliderControl *scClimate;
    SliderControl *scWind;
    SliderControl *scClothing;
    SliderControl *scVibration;
    SliderControl *scRoomToMove;

    OptionSelectionControl *oscHeadSupport;
    OptionSelectionControl *oscRightUpperArmSupport;
    OptionSelectionControl *oscLeftUpperArmSupport;
    OptionSelectionControl *oscRightForearmSupport;
    OptionSelectionControl *oscLeftForearmSupport;
    OptionSelectionControl *oscRightHandSupport;
    OptionSelectionControl *oscLeftHandSupport;
    OptionSelectionControl *oscTrunkSupport;
    OptionSelectionControl *oscRightThighSupport;
    OptionSelectionControl *oscLeftThighSupport;
    OptionSelectionControl *oscRightLowerLegSupport;
    OptionSelectionControl *oscLeftLowerLegSupport;

    const QStringList YES_NO_TEXTS = QStringList()<<(tr("yes"))<<(tr("no"));
    static const QVector<QVariant> YES_NO_VALUE;

};

#endif // EXECUTIONCONDITIONVIEW_H
