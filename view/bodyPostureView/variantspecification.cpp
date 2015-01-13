#include "variantspecification.h"

VariantSpecification::VariantSpecification(QWidget *parent) :
    QWidget(parent),
    mainContent(new QVBoxLayout)
{
   speciBtns = QVector<SelectableValueButton*>();
    this->setLayout(mainContent);
}


void VariantSpecification::addSpecification(const QString &name, int id, int value){
    SelectableValueButton *btn = new SelectableValueButton(id, value, this);
    btn->setText(name);
    mainContent->addWidget(btn);
    connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(btnSpeciClicked(int)));
}

void VariantSpecification::btnSpeciClicked(int id){
    if(selCurBtn != NULL)
        selCurBtn->setSelected(false);
    selCurBtn = getSpeciBtnByID(id);
    selCurBtn->setSelected(true);
}


int VariantSpecification::getValue(int id){
    return getSpeciBtnByID(id)->getValue().toInt();
}

int VariantSpecification::getSelectedID() const{
    if(selCurBtn != NULL)
        return selCurBtn->getID();
}

SelectableValueButton* VariantSpecification::getSpeciBtnByID(int id){
    for(int i = 0; i < speciBtns.length(); ++i){
        if(speciBtns.at(i)->getID() == id){
            return speciBtns.at(i);
        }
    }
}

void VariantSpecification::setSelected(int id){
    btnSpeciClicked(id);
}

