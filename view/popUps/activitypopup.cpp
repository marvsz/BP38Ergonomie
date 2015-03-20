#include "activitypopup.h"
#include "../flickcharm.h"
#include "../detailedlistitem.h"
#include "../../databaseHandler/dbconstants.h"

ActivityPopUp::ActivityPopUp(QWidget *parent) :
    AbstractPopUpWidget(ConfirmMode::ACCEPT, tr("Edit Activity"), parent),
    selectedProductID(0),
    productListLayout(new QVBoxLayout),
    productListContent(new QWidget()),
    scProducts(new QScrollArea()),
    lblActivityDescription(new QLabel(tr("Description:"))),
    lblActivityRepetitions(new QLabel(tr("Repetitions:"))),
    lblChooseProduct(new QLabel(tr("Choose Product"))),
    txtBxActivityDescription(new TextLineEdit()),
    numBxActivityRepetitions(new NumberLineEdit())
{
    connect(this, SIGNAL(confirm()), this, SLOT(onConfirm()));
    connect(this, SIGNAL(cancel()), this, SLOT(onClose()));

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


// PUBLIC SLOTS
void ActivityPopUp::addProduct(QHash<QString, QVariant> values){
    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_PRODUCT_NUMBER).toString());
    DetailedListItem *newListItem = new DetailedListItem(this, "productIcon", values.value(DBConstants::COL_PRODUCT_NAME).toString(), productItemScheme, false, true, false, false, false);
    newListItem->setValues(dliValues);
    newListItem->setID(values.value(DBConstants::COL_PRODUCT_ID).toInt());
    newListItem->setMaximumWidth(270);
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedProductChanged(int)));
    connect(newListItem, SIGNAL(deselected(int)), this, SLOT(deselectedProduct(int)));
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
            dli->setName(values.value(DBConstants::COL_PRODUCT_NAME).toString());
            dli->setValues(dliValues);
            break;
        }
        i++;
    }
}

void ActivityPopUp::removeProduct(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = productListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            productListLayout->removeItem(item);
            delete item->widget();
            delete item;
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


void ActivityPopUp::setActivity(QHash<QString, QVariant> values){
    id = values.value(DBConstants::COL_ACTIVITY_ID).toInt();
    txtBxActivityDescription->setText(values.value(DBConstants::COL_ACTIVITY_DESCRIPTION).toString());
    numBxActivityRepetitions->setValue(values.value(DBConstants::COL_ACTIVITY_REPETITIONS).toInt());
    selectedProductChanged(values.value(DBConstants::COL_ACTIVITY_PRODUCT_ID).toInt());
}

// PRIVATE SLOTS
void ActivityPopUp::selectedProductChanged(int id){
    selectedProductID = id;
    emit selectedProduct(id);
}

void ActivityPopUp::deselectedProduct(int id){
    if(selectedProductID == id)
        selectedProductID = 0;
}

void ActivityPopUp::onConfirm(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_ACTIVITY_ID, id);
    values.insert(DBConstants::COL_ACTIVITY_DESCRIPTION, txtBxActivityDescription->text());
    values.insert(DBConstants::COL_ACTIVITY_REPETITIONS, numBxActivityRepetitions->getValue());
    values.insert(DBConstants::COL_ACTIVITY_PRODUCT_ID, selectedProductID);
    emit saveActivity(values);
    onClose();
}

void ActivityPopUp::onClose(){
    emit closePopUp();
}
