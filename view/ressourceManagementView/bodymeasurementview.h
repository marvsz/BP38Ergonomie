#ifndef BODYMEASUREMENTVIEW_H
#define BODYMEASUREMENTVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "../textlineedit.h"
#include "../valuecontrol.h"
#include "../navigation/simplenavigateablewidget.h"


class BodyMeasurementView : public SimpleNavigateableWidget
{
    Q_OBJECT
public:
    explicit BodyMeasurementView(QWidget *parent = 0);

    int getHeadNeckLength() const;
    int getThighLength() const;
    int getTibialLength() const;
    int getFootLength() const;
    int getShoulderWidth() const;
    int getShoulderBiacromial() const;
    int getShoulderBideltoid() const;
    int getUpperArmLength() const;
    int getForearmLength() const;
    int getHandLength() const;
    int getTorsoHeight() const;


signals:

public slots:
    void setHeadNeckLength(int headNeckLength);
    void setThighLength(int thighLength);
    void setTibialLength(int tibialLength);
    void setFootLength(int footLength);
    void setShoulderWidth(int shoulderWidth);
    void setShoulderBiacromial(int shoulderBiacromial);
    void setShoulderBideltoid(int shoulderBideltoid);
    void setUpperArmLength(int upperArmLength);
    void setForearmLength(int forearmLength);
    void setHandLength(int handLength);
    void setTorsoHeight(int torsoHeight);

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
