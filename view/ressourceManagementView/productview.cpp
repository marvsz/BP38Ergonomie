#include "productview.h"
#include "separator.h"
#include <QGridLayout>
#include <QDebug>
#include "detailedlistitem.h"
#include "flickcharm.h"

ProductView::ProductView(QWidget *parent) : QWidget(parent),
    scProducts(new QScrollArea),
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
    btnAdd->setFixedSize(45, 45
                         );
    connect(btnBack, SIGNAL(clicked()), this, SLOT(btnBackClicked()));
    connect(btnAdd, SIGNAL(clicked()), this, SIGNAL(saveProduct()));

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, Qt::AlignRight);

    QGridLayout *productDataLayout = new QGridLayout;
    productDataLayout->addWidget(lblName, 0, 0, 1, 1, 0);
    productDataLayout->addWidget(txtBxName, 0, 1, 1, 1, 0);
    productDataLayout->addWidget(lblNumber, 0, 2, 1, 1, 0);
    productDataLayout->addWidget(txtBxNumber, 0, 3, 1, 1, 0);
    productDataLayout->addWidget(lblTotalPercentage, 1, 0, 1, 1, 0);
    productDataLayout->addWidget(numBxTotalPercentage, 1, 1, 1, 1, 0);
    productDataLayout->addWidget(btnAdd, 1, 3, 1, 1, 0);

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
    mainLayout->addWidget(scProducts);

    setLayout(mainLayout);
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

void ProductView::addProduct(int id, const QString &name){
    DetailedListItem *newListItem = new DetailedListItem(0, "", name, QList<QStringList>(), true, true, false);
    newListItem->setID(id);
    idSelectionMap.insert(id, false);
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteProduct(int)));
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(idSelected(int)));
    connect(newListItem, SIGNAL(deselected(int)), this, SLOT(idDeselected(int)));
    connect(this, SIGNAL(productSelected(int)), newListItem, SLOT(select(int)));
    productListLayout->addWidget(newListItem);

}

void ProductView::clearProducts(){
    QLayoutItem *item;
    while((item = productListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
    idSelectionMap.clear();
}

void ProductView::setProductSelected(int id){
    idSelectionMap.insert(id, true);
    emit productSelected(id);
}


//PRIVATE SLOTS
void ProductView::btnBackClicked(){
    emit saveSelectedProducts();
    emit back();
}

void ProductView::idSelected(int id){
    idSelectionMap.insert(id, true);
}

void ProductView::idDeselected(int id){
    idSelectionMap.insert(id, false);
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

QList<int> ProductView::getSelectedIDs() const {
    QList<int> list;
    foreach(int id, idSelectionMap.keys())
        if(idSelectionMap.value(id) == true)
            list << id;
    return list;
}
