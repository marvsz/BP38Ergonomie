#include "optionselectioncontrol.h"

OptionSelectionControl::OptionSelectionControl(QWidget *parent) :
    QWidget(parent),
    btnOptions(QVector<SelectableValueButton*>()),
    mainLayout(new QHBoxLayout)
{
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);
}

//Public slots
void OptionSelectionControl::setSelectedValue(int id){
    if(id >= 0 && id < btnOptions.length() && currentSelectedBtn != NULL){
        btnOptions.at(currentSelectedBtn->getID())->setSelected(false);
        currentSelectedBtn = btnOptions.at(id);
        currentSelectedBtn->setSelected(true);
        emit selectionChanged(id);
    }
}

void OptionSelectionControl::setSelectedValue(const QString &text){
    for(int i = 0; i < btnOptions.length(); ++i){
        SelectableValueButton *btn = btnOptions.at(i);
        if(btn->text().compare(text) == 0){
            setSelectedValue(btn->getID());
            break;
        }
    }
}

void OptionSelectionControl::setSelectedValue(const QVariant &value){
    for(int i = 0; i < btnOptions.length(); ++i){
        SelectableValueButton *btn = btnOptions.at(i);
        if(btn->getValue() == value){
            setSelectedValue(btn->getID());
            break;
        }
    }
}

void OptionSelectionControl::setValues(const QStringList &texts, const QVector<QVariant> &values){
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

void OptionSelectionControl::setValues(const QStringList &texts){
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

//Private methods
void OptionSelectionControl::clear(){
    btnOptions.clear();
    QLayoutItem *item;
    while((item = mainLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

//Getter and setter
QVariant OptionSelectionControl::getSelectedValue() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->getValue();
    else
        return 0;
}

QString OptionSelectionControl::getSelectedTexts() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->text();
    else
        return "";
}

int OptionSelectionControl::getSelectedID() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->getID();
    else
        return -1;
}


