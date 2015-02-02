#ifndef BODYMEASUREMENTVIEW_H
#define BODYMEASUREMENTVIEW_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <textlineedit.h>
#include <selectablevaluebutton.h>
#include <valuecontrol.h>


class BodyMeasurementView : public QWidget
{
    Q_OBJECT
public:
    explicit BodyMeasurementView(QWidget *parent = 0);


signals:
    void back();

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

    QPushButton *btnBack;
    QLabel *lblViewName;
    QPushButton *btnFeedback;

};

#endif // BODYMEASUREMENTVIEW_H
