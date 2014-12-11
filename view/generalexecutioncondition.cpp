#include "generalexecutioncondition.h"
#include "separator.h"
#include "subactivitycontrol.h"
#include "numberlineedit.h"
#include <QGuiApplication>

GeneralExecutionCondition::GeneralExecutionCondition(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QGridLayout),
    txtbxDescription(new TextLineEdit(this)),
    txtbxDistance(new NumberLineEdit(this)),
    txtbxImpulseCount(new NumberLineEdit(this)),
    txtbxWorkingHeight(new NumberLineEdit(this)),
    valConGrabType(new ValueControl(TEXT_CONTROL, this)),
    valConMtmCode(new ValueControl(TEXT_CONTROL, this))
{
    grabTypeTexts = new QVector<QString*>();
    mtmCodeTexts = new QVector<QString*>();
    impulseIntensityTexts = new QVector<QString*>();
    mtmCodeValueTexts = new QVector<QString*>();
    (*grabTypeTexts)<<new QString("Daumenkontaktgriff")<<new QString("Zeigefingerkontaktgriff")<<new QString("Handkontaktgriff")<<new QString("Daumen auf 2 Finger")<<new QString("Fingerzufassungsgriff")<<new QString("Daumen-Zeigefingergriff")<<new QString("Zange")<<new QString("Umfassungsgriff");
    (*mtmCodeTexts)<<new QString("Aufnehmen/Plazieren (A)")<<new QString("Hilfsmittel handhaben (H)")<<new QString("Platzieren(P)")<<new QString("Betätigen (B)")<<new QString("Körperbewegung (K)");
    (*mtmCodeValueTexts)<<new QString("A")<<new QString("H")<<new QString("P")<<new QString("B")<<new QString("K");
    (*impulseIntensityTexts)<<new QString("klein")<<new QString("mittel")<<new QString("stark");

    valConMtmCode->setValues(mtmCodeTexts, mtmCodeValueTexts, new QString(":/Icon/Icon/mtmCode/mtmCode_"));
    valConMtmCode->setText("MTM Code:");
    valConMtmCode->setTextHint("MTM Code des Arbeitsvorganges");
    valConGrabType->setValues(grabTypeTexts, grabTypeTexts, new QString(":/Icon/Icon/grabType/grabType_"));
    valConGrabType->setText("Greifart: [EAWS V 1.3.2c]");
    valConGrabType->setTextHint("Greifart");

    oscImpulseIntensity = new OptionSelectionControl(impulseIntensityTexts, this);

    txtbxDescription->setPlaceholderText("Beschreibung des Arbeitsvorganges");
    txtbxDistance->setPlaceholderText("Abstand zum Arbeitsobjekt [cm]");
    txtbxImpulseCount->setPlaceholderText("Anzahl der Impulse");
    txtbxWorkingHeight->setPlaceholderText("Arbeitshöhe des Arbeitsvorganges [cm]");

    mainLayout->addWidget(new QLabel("Beschreibung:"), 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxDescription, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 1, 0, 1, 2, 0);
    mainLayout->addWidget(valConMtmCode, 2, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 3, 0, 1, 2, 0);
    mainLayout->addWidget(new SubActivityControl(this), 4, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 5, 0, 1, 2, 0);
    mainLayout->addWidget(new QLabel("Produziertes Produkt:"), 6, 0, 1, 1, 0);
    mainLayout->addWidget(new QLabel("Arbeitshöhe [cm]:"), 7, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxWorkingHeight, 7, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel("Abstand [cm]:"), 8, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxDistance, 8, 1, 1, 1, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 9, 0, 1, 2, 0);
    mainLayout->addWidget(valConGrabType, 10, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 11, 0, 1, 2, 0);
    mainLayout->addWidget(new QLabel("Impulsintensität:"), 12, 0, 1, 1, 0);
    mainLayout->addWidget(oscImpulseIntensity, 12, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel("Impulsanzahl:"), 13, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxImpulseCount, 13, 1, 1, 1, 0);

    this->setLayout(mainLayout);

}
