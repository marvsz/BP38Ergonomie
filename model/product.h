#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
public:
    Product(QString* productName, int* productNumber, int* productionPercentage);
    ~Product();

    void setProductName(QString* pna);
    void setProductNumber(int* pnu);
    void seProductionPercentage(int ppe);

private:
    QString* productName;
    int* productNumber;
    int* productionPercentage;
};

#endif // PRODUCT_H
