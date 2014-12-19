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

    const QVector<QString> grabTypeTexts = QVector<QString>()<<"Daumenkontaktgriff"<<"Zeigefingerkontaktgriff"<<"Handkontaktgriff"<<"Daumen auf 2 Finger"<<"Fingerzufassungsgriff"<<"Daumenzeigefingergriff"<<"Zange"<<"Umfassungsgriff";
    const QVector<QString> impulseIntensityTexts = QVector<QString>()<<"klein"<<"mittel"<<"stark";

};

#endif // PRODUCEDPRODUCTEXECUTIONCONDITION_H
