#include "transporationpopup.h"
#include <QGridLayout>

TransporationPopUp::TransporationPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Create transportation"), parent),
    txtBxName(new TextLineEdit()),
    numBxWeight(new NumberLineEdit()),
    numBxMaxLoad(new NumberLineEdit()),
    oscFixedRoller(new OptionSelectionControl()),
    oscBrakes(new OptionSelectionControl())
{
    txtBxName->setPlaceholderText(tr("Name"));
    numBxWeight->setPlaceholderText(tr("Weight"));
    numBxMaxLoad->setPlaceholderText(tr("Maximum load"));


    oscFixedRoller->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscBrakes->setValues(YES_NO_TEXTS, YES_NO_VALUE);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel(tr("Name:")), 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxName, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Weight [kg]:")), 1, 0, 1, 1, 0);
    mainLayout->addWidget(numBxWeight, 1, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Maximum load [kg]:")), 2, 0, 1, 1, 0);
    mainLayout->addWidget(numBxMaxLoad, 2, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Fixed roller:")), 3, 0, 1, 1, 0);
    mainLayout->addWidget(oscFixedRoller, 3, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Brakes:")), 4, 0, 1, 1, 0);
    mainLayout->addWidget(oscBrakes, 4, 1, 1, 1, 0);

    setLayout(mainLayout);
}

TransporationPopUp::~TransporationPopUp()
{

}

//PUBLIC SLOTS
void TransporationPopUp::onEnter(){
    txtBxName->clear();
    numBxMaxLoad->clear();
    numBxWeight->clear();
    oscFixedRoller->setSelectedValue(1);
    oscBrakes->setSelectedValue(1);
}

// GETTER
QString TransporationPopUp::getName() const{
    return txtBxName->text();
}
int TransporationPopUp::getWeight() const{
    return numBxWeight->getValue();
}
int TransporationPopUp::getMaxLoad() const{
    return numBxMaxLoad->getValue();
}
bool TransporationPopUp::getHasFixedRoller() const{
    return oscFixedRoller->getSelectedValue().toBool();
}
bool TransporationPopUp::getHasBrakes() const{
    return oscBrakes->getSelectedValue().toBool();
}

