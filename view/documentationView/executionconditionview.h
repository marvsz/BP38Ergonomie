#ifndef EXECUTIONCONDITIONVIEW_H
#define EXECUTIONCONDITIONVIEW_H

#include "../view/navigation/documentationviewnavigateablewidget.h"
#include <QLabel>
#include "slidercontrol.h"
#include "optionselectioncontrol.h"

class ExecutionConditionView : public DocumentationViewNavigateableWidget
{
    Q_OBJECT
public:
    explicit ExecutionConditionView(QWidget *parent = 0);

    int getHeadSupport() const;
    int getRightUpperArmSupport() const;
    int getLeftUpperArmSupport() const;
    int getRightForearmSupport() const;
    int getLeftForearmSupport() const;
    int getRightHandSupport() const;
    int getLeftHandSupport() const;
    int getTrunkSupport() const;
    int getRightThighSupport() const;
    int getLeftThighSupport() const;
    int getRightLowerLegSupport() const;
    int getLeftLowerLegSupport() const;
    int getPrecision() const;
    int getVelocity() const;
    int getAcceleration() const;
    int getGraspingType() const;
    int getAccessibility() const;
    int getGround() const;
    int getLighting() const;
    int getClimate() const;
    int getWind() const;
    int getClothing() const;
    int getVibration() const;
    int getRoomToMove() const;

signals:

public slots:
    void setArmSupports(int ruas, int luas, int rfs, int lfs, int rhs, int lhs);
    void setBodySupports(int head, int trunk);
    void setLegSupports(int rts, int lts, int rlls, int llls);
    void setResultingConstraints(int graspingType, int access, int ground, int lighting, int climate, int wind, int clothing, int roomToMove);
    void setConditionAttributes(int precision, int velocity, int acceleration, int vibration);

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
