#ifndef IPRODUCTLIST_H
#define IPRODUCTLIST_H

#include <QtPlugin>

class IProductList{

signals:
    virtual void createProduct(QHash<QString, QVariant> values) = 0;
    virtual void deleteProduct(int id) = 0;

public slots:
    virtual void addProduct(QHash<QString, QVariant> values) = 0;
    virtual void updateProduct(QHash<QString, QVariant> values) = 0;
    virtual void removeProduct(int id) = 0;
    virtual void clearProducts() = 0;
};

#define IProductList_iid "IProductList"

Q_DECLARE_INTERFACE(IProductList, IProductList_iid)

#endif // IPRODUCTLIST_H
