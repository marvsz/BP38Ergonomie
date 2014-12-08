#include "actionforceview.h"
#include "separator.h"
#include "flickcharm.h"
#include <QScroller>

ActionForceView::ActionForceView(QWidget *parent) :
    QMainWindow(parent)
{
    wdgtMainContent = new QWidget(this);
    scMainContent = new QScrollArea(this);
    lytMainContent = new QVBoxLayout;

    textsDirection = new QVector<QString*>();
    (*textsDirection)<<new QString("Links")<<new QString("Rechts")<<new QString("Oben")<<new QString("Unten")<<new QString("Vorne")<<new QString("Hinten");
    textsOrgan = new QVector<QString*>();
    (*textsOrgan)<<new QString("Finger")<<new QString("Hand")<<new QString("Arm")<<new QString("Fuß/Bein")<<new QString("Ganzkörper");
    textsUsedHand = new QVector<QString*>();
    (*textsUsedHand)<<new QString("Beide")<<new QString("Rechts")<<new QString("Links");
    valuesIntensity = new QVector<int>();
    (*valuesIntensity)<<5<<20<<50<<100<<150;

    valConIntensity = new ValueControl(VALUE_CONTROL, this);
    valConIntensity->setValues(0, 300, valuesIntensity, new QString(""));
    valConIntensity->setUnit("N");
    valConIntensity->setText("Intensität");

    valConDirection = new ValueControl(TEXT_CONTROL, this);
    valConDirection->setValues(textsDirection, new QString(""));
    valConDirection->setText("Richtung:");

    valConOrgan = new ValueControl(TEXT_CONTROL, this);
    valConOrgan->setValues(textsOrgan,new QString(""));
    valConOrgan->setText("Organ:");

    valConUsedHand = new ValueControl(TEXT_CONTROL, this);
    valConUsedHand->setValues(textsUsedHand, new QString(""));
    valConUsedHand->setText("Benutzte Hand:");

    lytMainContent->addWidget(valConIntensity);
    lytMainContent->addWidget(new Separator(Qt::Horizontal, 3, this));
    lytMainContent->addWidget(valConDirection);
    lytMainContent->addWidget(new Separator(Qt::Horizontal, 3, this));
    lytMainContent->addWidget(valConOrgan);
    lytMainContent->addWidget(new Separator(Qt::Horizontal, 3, this));
    lytMainContent->addWidget(valConUsedHand);
    wdgtMainContent->setLayout(lytMainContent);

    scMainContent->setWidget(wdgtMainContent);
    scMainContent->setWidgetResizable(true);
    //QScroller::grabGesture(scMainContent->viewport(), QScroller::LeftMouseButtonGesture);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scMainContent);

    this->setCentralWidget(scMainContent);
}
