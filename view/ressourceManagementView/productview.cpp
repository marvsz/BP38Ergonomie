#include "productview.h"
#include "separator.h"
#include <QGridLayout>
#include <QDebug>
#include "detailedlistitem.h"
#include "flickcharm.h"

const QList<QStringList> ProductView::productItemScheme = QList<QStringList>() << (QStringList() << tr("product number")) << (QStringList()<< tr("total percentage"));

ProductView::ProductView(QWidget *parent) : QWidget(parent),
    scProducts(new QScrollArea),
    lblAddProduct(new QLabel(tr("Add Product"))),
    lblViewName(new QLabel(tr("product data"))),
    lblName(new QLabel(tr("product name:"))),
    lblNumber(new QLabel(tr("product number:"))),
    lblTotalPercentage(new QLabel(tr("percentage of the whole production:"))),
    txtBxName(new TextLineEdit()),
    txtBxNumber(new TextLineEdit()),
    numBxTotalPercentage(new NumberLineEdit()),
    btnBack(new QPushButton()),
    btnAdd(new QPushButton()),
    productListLayout(new QVBoxLayout)

{
    btnBack->setObjectName("leftIcon");
    btnBack->setFixedSize(45, 45);
    btnAdd->setObjectName("plusIcon");
    btnAdd->setFixedSize(45, 45);
    connect(btnBack, SIGNAL(clicked()), this, SIGNAL(back()));
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));

    lblAddProduct->setObjectName("lblHeader");
    txtBxName->setPlaceholderText(tr("name of the product"));
    txtBxNumber->setPlaceholderText(tr("number of the product"));
    numBxTotalPercentage->setPlaceholderText(tr("percentage of total production"));

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, Qt::AlignRight);

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
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(productDataLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addWidget(scProducts);

    setLayout(mainLayout);

    // TEST DATA
    addProduct(1, "Test Produkt 1", "MX123", 50);
    addProduct(2, "Test Produkt 2", "MX1321", 10);
    addProduct(3, "Test Produkt 3", "MG$123", 10);
    addProduct(4, "Test Produkt 4", "Mfasdo23", 10);
    addProduct(5, "Test Produkt 5", "YOLO42", 20);
}

ProductView::~ProductView()
{

}

//PUBLIC SLOTS
void ProductView::setProduct(const QString &name, const QString &number, int totalPercentage){
    txtBxName->setText(name);
    txtBxNumber->setText(number);
    numBxTotalPercentage->setValue(totalPercentage);
}

void ProductView::addProduct(int id, const QString &name, const QString &productNumber, int totalPercentage){
    DetailedListItem *newListItem = new DetailedListItem(0, "", name, productItemScheme, true, false, false);
    newListItem->setID(id);
    QList<QStringList> values = QList<QStringList>() << (QStringList() << productNumber) << (QStringList() << QString::number(totalPercentage));
    newListItem->setValues(values);
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteProduct(int)));
    productListLayout->addWidget(newListItem);

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
    emit saveProduct();
    txtBxName->clear();
    txtBxNumber->clear();
    numBxTotalPercentage->clear();
}

//GETTER
QString ProductView::getName() const{
    return txtBxName->text();
}
QString ProductView::getNumber() const{
    return txtBxNumber->text();
}
int ProductView::getTotalPercentage() const{
    return numBxTotalPercentage->getValue();
}
