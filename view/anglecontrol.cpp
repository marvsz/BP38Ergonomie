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

    this->descLbl = new QLabel(this);
    descLbl->setText((*descVarConText));

    this->variantCon = new VariantCon(this);
    this->variantCon->setVariantSpecification(varSpeci);

    this->valueControls = new QVector<ValueControl*>();
    this->valueControls->append(new ValueControl(VALUE_CONTROL, this));

    this->ownConSeparator = new QVector<Separator*>();

    this->showHideBtn = new QPushButton(this);
    this->showHideBtn->setText("-");
    this->showHideBtn->setMinimumSize(40,40);
    connect(showHideBtn, SIGNAL(pressed()), this, SLOT(showHideBtnPressed()));

    this->addVariant(variant);

    connect(variantCon, SIGNAL(selectedVariantChanged(int)), this, SLOT(selectedVariantChanged(int)));


    mainHLayout->addWidget(variantCon, 0, Qt::AlignTop);
    mainHLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    subVariantsLayout->addWidget(valueControls->at(0));
    mainHLayout->addLayout(subVariantsLayout);

    firstLineLayout->addWidget(descLbl, 0, Qt::AlignLeft);
    firstLineLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));
    firstLineLayout->addWidget(showHideBtn, 0, Qt::AlignRight);

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
            valueControls->at(i)->setValues(sv->getBtnTexts(), sv->getIconPath());

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
    if(showHideBtn->text().compare(QString("+"), Qt::CaseSensitive) == 0)
        this->showContent();
    else
        this->hideContent();
}

void AngleControl::showContent(){
    content->show();
    this->showHideBtn->setText("-");
    QApplication::processEvents();
}

void AngleControl::hideContent(){
    content->hide();
    this->showHideBtn->setText("+");
    QApplication::processEvents();
}

