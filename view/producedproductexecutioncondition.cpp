#include "producedproductexecutioncondition.h"
#include <QGridLayout>
#include <QLabel>
#include "separator.h"
#include "numberlineedit.h"

ProducedProductExecutionCondition::ProducedProductExecutionCondition(QWidget *parent) :
    QWidget(parent),
    txtbxWorkingHeight(new NumberLineEdit(this)),
    txtbxDistance(new NumberLineEdit(this)),
    txtbxImpulseCount(new NumberLineEdit(this)),
    valConGrabType(new ValueControl(TEXT_CONTROL, this))
{

    valConGrabType->setValues(false, grabTypeTexts, grabTypeTexts, new QString(":/icons/GrabType/GrabType_"));
    valConGrabType->setText(tr("grasping type: [EAWS V 1.3.2c]"));
    valConGrabType->setTextHint(tr("grasping type"));

    oscImpulseIntensity = new OptionSelectionControl(impulseIntensityTexts, this);

    txtbxDistance->setPlaceholderText(tr("distance to the produced product [cm]"));
    txtbxImpulseCount->setPlaceholderText(tr("count of the impulse"));
    txtbxWorkingHeight->setPlaceholderText(tr("working height of the work process [cm]"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel(tr("produced product:")), 0, 0, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("working height [cm]:")), 1, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxWorkingHeight, 1, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("distance [cm]:")), 2, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxDistance, 2, 1, 1, 1, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 3, 0, 1, 2, 0);
    mainLayout->addWidget(valConGrabType, 4, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 5, 0, 1, 2, 0);
    mainLayout->addWidget(new QLabel(tr("impulse intensity:")), 6, 0, 1, 1, 0);
    mainLayout->addWidget(oscImpulseIntensity, 6, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("impule count:")), 7, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxImpulseCount, 7, 1, 1, 1, 0);

    this->setLayout(mainLayout);
}
