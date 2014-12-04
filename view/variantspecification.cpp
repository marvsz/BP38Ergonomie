#include "variantspecification.h"

VariantSpecification::VariantSpecification()
{
    this->speciDescs = new QVector<QString*>();
}

void VariantSpecification::addSpezification(QString* desc){
    speciDescs->append(desc);
}

QVector<QString*>* VariantSpecification::getSpecificationDesc(){
    return speciDescs;
}
