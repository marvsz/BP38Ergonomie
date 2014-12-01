#include "anglecontrol.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QDebug>
#include "seperator.h"

AngleControl::AngleControl(QString* descVarConText, Variant* variant, VariantSpecification* varSpeci, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* mainVLayout = new QVBoxLayout;
    content = new QWidget(this);
    mainHLayout = new QHBoxLayout;
    subVariantsLayout = new QVBoxLayout;

    this->descLbl = new QLabel(this);
    descLbl->setText((*descVarConText));

    this->variantCon = new VariantCon(this);
    this->variantCon->setVariantSpecification(varSpeci);

    this->ownCons = new QVector<OwnCon*>();
    this->ownCons->append(new OwnCon(this));

    this->ownConSeperator = new QVector<Seperator*>();

    this->showHideBtn = new QPushButton(this);
    this->showHideBtn->setText("-");
    this->showHideBtn->setMinimumSize(40,40);
    connect(showHideBtn, SIGNAL(pressed()), this, SLOT(showHideBtnPressed()));

    this->addVariant(variant);
    this->selectedVariantChanged(0);

    connect(variantCon, SIGNAL(selectedVariantChanged(int)), this, SLOT(selectedVariantChanged(int)));


    mainHLayout->addWidget(variantCon, 0, Qt::AlignTop);
    mainHLayout->addWidget(new Seperator(Qt::Vertical, 3, this));
    subVariantsLayout->addWidget(ownCons->at(0));
    mainHLayout->addLayout(subVariantsLayout);
    mainVLayout->addWidget(descLbl);
    mainVLayout->addWidget(content);
    mainVLayout->addWidget(showHideBtn, 0 , Qt::AlignRight);
    mainVLayout->addWidget(new Seperator(Qt::Horizontal, 3, this));
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

void AngleControl::showHideBtnPressed(){
    if(showHideBtn->text().compare(QString("+"), Qt::CaseSensitive) == 0)
        this->showContent();
    else
        this->hideContent();
}

void AngleControl::showContent(){
    content->show();
    this->showHideBtn->setText("-");
    //this->setMinimumHeight(360*ownCons->length());
    QApplication::processEvents();
}

void AngleControl::hideContent(){
    content->hide();
    this->showHideBtn->setText("+");
    //this->setMinimumHeight(150);
    QApplication::processEvents();
}

