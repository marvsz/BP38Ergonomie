#include "generalexecutioncondition.h"
#include "separator.h"

GeneralExecutionCondition::GeneralExecutionCondition(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QGridLayout),
    txtbxDescription(new QLineEdit(this)),
    txtbxDistance(new QLineEdit(this)),
    txtbxImpulseCount(new QLineEdit(this)),
    txtbxWorkingHeight(new QLineEdit(this)),
    valConGrabType(new ValueControl(TEXT_CONTROL, this)),
    valConMtmCode(new ValueControl(TEXT_CONTROL, this))
{
    grabTypeTexts = new QVector<QString*>();
    mtmCodeTexts = new QVector<QString*>();
    impulseIntensityTexts = new QVector<QString*>();
    (*grabTypeTexts)<<new QString("Daumenkontaktgriff")<<new QString("Zeigefingerkontaktgriff")<<new QString("Handkontaktgriff")<<new QString("Daumen auf 2 Finger")<<new QString("Fingerzufassungsgriff")<<new QString("Daumen-Zeigefingergriff")<<new QString("Zange")<<new QString("Umfassungsgriff");
    (*mtmCodeTexts)<<new QString("Aufnehmen/Plazieren (A)")<<new QString("Hilfsmittel handhaben (H)")<<new QString("Platzieren(P)")<<new QString("Betätigen (B)")<<new QString("Körperbewegung (K)");
    (*impulseIntensityTexts)<<new QString("klein")<<new QString("mittel")<<new QString("stark");

    valConMtmCode->setValues(mtmCodeTexts, new QString(":/Icon/Icon/mtmCode/mtmCode_"));
    valConMtmCode->setText("MTM Code:");
    valConMtmCode->setTextHint("MTM Code des Arbeitsvorganges");
    valConGrabType->setValues(grabTypeTexts, new QString(":/Icon/Icon/grabType/grabType_"));
    valConGrabType->setText("Greifart: [EAWS V 1.3.2c]");
    valConGrabType->setTextHint("Greifart");

    oscImpulseIntensity = new OptionSelectionControl(impulseIntensityTexts, this);

    txtbxDescription->setPlaceholderText("Beschreibung des Arbeitsvorganges");
    txtbxDistance->setInputMask("#000");
    txtbxDistance->setPlaceholderText("Abstand zum Arbeitsobjekt [cm]");
    txtbxImpulseCount->setInputMask("#000");
    txtbxImpulseCount->setPlaceholderText("Anzahl der Impulse");
    txtbxWorkingHeight->setInputMask("#000");
    txtbxWorkingHeight->setPlaceholderText("Arbeitshöhe des Arbeitsvorganges [cm]");

    mainLayout->addWidget(new QLabel("Beschreibung:"), 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxDescription, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 1, 0, 1, 2, 0);
    mainLayout->addWidget(valConMtmCode, 2, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 3, 0, 1, 2, 0);
    mainLayout->addWidget(new QLabel("Produziertes Produkt:"), 4, 0, 1, 1, 0);
    mainLayout->addWidget(new QLabel("Arbeitshöhe [cm]:"), 5, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxWorkingHeight, 5, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel("Abstand [cm]:"), 6, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxDistance, 6, 1, 1, 1, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 7, 0, 1, 2, 0);
    mainLayout->addWidget(valConGrabType, 8, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 9, 0, 1, 2, 0);
    mainLayout->addWidget(new QLabel("Impulsintensität:"), 10, 0, 1, 1, 0);
    mainLayout->addWidget(oscImpulseIntensity, 10, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel("Impulsanzahl:"), 11, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxImpulseCount, 11, 1, 1, 1, 0);

    this->setLayout(mainLayout);

}
