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
    ~AngleView();

signals:

private slots:

private:
    AngleControl *acTorso;
    AngleControl *acArms;
    AngleControl *acLegs;
    AngleControl *acHead;

    QVector<int>* angleTorsoFlextion;
    QVector<int>* angleTorsoTilt;
    QVector<int>* angleTorsoRotation;

    QVector<int>* angleHeadTilt;
    QVector<int>* angleHeadRotation;
    QVector<int>* angleHeadSidewiseTilt;

    QVector<int>* angleUpperArmPosition;
    QVector<int>* angleUnderArmPosition;
    QVector<int>* angleUpperArmRotation;
    QVector<int>* angleUnderArmRotation;
    QVector<int>* angleUpperArmOpening;
    QVector<QString*> *textsWrist;

    QVector<int>* angleLegHip;
    QVector<int>* angleLegKnee;
    QVector<int>* angleLegAnkle;
    QVector<QString*>* textsLegPosition;

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
