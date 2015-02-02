#include "variantspecification.h"

VariantSpecification::VariantSpecification(QWidget *parent) :
    QWidget(parent),
    mainContent(new QVBoxLayout)
{
    selCurBtn = 0;
    speciBtns = QVector<SelectableValueButton*>();
    this->setLayout(mainContent);
}


void VariantSpecification::addSpecification(const QString &name, int id, int value){
    SelectableValueButton *btn = new SelectableValueButton(id, value, this);
    btn->setText(name);
    btn->setMinimumWidth(150);
    mainContent->addWidget(btn);
    speciBtns.append(btn);
    connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(btnSpeciClicked(int)));
}

void VariantSpecification::btnSpeciClicked(int id){
    if(selCurBtn != NULL)
        selCurBtn->setSelected(false);
    selCurBtn = getSpeciBtnByID(id);
    selCurBtn->setSelected(true);
    emit selectedSpeciValueChanged(selCurBtn->getValue().toInt());
}


int VariantSpecification::getValue(int id){
    return getSpeciBtnByID(id)->getValue().toInt();
}

int VariantSpecification::getSelectedID() const{
    if(selCurBtn != NULL)
        return selCurBtn->getID();
    return -1;
}

SelectableValueButton* VariantSpecification::getSpeciBtnByID(int id){
    for(int i = 0; i < speciBtns.length(); ++i){
        if(speciBtns.at(i)->getID() == id){
            return speciBtns.at(i);
        }
    }
    return 0;
}

void VariantSpecification::setSelected(int id){
    btnSpeciClicked(id);
}


