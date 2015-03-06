#ifndef BODYMEASUREMENTVIEW_H
#define BODYMEASUREMENTVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "../textlineedit.h"
#include "../valuecontrol.h"
#include "../navigation/simplenavigateablewidget.h"
#include "../interfaces/ibodymeasurement.h"

class BodyMeasurementView : public SimpleNavigateableWidget, IBodyMeasurement
{
    Q_OBJECT
    Q_INTERFACES(IBodyMeasurement)
public:
    explicit BodyMeasurementView(QWidget *parent = 0);

signals:
    void saveBodyMeasurement(QHash<QString, QVariant> values);

public slots:
    void setBodyMeasurement(QHash<QString, QVariant> values);
    void onLeaving();

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


    QPushButton *btnHead;
    QPushButton *btnTorso;
    QPushButton *btnArmLeft;
    QPushButton *btnArmRight;
    QPushButton *btnLegs;
};

#endif // BODYMEASUREMENTVIEW_H
