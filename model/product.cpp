#include "product.h"

Product::Product(QString* productName, int* productNumber, int* productionPercentage)
{
    this->seProductionPercentage(productionPercentage);
    this->setProductName(productName);
    this->setProductNumber(productNumber);
}

Product::~Product(){

}

int* Product::getProductionPercentage(){
    return this->productionPercentage;
}

int* Product::getProductNumber(){
    return this->productNumber;
}

QString* Product::getProductName(){
    return this->productName;
}

void Product::seProductionPercentage(int* ppe){
    this->productionPercentage=ppe;
}

void Product::setProductName(QString* pna){
    this->productName=pna;
}

void Product::setProductNumber(int* pnu){
    this->productNumber=pnu;
}
