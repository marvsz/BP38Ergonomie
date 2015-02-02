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

private:
    ValueControl *vcHeadNeck;

    ValueControl *vcThighLength;
    ValueControl *vcTibialHeight;
    ValueControl *vcFootLength;

    QLabel *lblUpperBody;
    QLabel *lblLowerBody;
    QLabel *lblShoulderWidth;
    QLabel *lblShoulderBiacromial;
    QLabel *lblShoulderBideltoid;
    QLabel *lblUpperArmLength;
    QLabel *lblForearmLength;
    QLabel *lblHandLength;
    QLabel *lblTorsoHeight;


    QWidget *head;
    QWidget *torso;
    QWidget *legs;


    SelectableValueButton *btnHead;
    SelectableValueButton *btnTorso;
    SelectableValueButton *btnLegs;
};

#endif // BODYMEASUREMENTVIEW_H
