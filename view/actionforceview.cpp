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
    valConIntensity->setUnit(tr("N"));
    valConIntensity->setText(tr("intensity"));

    valConDirection = new ValueControl(TEXT_CONTROL, this);
    valConDirection->setValues(true, textsDirection, textsDirectionValues, new QString(""));
    valConDirection->setText(tr("direction:"));

    valConOrgan = new ValueControl(TEXT_CONTROL, this);
    valConOrgan->setValues(true, textsOrgan, textsOrgan, new QString(""));
    valConOrgan->setText(tr("organ:"));

    valConUsedHand = new ValueControl(TEXT_CONTROL, this);
    valConUsedHand->setValues(true, textsUsedHand, textsUsedHand, new QString(""));
    valConUsedHand->setText(tr("used hand:"));

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
