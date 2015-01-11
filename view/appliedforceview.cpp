#include "appliedforceview.h"
#include "separator.h"
#include "flickcharm.h"
#include <QScroller>

const QVector<QString> AppliedForceView::ORGAN_TEXTS = QVector<QString>()<<tr("finger")<<tr("hand")<<tr("arm")<<tr("foot/leg")<<tr("full body");
const QVector<QString> AppliedForceView::DIRECTION_TEXTS = QVector<QString>()<<tr("above")<<tr("below")<<tr("front")<<tr("back")<<tr("right")<<tr("left");
const QVector<QString> AppliedForceView::DIRECTION_VALUES = QVector<QString>()<<tr("+A")<<tr("-A")<<tr("+B")<<tr("-B")<<tr("+C")<<tr("-C");
const QVector<int> AppliedForceView::INTENSITY_VALUES = QVector<int>()<<5<<20<<50<<100<<150;


AppliedForceView::AppliedForceView(QWidget *parent) :
    QWidget(parent),
    valConIntensity(new ValueControl(VALUE_CONTROL, this)),
    valConDirection(new ValueControl(TEXT_CONTROL, this)),
    valConOrgan(new ValueControl(TEXT_CONTROL, this))
{
    valConIntensity->setValues(0, 300, INTENSITY_VALUES, new QString(""));
    valConIntensity->setUnit(tr("N"));
    valConIntensity->setText(tr("intensity"));

    valConDirection->setValues(true, DIRECTION_TEXTS, DIRECTION_VALUES, new QString(""));
    valConDirection->setText(tr("direction:"));

    valConOrgan->setValues(true, ORGAN_TEXTS, ORGAN_TEXTS, new QString(""));
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
void AppliedForceView::setValues(const QString &organ, const QString &direction, int intensity){
    valConOrgan->setValue(organ);
    valConDirection->setValue(direction);
    valConIntensity->setValue(intensity);
}

//GETTER
int AppliedForceView::getIntensity() const{
    return valConIntensity->getValue();
}
QString AppliedForceView::getOrgan() const{
    return valConOrgan->getTextValue();
}
QString AppliedForceView::getDirection() const{
    return valConDirection->getTextValue();
}
