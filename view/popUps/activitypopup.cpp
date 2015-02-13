#include "activitypopup.h"
#include "../view/flickcharm.h"
#include "../view/detailedlistitem.h"
#include "../view/iconconstants.h"

ActivityPopUp::ActivityPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Edit Activity"), parent),
    productListLayout(new QVBoxLayout),
    productListContent(new QWidget()),
    scProducts(new QScrollArea()),
    lblActivityDescription(new QLabel(tr("Description:"))),
    lblActivityRepetitions(new QLabel(tr("Repetitions:"))),
    lblChooseProduct(new QLabel(tr("Choose Product"))),
    txtBxActivityDescription(new TextLineEdit()),
    numBxActivityRepetitions(new NumberLineEdit())
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    productListLayout->setAlignment(Qt::AlignCenter);
    scProducts->setWidget(productListContent);
    scProducts->setWidgetResizable(true);
    scProducts->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scProducts->setObjectName("saBordered");
    scProducts->setMinimumSize(700, 300);
    productListContent->setLayout(productListLayout);

    FlickCharm *flickCharmProducts = new FlickCharm(this);
    flickCharmProducts->activateOn(scProducts);

    txtBxActivityDescription->setPlaceholderText(tr("description"));
    numBxActivityRepetitions->setPlaceholderText(tr("amout of repetitions"));
    lblChooseProduct->setObjectName("lblHeader");

    mainLayout->addWidget(lblActivityDescription);
    mainLayout->addWidget(txtBxActivityDescription);
    mainLayout->addWidget(lblActivityRepetitions);
    mainLayout->addWidget(numBxActivityRepetitions);
    mainLayout->addWidget(scProducts);

    setLayout(mainLayout);

    addProduct(0, "Produkt 1", "ABCD1234");
    addProduct(1, "Produkt 2", "ABCD1234");
    addProduct(2, "Produkt 3", "ABCD1234");
    addProduct(3, "Produkt 4", "ABCD1234");
    addProduct(0, "Produkt 1", "ABCD1234");
    addProduct(1, "Produkt 2", "ABCD1234");
    addProduct(2, "Produkt 3", "ABCD1234");
    addProduct(3, "Produkt 4", "ABCD1234");

}

ActivityPopUp::~ActivityPopUp(){
}

// GETTER
QString ActivityPopUp::getDescription() const{
    return txtBxActivityDescription->text();
}

int ActivityPopUp::getRepetitions() const{
    return numBxActivityRepetitions->getValue();
}

int ActivityPopUp::getSelectedProduct() const{
    return selectedProductID;
}


// PUBLIC SLOTS
void ActivityPopUp::setActivity(const QString &description, int repetitions, int selectedProductID){
    txtBxActivityDescription->setText(description);
    numBxActivityRepetitions->setValue(repetitions);
    this->selectedProductID = selectedProductID;
}

void ActivityPopUp::addProduct(int id, const QString &name, const QString &productNumber){
    DetailedListItem *newListItem = new DetailedListItem(0, IconConstants::ICON_PRODUCT, name, productItemScheme, false, true, false, false, false);
    newListItem->setID(id);
    QList<QStringList> values = QList<QStringList>() << (QStringList() << productNumber);
    newListItem->setValues(values);
    newListItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedProductChanged(int)));
    connect(this, SIGNAL(selectedProduct(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    productListLayout->addWidget(newListItem);
}
void ActivityPopUp::clearProducts(){
    QLayoutItem *item;
    while((item = productListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}
void ActivityPopUp::setSelectedProduct(int id){
    selectedProductChanged(id);
}

// PRIVATE SLOTs
void ActivityPopUp::selectedProductChanged(int id){
    selectedProductID = id;
    emit selectedProduct(id);
}
