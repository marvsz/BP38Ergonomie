#include "variant.h"

Variant::Variant(QString *desc, SubVariant *subVariant){
    this->desc = desc;
    this->subVariants = new std::vector<SubVariant*>();
    this->addSubVariant(subVariant);
}

Variant::~Variant(){
    for(unsigned int i = 0; i < subVariants->size(); i++)
        delete subVariants->at(i);
    delete subVariants;
}

QString* Variant::getDescription() const{
    return this->desc;
}
std::vector<SubVariant*>* Variant::getSubVariants() const{
    return this->subVariants;
}
void Variant::addSubVariant(SubVariant* subVariant){
    subVariants->push_back(subVariant);
}
