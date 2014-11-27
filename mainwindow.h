#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QVector>
#include "anglecontrol.h"
#include "variant.h"
#include "subvariant.h"
#include "variantspecification.h"
#include "enums.h"
#include "stopwatch.h"
#include <QPushButton>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


signals:
    void menuViewSelected();

private slots:
    void openMenuView();

private:
    AngleControl *ac1;
    AngleControl *ac2;
    AngleControl *ac3;
    AngleControl *ac4;







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

    QVector<int>* angleLegHip;
    QVector<int>* angleLegKnee;
    QVector<int>* angleLegAnkle;

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

    Variant* legAngle;
    SubVariant* legKnee;
    SubVariant* legAnkle;


    QPushButton *btnBack;
    QLabel *lblViewName;

    StopWatch *stopWatch;
    QWidget *control;
    QWidget *timer;

    QWidget *main;

};

#endif // MAINWINDOW_H
