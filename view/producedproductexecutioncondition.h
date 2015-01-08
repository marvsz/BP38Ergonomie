#ifndef PRODUCEDPRODUCTEXECUTIONCONDITION_H
#define PRODUCEDPRODUCTEXECUTIONCONDITION_H

#include <QWidget>
#include "valuecontrol.h"
#include "optionselectioncontrol.h"
class ProducedProductExecutionCondition : public QWidget
{
    Q_OBJECT
public:
    explicit ProducedProductExecutionCondition(QWidget *parent = 0);

private:
    QLineEdit *txtbxWorkingHeight;
    QLineEdit *txtbxDistance;
    QLineEdit *txtbxImpulseCount;
    ValueControl *valConGrabType;
    OptionSelectionControl *oscImpulseIntensity;

    const QVector<QString> grabTypeTexts = QVector<QString>()<<tr("thumb contact grasp")<<tr("index contact grasp")<<tr("hand contact grasp")<<tr("thumb on 2 fingers")<<tr("finger to gripping grasp")<<tr("thumb index finger grasp")<<tr("wrench")<<tr("covering grasp");
    const QVector<QString> impulseIntensityTexts = QVector<QString>()<<tr("small")<<tr("medium")<<tr("strong");

};

#endif // PRODUCEDPRODUCTEXECUTIONCONDITION_H
