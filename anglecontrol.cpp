#include "anglecontrol.h"
#include <QHBoxLayout>

AngleControl::AngleControl(QString* descVarConText, Variant* variant, VariantSpecification* varSpeci, QWidget *parent) :
    QWidget(parent)
{
    mainLayout = new QHBoxLayout;
    subVariantsLayout = new QVBoxLayout;

    this->variantCon = new VariantCon(descVarConText, this);
    this->variantCon->setVariantSpecification(varSpeci);

    this->ownCons = new QVector<OwnCon*>();
    this->ownCons->append(new OwnCon(this));

    this->ownConSeperator = new QVector<QWidget*>();

    this->addVariant(variant);
    this->selectedVariantChanged(0);

    connect(variantCon, SIGNAL(selectedVariantChanged(int)), this, SLOT(selectedVariantChanged(int)));


    mainLayout->addWidget(variantCon, 0, Qt::AlignTop);
    QWidget *vSep = new QWidget(this);
    vSep->setStyleSheet("QWidget {background-color: #c8c7cc;border: 1px solid #c8c7cc; border-radius: 2px; margin: 10px 10px 10px 10px}");
    vSep->setFixedWidth(3);
    vSep->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    mainLayout->addWidget(vSep);
    subVariantsLayout->addWidget(ownCons->at(0));
    mainLayout->addLayout(subVariantsLayout);
    this->setLayout(mainLayout);
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
            QWidget *hSep = new QWidget(this);
            hSep->setStyleSheet("QWidget {background-color: #c8c7cc;border: 1px solid #c8c7cc; border-radius: 2px; margin: 10px 10px 10px 10px}");
            hSep->setFixedHeight(3);
            hSep->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            this->ownConSeperator->append(hSep);
            subVariantsLayout->addWidget(hSep);
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

