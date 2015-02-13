#ifndef BODYMEASUREMENTVIEW_H
#define BODYMEASUREMENTVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <textlineedit.h>
#include <selectableiconbutton.h>
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


    SelectableIconButton *btnHead;
    SelectableIconButton *btnTorso;
    SelectableIconButton *btnArmLeft;
    SelectableIconButton *btnArmRight;
    SelectableIconButton *btnLegs;
};

#endif // BODYMEASUREMENTVIEW_H
