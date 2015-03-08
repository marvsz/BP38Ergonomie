#include "appliedforceview.h"
#include "../separator.h"
#include "../flickcharm.h"
#include "../../databaseHandler/dbconstants.h"
#include <QScroller>

const QVector<int> AppliedForceView::INTENSITY_VALUES = QVector<int>()<<5<<20<<50<<100<<150;


AppliedForceView::AppliedForceView(QWidget *parent) :
    TitledWidget(tr("Applied force"), parent),
    valConIntensity(new ValueControl(VALUE, this)),
    valConDirection(new ValueControl(TEXT, this)),
    valConOrgan(new ValueControl(TEXT, this))
{
    valConIntensity->setValues(0, 300, INTENSITY_VALUES, QString(""));
    valConIntensity->setUnit(tr("N"));
    valConIntensity->setText(tr("intensity"));

    valConDirection->setValues(true, DIRECTION_TEXTS, DIRECTION_VALUES, QString(""));
    valConDirection->setText(tr("direction:"));

    valConOrgan->setValues(true, ORGAN_TEXTS, ORGAN_TEXTS, QString(""));
    valConOrgan->setText(tr("organ:"));

    QVBoxLayout *lytMainContent = new QVBoxLayout;
    lytMainContent->addWidget(valConIntensity);
    lytMainContent->addWidget(new Separator(Qt::Horizontal, 3, this));
    lytMainContent->addWidget(valConDirection);
    lytMainContent->addWidget(new Separator(Qt::Horizontal, 3, this));
    lytMainContent->addWidget(valConOrgan);

    QWidget *wdgtMainContent = new QWidget(this);
    wdgtMainContent->setLayout(lytMainContent);

    QScrollArea *scMainContent = new QScrollArea(this);
    scMainContent->setWidget(wdgtMainContent);
    scMainContent->setWidgetResizable(true);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scMainContent);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(scMainContent);
    this->setLayout(mainLayout);
}

//PUBLIC SLOTS
void AppliedForceView::setAppliedForce(QHash<QString, QVariant> values){
    valConOrgan->setValue(values.value(DBConstants::COL_APPLIED_FORCE_ORGAN).toString());
    valConDirection->setValue(values.value(DBConstants::COL_APPLIED_FORCE_DIRECTION).toString());
    valConIntensity->setValue(values.value(DBConstants::COL_APPLIED_FORCE_INTENSITY).toInt());
}

void AppliedForceView::onLeaving(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_APPLIED_FORCE_ORGAN, valConOrgan->getTextValue());
    values.insert(DBConstants::COL_APPLIED_FORCE_DIRECTION, valConDirection->getTextValue());
    values.insert(DBConstants::COL_APPLIED_FORCE_INTENSITY, valConIntensity->getValue());
    emit saveAppliedForce(values);
}
