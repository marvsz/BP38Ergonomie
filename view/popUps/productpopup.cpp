#include "productpopup.h"

ProductPopUp::ProductPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Create product"), parent),
    txtBxName(new TextLineEdit()),
    txtBxNumber(new TextLineEdit()),
    numBxTotalPercentage(new NumberLineEdit())
{
    txtBxName->setPlaceholderText(tr("Name"));
    txtBxNumber->setPlaceholderText(tr("Product Number"));
    numBxTotalPercentage->setPlaceholderText(tr("Total Percentage"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel(tr("Name:")), 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxName, 0, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Product Number:")), 1, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxNumber, 1, 1, 1, 1, 0);
    mainLayout->addWidget(new QLabel(tr("Total Percentage:")), 2, 0, 1, 1, 0);
    mainLayout->addWidget(numBxTotalPercentage, 2, 1, 1, 1, 0);

    setLayout(mainLayout);
}

ProductPopUp::~ProductPopUp(){

}

// PUBLIC SLOTS

void ProductPopUp::onEnter(){
    txtBxName->clear();
    txtBxNumber->clear();
    numBxTotalPercentage->clear();
}
// GETTER

QString ProductPopUp::getName() const{
    return txtBxName->text();
}

QString ProductPopUp::getNumber() const{
    return txtBxNumber->text();
}

int ProductPopUp::getTotalPercentage() const{
    return numBxTotalPercentage->getValue();
}


