#ifndef BODYMEASUREMENTVIEW_H
#define BODYMEASUREMENTVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <textlineedit.h>
#include <selectablevaluebutton.h>
#include <valuecontrol.h>
#include "../view/navigation/simplenavigateablewidget.h"


class BodyMeasurementView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit BodyMeasurementView(QWidget *parent = 0);


signals:

private slots:
    void btnHeadClicked();
    void btnTorsoClicked();
    void btnLegsClicked();
    void btnArmClicked();

private:
    ValueControl *vcHeadNeck;

    ValueControl *vcThighLength;
    ValueControl *vcTibialHeight;
    ValueControl *vcFootLength;
    ValueControl *vcShoulderWidth;
    ValueControl *vcShoulderBiacromial;
    ValueControl *vcShoulderBideltoid;
    ValueControl *vcUpperArmLength;
    ValueControl *vcForearmLength;
    ValueControl *vcHandLength;
    ValueControl *vcTorsoHeight;

    QLabel *lblHeadNeck;
    QLabel *lblUpperBody;
    QLabel *lblArmsHands;
    QLabel *lblLowerBody;
    QLabel *lblSelectBodyPart;


    QWidget *head;
    QWidget *torso;
    QWidget *arms;
    QWidget *legs;


    SelectableValueButton *btnHead;
    SelectableValueButton *btnTorso;
    SelectableValueButton *btnArmLeft;
    SelectableValueButton *btnArmRight;
    SelectableValueButton *btnLegs;
};

#endif // BODYMEASUREMENTVIEW_H
