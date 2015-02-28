#include "activitypopup.h"
#include "../view/flickcharm.h"
#include "../view/detailedlistitem.h"


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
    QGridLayout *mainLayout = new QGridLayout;

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

    mainLayout->addWidget(lblActivityDescription, 0, 0, 1, 1, 0);
    mainLayout->addWidget(txtBxActivityDescription, 0, 1, 1, 1, 0);
    mainLayout->addWidget(lblActivityRepetitions, 1, 0, 1, 1, 0);
    mainLayout->addWidget(numBxActivityRepetitions, 1, 1, 1, 1, 0);
    mainLayout->addWidget(scProducts, 2, 0, 1, 2, 0);

    setLayout(mainLayout);
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
    DetailedListItem *newListItem = new DetailedListItem(0, "productIcon", name, productItemScheme, false, true, false, false, false);
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
