#include "quickarmposturecontrol.h"

#include <QLabel>

QuickArmPostureControl::QuickArmPostureControl(QWidget *parent) :
    QWidget(parent),
    btnOptions(QVector<SelectableValueButton*>()),
    speciOptions(QVector<SelectableValueButton*>()),
    mainLayout(new QVBoxLayout),
    id(0),
    idSpeci(0)
{
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);
}


//Public slots
void QuickArmPostureControl::setSelectedValue(int id){
    if(id >= 0 && id < btnOptions.length() && currentSelectedBtn != NULL && currentSelectedBtn->getID() != id){
        btnOptions.at(currentSelectedBtn->getID())->setSelected(false);
        currentSelectedBtn = btnOptions.at(id);
        currentSelectedBtn->setSelected(true);
        if(speciOptions.at(0)->isSelected()&&speciOptions.at(1)->isSelected()){
            emit selectionChanged(id,2);
        }
        else{
            if(speciOptions.at(0)->isSelected()){
                emit selectionChanged(id,0);
            }
            if(speciOptions.at(1)->isSelected()){
                emit selectionChanged(id,1);
            }
        }


    }
}

void QuickArmPostureControl::setSelectedSpecification(int id){
    if(id >= 0 && id < speciOptions.length() && currentSpeciBtn != NULL){
        switch (id) {
        case 0:
            if(!speciOptions.at(0)->isSelected()){
                speciOptions.at(0)->setSelected(true);
                emit specificationChanged(2);
            }
            else{
                if(speciOptions.at(0)->isSelected()&&speciOptions.at(1)->isSelected()){
                    speciOptions.at(0)->setSelected(false);
                    emit specificationChanged(1);
                }
            }
            break;
        case 1:
            if(!speciOptions.at(1)->isSelected()){
                speciOptions.at(1)->setSelected(true);
                emit specificationChanged(2);
            }
            else{
                if(speciOptions.at(1)->isSelected()&&speciOptions.at(0)->isSelected()){
                    speciOptions.at(1)->setSelected(false);
                    emit specificationChanged(0);
                }
            }
            break;
        default:
            break;
        }
    }
}

void QuickArmPostureControl::setSelectedValue(const QString &text){
    for(int i = 0; i < btnOptions.length(); ++i){
        SelectableValueButton *btn = btnOptions.at(i);
        if(btn->text().compare(text) == 0){
            setSelectedValue(btn->getID());
            break;
        }
    }
}

void QuickArmPostureControl::setSelectedByValue(int value){
    for(int i = 0; i < btnOptions.length(); ++i){
        SelectableValueButton *btn = btnOptions.at(i);
        if(btn->getValue().toInt() == value){
            setSelectedValue(btn->getID());
            break;
        }
    }
}

void QuickArmPostureControl::setValues(const QStringList &texts, const QVector<QVariant> &values){
    clear();
    for(int i=0; i < texts.length(); ++i){
        SelectableValueButton *btn = new SelectableValueButton(i, values.at(i), this);
        btn->setMinimumSize(45, 45);
        btn->setText(texts.at(i));
        btnOptions.append(btn);
        mainLayout->addWidget(btn, 0, Qt::AlignVCenter);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
    }
    currentSelectedBtn = btnOptions.at(0);
    setSelectedValue(0);
}

void QuickArmPostureControl::setValues(const QStringList &texts){
    clear();
    for(int i=0; i < texts.length(); ++i){
        SelectableValueButton *btn = new SelectableValueButton(i, texts.at(i), this);
        btn->setMinimumSize(45, 45);
        btn->setText(texts.at(i));
        btnOptions.append(btn);
        mainLayout->addWidget(btn, 0, Qt::AlignVCenter);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
    }
    currentSelectedBtn = btnOptions.at(0);
    setSelectedValue(0);
}

void QuickArmPostureControl::setValues(const QStringList &texts, const QStringList &differ, const QString &label){
    clear();
    mainLayout->addWidget(new QLabel(label));

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

    generalButtonLayout->addLayout(optionButtonLayout);
    mainLayout->addLayout(generalButtonLayout);
    currentSelectedBtn = btnOptions.at(0);
    currentSelectedBtn->setSelected(true);
    setSelectedValue(-1);
    if(!speciOptions.isEmpty()){
        currentSpeciBtn = speciOptions.at(0);
        setSelectedSpecification(0);
    }
    if(!speciOptions.isEmpty()){
        currentSpeciBtn = speciOptions.at(1);
        setSelectedSpecification(1);
    }
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
