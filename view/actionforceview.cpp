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

    valConIntensity = new ValueControl(VALUE_CONTROL, this);
    valConIntensity->setValues(0, 300, valuesIntensity, new QString(""));
    valConIntensity->setUnit("N");
    valConIntensity->setText("Intensität");

    valConDirection = new ValueControl(TEXT_CONTROL, this);
    valConDirection->setValues(textsDirection, textsDirectionValues, new QString(""));
    valConDirection->setText("Richtung:");

    valConOrgan = new ValueControl(TEXT_CONTROL, this);
    valConOrgan->setValues(textsOrgan, textsOrgan, new QString(""));
    valConOrgan->setText("Organ:");

    valConUsedHand = new ValueControl(TEXT_CONTROL, this);
    valConUsedHand->setValues(textsUsedHand, textsUsedHand, new QString(""));
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
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scMainContent);

    this->setCentralWidget(scMainContent);
}
