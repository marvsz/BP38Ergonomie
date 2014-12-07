#include "product.h"

Product::Product(TextField* productName, NumberField* productNumber, NumberField* productoinPercentage)
{
    this->productName=productName;
    this->productNumber=productNumber;
    this->productoinPercentage=productoinPercentage;
}
