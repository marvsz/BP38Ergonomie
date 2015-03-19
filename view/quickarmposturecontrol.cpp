#include "quickarmposturecontrol.h"

#include <QLabel>

QuickArmPostureControl::QuickArmPostureControl(QWidget *parent) :
    QWidget(parent),
    btnOptions(QVector<SelectableValueButton*>()),
    speciOptions(QVector<SelectableValueButton*>()),
    mainLayout(new QVBoxLayout),
    id(1),
    idSpeci(1),
    specification(3)
{
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);
}


//Public slots
void QuickArmPostureControl::setSelectedValue(int id){
    if(id >= 0 && id < btnOptions.length()+1 && currentSelectedBtn != NULL && currentSelectedBtn->getID() != id){
        btnOptions.at(currentSelectedBtn->getID()-1)->setSelected(false);
        currentSelectedBtn = btnOptions.at(id-1);
        currentSelectedBtn->setSelected(true);
        if(speciOptions.at(0)->isSelected()&&speciOptions.at(1)->isSelected()){
            emit selectionChanged(id,3);
            specification = 3;
        }
        else{
            if(speciOptions.at(0)->isSelected()){
                emit selectionChanged(id,1);
                specification = 1;
            }
            if(speciOptions.at(1)->isSelected()){
                emit selectionChanged(id,2);
                specification = 2;
            }
        }


    }
    else if(currentSelectedBtn->getID() == id){
        currentSelectedBtn->setSelected(true);
    }
}

void QuickArmPostureControl::setSelectedSpecification(int id){
    if(id >= 0 && id < speciOptions.length()+1 && currentSpeciBtn != NULL){
        switch (id) {
        case 1:
            if(!speciOptions.at(0)->isSelected()){
                speciOptions.at(0)->setSelected(true);
                emit specificationChanged(3);
                specification = 3;
            }
            else{
                if(speciOptions.at(0)->isSelected()&&speciOptions.at(1)->isSelected()){
                    speciOptions.at(0)->setSelected(false);
                    emit specificationChanged(1);
                    specification = 2;
                }
                else
                    speciOptions.at(0)->setSelected(true);
            }
            break;
        case 2:
            if(!speciOptions.at(1)->isSelected()){
                speciOptions.at(1)->setSelected(true);
                emit specificationChanged(2);
                specification = 3;
            }
            else{
                if(speciOptions.at(1)->isSelected()&&speciOptions.at(0)->isSelected()){
                    speciOptions.at(1)->setSelected(false);
                    emit specificationChanged(1);
                    specification = 1;
                }
                else
                    speciOptions.at(1)->setSelected(true);
            }
            break;
        default:
            break;
        }
    }
}

void QuickArmPostureControl::setValues(const QStringList &texts, const QStringList &differ, const QString &label){
    clear();
    QLabel *lblName = new QLabel(label);
    lblName->setObjectName("lblHeader");
    mainLayout->addWidget(lblName, 0, Qt::AlignHCenter);

    QHBoxLayout *generalButtonLayout = new QHBoxLayout();
    QVBoxLayout *variantButtonLayout = new QVBoxLayout();
    QVBoxLayout *optionButtonLayout = new QVBoxLayout();

    SelectableValueButton *leftBtn = new SelectableValueButton(idSpeci++, QVariant(differ.at(0)), this);
    SelectableValueButton *rightBtn = new SelectableValueButton(idSpeci++, QVariant(differ.at(1)), this);

    leftBtn->setMinimumSize(45, 45);
    leftBtn->setText(differ.at(0));
    speciOptions.append(leftBtn);
    rightBtn->setMinimumSize(45, 45);
    rightBtn->setText(differ.at(1));
    speciOptions.append(rightBtn);


    variantButtonLayout->addWidget(leftBtn);
    variantButtonLayout->addWidget(rightBtn);
    generalButtonLayout->addLayout(variantButtonLayout);

    connect(leftBtn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedSpecification(int)));
    connect(rightBtn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedSpecification(int)));

    for(int i=0; i < texts.length(); ++i) {
        SelectableValueButton *btn = new SelectableValueButton(id++, QVariant(texts.at(i)), this);
        btn->setMinimumSize(45, 45);
        btn->setText(texts.at(i));
        btnOptions.append(btn);
        optionButtonLayout->addWidget(btn, 0, Qt::AlignVCenter);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
    }
    mainLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Fixed, QSizePolicy::Expanding));
    generalButtonLayout->addLayout(optionButtonLayout);
    mainLayout->addLayout(generalButtonLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Fixed, QSizePolicy::Expanding));
    currentSelectedBtn = btnOptions.at(0);
    currentSelectedBtn->setSelected(true);
    setSelectedValue(1);
    currentSpeciBtn = speciOptions.at(0);
    setSelectedSpecification(1);
    setSelectedSpecification(2);

}

//Private methods
void QuickArmPostureControl::clear(){
    btnOptions.clear();
    QLayoutItem *item;
    while((item = mainLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

//Getter and setter
QVariant QuickArmPostureControl::getSelectedValue() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->getValue();
    else
        return 0;
}

QString QuickArmPostureControl::getSelectedTexts() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->text();
    else
        return "";
}

int QuickArmPostureControl::getSelectedID() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->getID();
    else
        return -1;
}

int QuickArmPostureControl::getSelectedSpecification() const{
        return this->specification;
}
