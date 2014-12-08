#ifndef GENERALEXECUTIONCONDITION_H
#define GENERALEXECUTIONCONDITION_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include "valuecontrol.h"
#include "optionselectioncontrol.h"

class GeneralExecutionCondition : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralExecutionCondition(QWidget *parent = 0);

signals:

public slots:

private:
    QGridLayout *mainLayout;

    QLineEdit *txtbxDescription;
    QLineEdit *txtbxWorkingHeight;
    QLineEdit *txtbxDistance;
    QLineEdit *txtbxImpulseCount;
    ValueControl *valConMtmCode;
    ValueControl *valConGrabType;
    OptionSelectionControl *oscImpulseIntensity;

    QVector<QString*> *grabTypeTexts;
    QVector<QString*> *mtmCodeTexts;
    QVector<QString*> *impulseIntensityTexts;

};

#endif // GENERALEXECUTIONCONDITION_H
