#include "createproductpopup.h"

CreateProductPopUp::CreateProductPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Create product"), parent),
    txtBxName(new TextLineEdit()),
    txtBxNumber(new TextLineEdit()),
    numBxTotalPercentage(new NumberLineEdit())
{
    txtBxName->setPlaceholderText(tr("Name"));
    txtBxNumber->setPlaceholderText(tr("Product Number"));
    numBxTotalPercentage->setPlaceholderText(tr("Total Percentage"));

    connect(this, SIGNAL(cancel()), this, SLOT(onClose()));
    connect(this, SIGNAL(confirm()), this, SLOT(onConfirm()));

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

CreateProductPopUp::~CreateProductPopUp(){

}

// PRIVATE SLOTS
void CreateProductPopUp::onConfirm(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_PRODUCT_NAME, txtBxName->text());
    values.insert(DBConstants::COL_PRODUCT_NUMBER, txtBxNumber->text());
    values.insert(DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE, numBxTotalPercentage->getValue());
    emit saveProduct(values);
    onClose();
}

void CreateProductPopUp::onClose(){
    txtBxName->clear();
    txtBxNumber->clear();
    numBxTotalPercentage->clear();
    emit closePopUp();
}

