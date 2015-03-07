#include "productview.h"
#include "../separator.h"
#include <QGridLayout>
#include <QDebug>
#include "../detailedlistitem.h"
#include "../flickcharm.h"
#include "../../databaseHandler/dbconstants.h"

ProductView::ProductView(QWidget *parent) : SimpleNavigateableWidget(tr("Products"),parent),
    scProducts(new QScrollArea),
    lblAddProduct(new QLabel(tr("Add Product"))),
    lblName(new QLabel(tr("Product name:"))),
    lblNumber(new QLabel(tr("Product number:"))),
    lblTotalPercentage(new QLabel(tr("Percentage of the whole production:"))),
    txtBxName(new TextLineEdit()),
    txtBxNumber(new TextLineEdit()),
    numBxTotalPercentage(new NumberLineEdit()),
    btnAdd(new QPushButton()),
    productListLayout(new QVBoxLayout)

{
    btnAdd->setObjectName("plusIcon");
    btnAdd->setFixedSize(45, 45);
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));

    lblAddProduct->setObjectName("lblHeader");
    txtBxName->setPlaceholderText(tr("name of the product"));
    txtBxNumber->setPlaceholderText(tr("number of the product"));
    numBxTotalPercentage->setPlaceholderText(tr("percentage of total production"));

    QGridLayout *productDataLayout = new QGridLayout;
    productDataLayout->addWidget(lblAddProduct, 0, 0, 1, 1, 0);
    productDataLayout->addWidget(lblName, 1, 0, 1, 1, 0);
    productDataLayout->addWidget(txtBxName, 1, 1, 1, 1, 0);
    productDataLayout->addWidget(lblNumber, 1, 2, 1, 1, 0);
    productDataLayout->addWidget(txtBxNumber, 1, 3, 1, 1, 0);
    productDataLayout->addWidget(lblTotalPercentage, 2, 0, 1, 1, 0);
    productDataLayout->addWidget(numBxTotalPercentage, 2, 1, 1, 1, 0);
    productDataLayout->addWidget(btnAdd, 2, 2, 1, 2, Qt::AlignCenter);

    QWidget *listContent = new QWidget;
    listContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scProducts->setWidget(listContent);
    scProducts->setWidgetResizable(true);
    listContent->setLayout(productListLayout);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scProducts);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(productDataLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addWidget(scProducts);

    productListLayout->setAlignment(Qt::AlignTop);

    setLayout(mainLayout);
}

ProductView::~ProductView()
{
}

void ProductView::addProduct(QHash<QString, QVariant> values){
    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_PRODUCT_NUMBER).toString()) << (QStringList() << values.value(DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE).toString());
    DetailedListItem *newListItem = new DetailedListItem(this, "productIcon", values.value(DBConstants::COL_PRODUCT_NAME).toString(), productItemScheme, true, false, false, false, false);
    newListItem->setValues(dliValues);
    newListItem->setID(values.value(DBConstants::COL_PRODUCT_ID).toInt());
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteProduct(int)));
    productListLayout->addWidget(newListItem);
}

void ProductView::updateProduct(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int id = values.value(DBConstants::COL_PRODUCT_ID).toInt();
    int i = 0;
    while((item = productListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_PRODUCT_NUMBER).toString()) << (QStringList() << values.value(DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE).toString());
            dli->setName(values.value(DBConstants::COL_PRODUCT_NAME).toString());
            dli->setValues(dliValues);
            break;
        }
        i++;
    }
}

void ProductView::removeProduct(int id){
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

void ProductView::clearProducts(){
    QLayoutItem *item;
    while((item = productListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

// PRIVATE SLOTS
void ProductView::btnAddClicked(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_PRODUCT_NAME, txtBxName->text());
    values.insert(DBConstants::COL_PRODUCT_NUMBER, txtBxNumber->text());
    values.insert(DBConstants::COL_PRODUCT_TOTAL_PERCENTAGE, numBxTotalPercentage->getValue());
    emit createProduct(values);
    txtBxName->clear();
    txtBxNumber->clear();
    numBxTotalPercentage->clear();
}


