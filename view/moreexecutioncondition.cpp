#include "moreexecutioncondition.h"

#include <QLabel>
#include "optionselectioncontrol.h"

MoreExecutionCondition::MoreExecutionCondition(QWidget *parent) :
    QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    mecLayout = new QFormLayout;
    resultedMecLayout = new QFormLayout;

    boolSelectionStrings = new QVector<QString*>();
    (*boolSelectionStrings)<<new QString("Ja")<<new QString("Nein");

    noMiddleHighSelectionStrings = new QVector<QString*>();
    (*noMiddleHighSelectionStrings)<<new QString("keine")<<new QString("mittlere")<<new QString("hohe");

    noMiddleStrongSelectionStrings = new QVector<QString*>();
    (*noMiddleStrongSelectionStrings)<<new QString("keine")<<new QString("mittlere")<<new QString("starke");

    noLowHighSelectionStrings = new QVector<QString*>();
    (*noLowHighSelectionStrings)<<new QString("keine")<<new QString("geringe")<<new QString("hohe");

    mainLayout->addWidget(new QLabel("Weitere Ausführungsbedingungen"), 0, Qt::AlignCenter);

    mecLayout->addRow("Rumpfabstützung:", new OptionSelectionControl(boolSelectionStrings, this));
    mecLayout->addRow("Armabstützung:", new OptionSelectionControl(boolSelectionStrings, this));
    mecLayout->addRow("Notwendige Präzision:", new OptionSelectionControl(noMiddleHighSelectionStrings, this));
    mecLayout->addRow("Notwendige Geschwindigkeit:", new OptionSelectionControl(noMiddleHighSelectionStrings, this));
    mecLayout->addRow("Notwendige Beschleunigung:", new OptionSelectionControl(noMiddleHighSelectionStrings, this));
    mecLayout->addRow("Vorhandene Vibrationen:", new OptionSelectionControl(noMiddleStrongSelectionStrings, this));

    mainLayout->addLayout(mecLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0, 30, QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainLayout->addWidget(new QLabel("Resultierende Einschränkungen auf den Arbeitsvorgang durch:"), 0, Qt::AlignLeft);

    resultedMecLayout->addRow("Greifbedingung:", new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow("Zugänglichkeit:", new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow("Untergrund (Boden):", new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow("Lichtverhältnisse:", new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow("Klima:", new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow("Wind:", new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow("Kleidung:", new OptionSelectionControl(noLowHighSelectionStrings, this));
    resultedMecLayout->addRow("Bewegungsfreiheit:", new OptionSelectionControl(noLowHighSelectionStrings, this));

    mainLayout->addLayout(resultedMecLayout);

    this->setLayout(mainLayout);

}
