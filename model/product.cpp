#include "product.h"

Product::Product(QString* productName, int* productNumber, int* productionPercentage)
{
    this->productName=productName;
    this->productNumber=productNumber;
    this->productionPercentage=productionPercentage;
}
