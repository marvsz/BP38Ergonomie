#ifndef IPRODUCT_H
#define IPRODUCT_H

#include <QtPlugin>

class IProduct {

public slots:
    virtual void setProduct(QHash<QString, QVariant> values) = 0;

signals:
    virtual void saveProduct(QHash<QString, QVariant> values) = 0;
};

#define IProduct_iid "IProduct"
Q_DECLARE_INTERFACE(IProduct, IProduct_iid)

#endif // IPRODUCT_H
