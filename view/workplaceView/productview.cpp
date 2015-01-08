#include "productview.h"
#include "separator.h"
#include <QGridLayout>
#include "detailedlistitem.h"

ProductView::ProductView(QWidget *parent) : QWidget(parent),
    lblViewName(new QLabel("Produktdaten")),
    lblName(new QLabel("Produktname:")),
    lblNumber(new QLabel("Produktnummer:")),
    lblTotalPercentage(new QLabel("Prozent der Gesamtproduktion:")),
    txtBxName(new TextLineEdit()),
    txtBxNumber(new TextLineEdit()),
    numBxTotalPercentage(new NumberLineEdit()),
    btnBack(new QPushButton("Zurück")),
    btnAdd(new QPushButton("Hinzufügen")),
    productListLayout(new QVBoxLayout)
{
    btnBack->setObjectName("btnNavigation");
    connect(btnBack, SIGNAL(clicked()), this, SLOT(btnBackClicked()));
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));

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

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(productDataLayout);
    mainLayout->addLayout(productListLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));

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
    connect(newListItem, SIGNAL(clicked()), newListItem, SLOT(changeSelection())),
    connect(newListItem, SIGNAL(deleteItem(int)), this, SLOT(deleteProductClicked(int)));
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

void ProductView::btnAddClicked(){
    emit saveProduct();
}

void ProductView::deleteProductClicked(int id){
    emit deleteProduct(id);
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
    foreach(int id, idSelectionMap)
        if(idSelectionMap.value(id))
            list << id;
    return list;
}
