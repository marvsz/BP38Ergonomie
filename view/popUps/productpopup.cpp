#include "productpopup.h"
#include <QVBoxLayout>

ProductPopUp::ProductPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Create product"), parent),
    txtBxName(new TextLineEdit()),
    txtBxNumber(new TextLineEdit()),
    numBxTotalPercentage(new NumberLineEdit())
{
    txtBxName->setPlaceholderText(tr("Name"));
    txtBxNumber->setPlaceholderText(tr("Product Number"));
    numBxTotalPercentage->setPlaceholderText(tr("Total Percentage"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel(tr("Name:")));
    mainLayout->addWidget(txtBxName);
    mainLayout->addWidget(new QLabel(tr("Product Number:")));
    mainLayout->addWidget(txtBxNumber);
    mainLayout->addWidget(new QLabel(tr("Total Percentage:")));
    mainLayout->addWidget(numBxTotalPercentage);

    setLayout(mainLayout);
}

ProductPopUp::~ProductPopUp(){

}

// PUBLIC SLOTS

void ProductPopUp::onEnter(){
    txtBxName->setText("");
    txtBxNumber->setText("");
    numBxTotalPercentage->setText("");
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


