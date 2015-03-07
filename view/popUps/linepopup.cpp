#include "linepopup.h"
#include <QGridLayout>

LinePopUp::LinePopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Edit Line"), parent),
    txtBxName(new TextLineEdit(this)),
    numBxWorkplaceCount(new NumberLineEdit(this)),
    txtBxDescription(new TextEdit(this))
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel(tr("Name:")), 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxName, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Workplace count:")), 1, 0, 1, 1, 0);
    mainLayout->addWidget(numBxWorkplaceCount, 1, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Description:")), 2, 0, 1, 2, 0);
    mainLayout->addWidget(txtBxDescription, 3, 0, 1, 2, 0);
    setLayout(mainLayout);
}
