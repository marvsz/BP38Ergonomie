#include "producedproductexecutioncondition.h"
#include <QGridLayout>
#include <QLabel>
#include "separator.h"
#include "numberlineedit.h"

producedProductExecutionCondition::producedProductExecutionCondition(QWidget *parent) :
    QWidget(parent),
    txtbxDistance(new NumberLineEdit(this)),
    txtbxImpulseCount(new NumberLineEdit(this)),
    txtbxWorkingHeight(new NumberLineEdit(this)),
    valConGrabType(new ValueControl(TEXT_CONTROL, this))
{
    grabTypeTexts = new QVector<QString*>();
    (*grabTypeTexts)<<new QString("Daumenkontaktgriff")<<new QString("Zeigefingerkontaktgriff")<<new QString("Handkontaktgriff")<<new QString("Daumen auf 2 Finger")<<new QString("Fingerzufassungsgriff")<<new QString("Daumen-Zeigefingergriff")<<new QString("Zange")<<new QString("Umfassungsgriff");
    impulseIntensityTexts = new QVector<QString*>();
    (*impulseIntensityTexts)<<new QString("klein")<<new QString("mittel")<<new QString("stark");

    valConGrabType->setValues(grabTypeTexts, grabTypeTexts, new QString(":/Icon/Icon/grabType/grabType_"));
    valConGrabType->setText("Greifart: [EAWS V 1.3.2c]");
    valConGrabType->setTextHint("Greifart");

    oscImpulseIntensity = new OptionSelectionControl(impulseIntensityTexts, this);

    txtbxDistance->setPlaceholderText("Abstand zum Arbeitsobjekt [cm]");
    txtbxImpulseCount->setPlaceholderText("Anzahl der Impulse");
    txtbxWorkingHeight->setPlaceholderText("Arbeitshöhe des Arbeitsvorganges [cm]");

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel("Produziertes Produkt:"), 0, 0, 1, 1, 0);
    mainLayout->addWidget(new QLabel("Arbeitshöhe [cm]:"), 1, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxWorkingHeight, 1, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel("Abstand [cm]:"), 2, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxDistance, 2, 1, 1, 1, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 3, 0, 1, 2, 0);
    mainLayout->addWidget(valConGrabType, 4, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 5, 0, 1, 2, 0);
    mainLayout->addWidget(new QLabel("Impulsintensität:"), 6, 0, 1, 1, 0);
    mainLayout->addWidget(oscImpulseIntensity, 6, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel("Impulsanzahl:"), 7, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxImpulseCount, 7, 1, 1, 1, 0);

    this->setLayout(mainLayout);
}
