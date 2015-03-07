#include "activitypopup.h"
#include "../flickcharm.h"
#include "../detailedlistitem.h"


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

    productListLayout->setAlignment(Qt::AlignTop);
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
void ActivityPopUp::addProduct(QHash<QString, QVariant> values){
    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_PRODUCT_NUMBER).toString());
    DetailedListItem *newListItem = new DetailedListItem(this, "productIcon", values.value(DBConstants::COL_PRODUCT_NAME), productItemScheme, false, true, false, false, false);
    newListItem->setValues(dliValues);
    newListItem->setID(values.value(DBConstants::COL_PRODUCT_ID).toInt());
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedProductChanged(int)));
    connect(this, SIGNAL(selectedProduct(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    productListLayout->addWidget(newListItem);
}

void ActivityPopUp::updateProduct(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int id = values.value(DBConstants::COL_PRODUCT_ID).toInt();
    int i = 0;
    while((item = productListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_PRODUCT_NUMBER).toString());
            dli->setName(values.value(DBConstants::COL_PRODUCT_NAME));
            dli->setValues(dliValues);
            break;
        }
        i++;
    }
}

void ActivityPopUp::removeProduct(int id){
    QLayoutItem *item;
    int id = values.value(DBConstants::COL_PRODUCT_ID).toInt();
    int i = 0;
    while((item = productListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_PRODUCT_NUMBER).toString());
            dli->setName(values.value(DBConstants::COL_PRODUCT_NAME));
            dli->setValues(dliValues);
            break;
        }
        i++;
    }
}

void ActivityPopUp::clearProducts(){
    QLayoutItem *item;
    while((item = productListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}


void ActivityPopUp::setActivity(const QString &description, int repetitions, int selectedProductID){
    txtBxActivityDescription->setText(description);
    numBxActivityRepetitions->setValue(repetitions);
    this->selectedProductID = selectedProductID;
}

void ActivityPopUp::setSelectedProduct(int id){
    selectedProductChanged(id);
}

// PRIVATE SLOTS
void ActivityPopUp::selectedProductChanged(int id){
    selectedProductID = id;
    emit selectedProduct(id);
}

void ActivityPopUp::onConfirm(){

}

void ActivityPopUp::onCancel(){

}

void ActivityPopUp::onClose(){
    txtBxActivityDescription->clear();
    numBxActivityRepetitions->clear();
}
