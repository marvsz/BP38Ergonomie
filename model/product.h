#ifndef PRODUCT_H
#define PRODUCT_H

#import "textfield.h"
#import "numberfield.h"

class Product
{
public:
    Product(TextField* productName, NumberField* productNumber, NumberField* productoinPercentage);
    ~Product();

private:
    TextField* productName;
    NumberField* productNumber;
    NumberField* productoinPercentage;
};

#endif // PRODUCT_H
