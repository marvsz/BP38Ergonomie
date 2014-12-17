#include "generalexecutioncondition.h"
#include "separator.h"
#include "subactivitycontrol.h"
#include "numberlineedit.h"
#include <QGuiApplication>

GeneralExecutionCondition::GeneralExecutionCondition(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QGridLayout),
    txtbxDescription(new TextLineEdit(this)),
    valConMtmCode(new ValueControl(TEXT_CONTROL, this))
{
    mtmCodeTexts = new QVector<QString*>();
    mtmCodeValueTexts = new QVector<QString*>();
    (*mtmCodeTexts)<<new QString("Aufnehmen/Plazieren")<<new QString("Hilfsmittel handhaben")<<new QString("Platzieren")<<new QString("Betätigen")<<new QString("Körperbewegung");
    (*mtmCodeValueTexts)<<new QString("A")<<new QString("H")<<new QString("P")<<new QString("B")<<new QString("K"); 

    valConMtmCode->setValues(mtmCodeTexts, mtmCodeValueTexts, new QString(":/Icon/Icon/mtmCode/mtmCode_"));
    valConMtmCode->setText("MTM Code:");
    valConMtmCode->setTextHint("MTM Code des Arbeitsvorganges");

    txtbxDescription->setPlaceholderText("Beschreibung des Arbeitsvorganges");

    mainLayout->addWidget(new QLabel("Beschreibung:"), 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxDescription, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 1, 0, 1, 2, 0);
    mainLayout->addWidget(valConMtmCode, 2, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 3, 0, 1, 2, 0);
    mainLayout->addWidget(new SubActivityControl(this), 4, 0, 1, 2, 0);

    this->setLayout(mainLayout);


}
