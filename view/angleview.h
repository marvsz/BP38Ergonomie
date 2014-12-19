#ifndef ANGLEVIEW_H
#define ANGLEVIEW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QVector>
#include "anglecontrol.h"
#include "variant.h"
#include "subvariant.h"
#include "variantspecification.h"
#include "enum.h"
#include <QPushButton>
#include <QLabel>

namespace Ui {
class AngleView;
}

class AngleView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AngleView(QWidget *parent = 0);

public slots:
    void showTorso();
    void showArms();
    void showLegs();
    void showHead();
    void selectLeftAV();
    void selectRightAV();
    void selectAV();

signals:

private:
    AngleControl *acTorso;
    AngleControl *acArms;
    AngleControl *acLegs;
    AngleControl *acHead;

    const QVector<int> angleTorsoFlextion = QVector<int>()<<-45<<-20<<0<<20<<45<<90<<110;
    const QVector<int> angleTorsoTilt = QVector<int>()<<0<<20<<45<<60<<90;
    const QVector<int> angleTorsoRotation = QVector<int>()<<0<<20<<45<<60<<90;

    const QVector<int> angleHeadTilt = QVector<int>()<<-90<<-45<<0<<45<<90;
    const QVector<int> angleHeadRotation = QVector<int>()<<0<<20<<45;
    const QVector<int> angleHeadSidewiseTilt = QVector<int>()<<0<<20<<45;

    const QVector<int> angleUpperArmPosition = QVector<int>()<<-90<<0<<45<<90<<135<<180;
    const QVector<int> angleUnderArmPosition = QVector<int>()<<0<<45<<90<<135<<180;
    const QVector<int> angleUpperArmRotation = QVector<int>()<<-45<<0<<45<<90;
    const QVector<int> angleUnderArmRotation = QVector<int>()<<-90<<-45<<0<<45<<90;
    const QVector<int> angleUpperArmOpening = QVector<int>()<<-90<<-45<<0<<45<<90;
    const QVector<QString> textsWrist = QVector<QString>()<<"Palmarflexion"<<"Dorsalextension"<<"Ularabduktion"<<"Radialabduktion";

    const QVector<int> angleLegHip = QVector<int>()<<45<<90<<135<<180;
    const QVector<int> angleLegKnee = QVector<int>()<<0<<45<<90<<135<<180;
    const QVector<int> angleLegAnkle = QVector<int>()<<90<<135<<180;
    const QVector<QString> textsLegPosition = QVector<QString>()<<"stehend"<<"sitzend"<<"gehend"<<"laufend"<<"kniend&&hockend"<<"liegend"<<"kletternd";

    VariantSpecification* varSpeciArms;
    VariantSpecification* varSpeciLegs;

    Variant* torsoFlextion;
    Variant* torsoTilt;
    Variant* torsoRotation;

    Variant* headTilt;
    Variant* headRotation;
    Variant* headSidewiseTilt;

    Variant* armsPosition;
    SubVariant* armsUnderPosition;
    Variant* armsRotation;
    SubVariant* armsUnderRotation;
    Variant* armsOpening;
    Variant* armsWrist;

    Variant* legPosition;
    Variant* legAngle;
    SubVariant* legKnee;
    SubVariant* legAnkle;

    QWidget *main;

};

#endif // ANGLEWINDOW_H
