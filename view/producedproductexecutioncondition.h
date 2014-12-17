#ifndef PRODUCEDPRODUCTEXECUTIONCONDITION_H
#define PRODUCEDPRODUCTEXECUTIONCONDITION_H

#include <QWidget>
#include "valuecontrol.h"
#include "optionselectioncontrol.h"
class producedProductExecutionCondition : public QWidget
{
    Q_OBJECT
public:
    explicit producedProductExecutionCondition(QWidget *parent = 0);

private:
    QLineEdit *txtbxWorkingHeight;
    QLineEdit *txtbxDistance;
    QLineEdit *txtbxImpulseCount;
    ValueControl *valConGrabType;
    OptionSelectionControl *oscImpulseIntensity;

    QVector<QString*> *grabTypeTexts;
    QVector<QString*> *impulseIntensityTexts;
};

#endif // PRODUCEDPRODUCTEXECUTIONCONDITION_H
