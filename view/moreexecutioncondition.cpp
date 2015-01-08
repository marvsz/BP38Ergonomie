#include "moreexecutioncondition.h"
#include "numberlineedit.h"
#include <QLabel>
#include "optionselectioncontrol.h"

MoreExecutionCondition::MoreExecutionCondition(QWidget *parent) :
    QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    mecLayout = new QFormLayout;
    resultedMecLayout = new QFormLayout;

    mainLayout->addWidget(new QLabel(tr("more workingconditions")), 0, Qt::AlignCenter);

    mecLayout->addRow(tr("torso support:"), new OptionSelectionControl(boolSelectionStrings, this));
    mecLayout->addRow(tr("arm support:"), new OptionSelectionControl(boolSelectionStrings, this));
    mecLayout->addRow(tr("needed precision:"), new OptionSelectionControl(noMiddleHighSelectionStrings, this));
    mecLayout->addRow(tr("needed speed:"), new OptionSelectionControl(noMiddleHighSelectionStrings, this));
    mecLayout->addRow(tr("needed velocity:"), new OptionSelectionControl(noMiddleHighSelectionStrings, this));
    mecLayout->addRow(tr("given vibration:"), new OptionSelectionControl(noMiddleStrongSelectionStrings, this));

    mainLayout->addLayout(mecLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0, 30, QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(new QLabel(tr("resulting constraints to the work process through:")), 0, Qt::AlignLeft);

    resultedMecLayout->addRow(tr("grasp conditions:"), new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow(tr("accessibility:"), new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow(tr("terrain:"), new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow(tr("lighting:"), new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow(tr("clima:"), new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow(tr("wind:"), new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow(tr("clothing:"), new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow(tr("abillity to move:"), new OptionSelectionControl(noLowHighSelectionStrings, this));

    mainLayout->addLayout(resultedMecLayout);

    this->setLayout(mainLayout);

}
