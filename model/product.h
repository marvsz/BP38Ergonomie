#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
public:
    Product(QString* productName, int* productNumber, int* productoinPercentage);
    ~Product();

private:
    QString* productName;
    int* productNumber;
    int* productoinPercentage;
};

#endif // PRODUCT_H
