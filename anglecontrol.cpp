#include "anglecontrol.h"
#include <QHBoxLayout>
#include "seperator.h"

AngleControl::AngleControl(QString* descVarConText, Variant* variant, VariantSpecification* varSpeci, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* mainVLayout = new QVBoxLayout;
    mainHLayout = new QHBoxLayout;
    subVariantsLayout = new QVBoxLayout;

    this->variantCon = new VariantCon(descVarConText, this);
    this->variantCon->setVariantSpecification(varSpeci);

    this->ownCons = new QVector<OwnCon*>();
    this->ownCons->append(new OwnCon(this));

    this->ownConSeperator = new QVector<Seperator*>();

    this->addVariant(variant);
    this->selectedVariantChanged(0);

    connect(variantCon, SIGNAL(selectedVariantChanged(int)), this, SLOT(selectedVariantChanged(int)));


    mainHLayout->addWidget(variantCon, 0, Qt::AlignTop);
    mainHLayout->addWidget(new Seperator(Qt::Vertical, 3, this));
    subVariantsLayout->addWidget(ownCons->at(0));
    mainHLayout->addLayout(subVariantsLayout);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->addWidget(new Seperator(Qt::Horizontal, 3, this));
    this->setLayout(mainVLayout);
}

void AngleControl::addVariant(Variant* variant){
    this->variantCon->addVariant(variant);
}

void AngleControl::selectedVariantChanged(int id){
    Variant* v = this->variantCon->getVariantByID(id);
    std::vector<SubVariant*>* subVariants = v->getSubVariants();
    int svSize = subVariants->size();
    int ocSize = ownCons->size();
    for(int i = 0; i < svSize; i++){
        if(i >= ocSize){
            this->ownCons->append(new OwnCon(this));
            Seperator* sep = new Seperator(Qt::Horizontal, 3, this);
            this->ownConSeperator->append(sep);
            subVariantsLayout->addWidget(sep);
            subVariantsLayout->addWidget(ownCons->at(i));
        }
        SubVariant *sv = subVariants->at(i);
        this->ownCons->at(i)->setValues(sv->getMin(), sv->getMax(), sv->getBtnValues(), sv->getIconPath());
        this->ownCons->at(i)->setText((*sv->getDescription()));
    }

    for(int i = subVariants->size(); i < ownCons->size();){
        subVariantsLayout->removeWidget(ownCons->at(i));
        ownCons->at(i)->setParent(NULL);
        ownCons->remove(i);
        subVariantsLayout->removeWidget(ownConSeperator->at(i-1));
        ownConSeperator->at(i-1)->setParent(NULL);
        ownConSeperator->remove(i-1);
    }
}

void AngleControl::selectVariant(int id){
    variantCon->selectID(id);
}

