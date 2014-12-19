#include "anglecontrol.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QDebug>
#include "separator.h"

AngleControl::AngleControl(QString* descVarConText, Variant* variant, VariantSpecification* varSpeci, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* mainVLayout = new QVBoxLayout;
    QHBoxLayout* firstLineLayout = new QHBoxLayout;
    content = new QWidget(this);
    mainHLayout = new QHBoxLayout;
    subVariantsLayout = new QVBoxLayout;

    btnDescription = new QPushButton(this);
    btnDescription->setText((*descVarConText));
    btnDescription->setMinimumWidth(100);
    connect(btnDescription, SIGNAL(clicked()), this, SLOT(showHideBtnPressed()));

    this->variantCon = new VariantCon(this);
    this->variantCon->setVariantSpecification(varSpeci);

    this->valueControls = new QVector<ValueControl*>();
    this->valueControls->append(new ValueControl(VALUE_CONTROL, this));

    this->ownConSeparator = new QVector<Separator*>();

    this->addVariant(variant);

    connect(variantCon, SIGNAL(selectedVariantChanged(int)), this, SLOT(selectedVariantChanged(int)));


    mainHLayout->addWidget(variantCon, 0, Qt::AlignTop);
    mainHLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    subVariantsLayout->addWidget(valueControls->at(0));
    mainHLayout->addLayout(subVariantsLayout);

    firstLineLayout->addWidget(btnDescription, 0, Qt::AlignLeft);
    firstLineLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));

    mainVLayout->addLayout(firstLineLayout);
    mainVLayout->addWidget(content);
    mainVLayout->addWidget(new Separator(Qt::Horizontal, 3, this));

    content->setLayout(mainHLayout);
    this->setLayout(mainVLayout);
}

void AngleControl::addVariant(Variant* variant){
    this->variantCon->addVariant(variant);
}

void AngleControl::selectedVariantChanged(int id){
    Variant* v = this->variantCon->getVariantByID(id);
    std::vector<SubVariant*>* subVariants = v->getSubVariants();
    int svSize = subVariants->size();
    for(int i = 0; i < svSize; ++i){
        SubVariant *sv = subVariants->at(i);
        VariantControl controlType = sv->getControlType();
        if(i >= valueControls->size()){
            valueControls->append(new ValueControl(controlType, this));
            if(i != 0){
                Separator* sep = new Separator(Qt::Horizontal, 3, this);
                this->ownConSeparator->append(sep);
                subVariantsLayout->addWidget(sep);
            }
            subVariantsLayout->addWidget(valueControls->at(i));
        }
        else if(valueControls->at(i)->getControlType() != controlType){
            subVariantsLayout->removeWidget(valueControls->at(i));
            valueControls->at(i)->setParent(NULL);
            valueControls->remove(i);
            if(i < ownConSeparator->size()){
                subVariantsLayout->removeWidget(ownConSeparator->at(i));
                ownConSeparator->at(i)->setParent(NULL);
                ownConSeparator->remove(i);
            }
            i--;
            continue;
        }
        if(controlType == VALUE_CONTROL) {
            valueControls->at(i)->setValues(sv->getMin(), sv->getMax(), sv->getBtnValues(), sv->getIconPath());
            valueControls->at(i)->setUnit("°");
        }
        else
            valueControls->at(i)->setValues(sv->getShowText(), sv->getBtnTexts(), sv->getBtnTexts(), sv->getIconPath());

        valueControls->at(i)->setText((*sv->getDescription()));
    }

    for(int i = subVariants->size(); i < valueControls->size();){
        subVariantsLayout->removeWidget(valueControls->at(i));
        valueControls->at(i)->setParent(NULL);
        valueControls->remove(i);
        subVariantsLayout->removeWidget(ownConSeparator->at(i-1));
        ownConSeparator->at(i-1)->setParent(NULL);
        ownConSeparator->remove(i-1);
    }
}

void AngleControl::selectVariant(int id){
    variantCon->selectID(id);
}

void AngleControl::showHideBtnPressed(){
    if(content->isHidden()){
        this->showContent();
        emit contentIsShown();
    }
    else {
        this->hideContent();
        emit contentIsHidden();
    }
}

void AngleControl::showContent(){
    content->show();
}

void AngleControl::hideContent(){
    content->hide();
}

void AngleControl::selectSpecification(int id){
    variantCon->selectSpecification(id);
}

