#include "linepopup.h"
#include <QGridLayout>
#include "../../databaseHandler/dbconstants.h"

LinePopUp::LinePopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Edit Line"), parent),
    txtBxName(new TextLineEdit(this)),
    numBxWorkplaceCount(new NumberLineEdit(this)),
    txtBxDescription(new TextEdit(this))
{
    connect(this, SIGNAL(confirm()), this, SLOT(onConfirm()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel(tr("Name:")), 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxName, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Workplace count:")), 1, 0, 1, 1, 0);
    mainLayout->addWidget(numBxWorkplaceCount, 1, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Description:")), 2, 0, 1, 2, 0);
    mainLayout->addWidget(txtBxDescription, 3, 0, 1, 2, 0);
    setLayout(mainLayout);
}

// PUBLIC SLOTS
void LinePopUp::setLine(QHash<QString, QVariant> values){
    id = values.value(DBConstants::COL_LINE_ID).toInt();
    txtBxName->setText(values.value(DBConstants::COL_LINE_NAME).toString());
    numBxWorkplaceCount->setValue(values.value(DBConstants::COL_LINE_NUMBER_OF_WORKPLACES).toInt());
    txtBxDescription->setText(values.value(DBConstants::COL_LINE_DESCRIPTION).toString());
}

// PRIVATE SLOTS
void LinePopUp::onConfirm(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_LINE_ID, id);
    values.insert(DBConstants::COL_LINE_NAME, txtBxName->text());
    values.insert(DBConstants::COL_LINE_NUMBER_OF_WORKPLACES, numBxWorkplaceCount->getValue());
    values.insert(DBConstants::COL_LINE_DESCRIPTION, txtBxDescription->toPlainText());
    emit saveLine(values);
    emit closePopUp();
}
