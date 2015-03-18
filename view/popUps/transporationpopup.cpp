#include "transporationpopup.h"
#include <QGridLayout>
#include "../../databaseHandler/dbconstants.h"

TransporationPopUp::TransporationPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Create transportation"), parent),
    txtBxName(new TextLineEdit()),
    numBxWeight(new NumberLineEdit()),
    numBxMaxLoad(new NumberLineEdit()),
    oscFixedRoller(new OptionSelectionControl()),
    oscBrakes(new OptionSelectionControl())
{
    connect(this, SIGNAL(confirm()), this, SLOT(onConfirm()));
    connect(this, SIGNAL(cancel()), this, SLOT(onClose()));
    txtBxName->setPlaceholderText(tr("Name"));
    numBxWeight->setPlaceholderText(tr("Weight"));
    numBxMaxLoad->setPlaceholderText(tr("Maximum load"));

    oscFixedRoller->setValues(YES_NO_TEXTS, YES_NO_VALUE);
    oscBrakes->setValues(YES_NO_TEXTS, YES_NO_VALUE);

    oscFixedRoller->setSelectedValue(1);
    oscBrakes->setSelectedValue(1);

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

// PRIVATE SLOTS
void TransporationPopUp::onConfirm(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_TRANSPORTATION_NAME, txtBxName->text());
    values.insert(DBConstants::COL_TRANSPORTATION_EMPTY_WEIGHT, numBxWeight->getValue());
    values.insert(DBConstants::COL_TRANSPORTATION_MAX_LOAD, numBxMaxLoad->getValue());
    values.insert(DBConstants::COL_TRANSPORTATION_FIXED_ROLLER, oscFixedRoller->getSelectedValue().toInt());
    values.insert(DBConstants::COL_TRANSPORTATION_BRAKES, oscBrakes->getSelectedValue().toInt());
    emit saveTransportation(values);
    onClose();
}

void TransporationPopUp::onClose(){
    txtBxName->clear();
    numBxWeight->clear();
    numBxMaxLoad->clear();
    oscFixedRoller->setSelectedValue(1);
    oscBrakes->setSelectedValue(1);
    emit closePopUp();
}

