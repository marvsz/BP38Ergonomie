#include "verticaloptionselectioncontrol.h"
#include <QLabel>

VerticalOptionSelectionControl::VerticalOptionSelectionControl(QWidget *parent) :
    QWidget(parent),
    btnOptions(QVector<SelectableValueButton*>()),
    mainLayout(new QVBoxLayout)
{
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);
}


//Public slots
void VerticalOptionSelectionControl::setSelectedValue(int id){
    if(id >= 0 && id < btnOptions.length() && currentSelectedBtn != NULL && currentSelectedBtn->getID() != id){
        btnOptions.at(currentSelectedBtn->getID())->setSelected(false);
        currentSelectedBtn = btnOptions.at(id);
        currentSelectedBtn->setSelected(true);
        emit selectionChanged(id);
    }
}

void VerticalOptionSelectionControl::setSelectedValue(const QString &text){
    for(int i = 0; i < btnOptions.length(); ++i){
        SelectableValueButton *btn = btnOptions.at(i);
        if(btn->text().compare(text) == 0){
            setSelectedValue(btn->getID());
            break;
        }
    }
}

void VerticalOptionSelectionControl::setSelectedByValue(int value){
    for(int i = 0; i < btnOptions.length(); ++i){
        SelectableValueButton *btn = btnOptions.at(i);
        if(btn->getValue().toInt() == value){
            setSelectedValue(btn->getID());
            break;
        }
    }
}

void VerticalOptionSelectionControl::setValues(const QStringList &texts, const QVector<QVariant> &values){
    clear();
    for(int i=0; i < texts.length(); ++i){
        SelectableValueButton *btn = new SelectableValueButton(i, values.at(i), this);
        btn->setMinimumSize(45, 45);
        btn->setText(texts.at(i));
        btnOptions.append(btn);
        mainLayout->addWidget(btn, 0, Qt::AlignVCenter);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
    }
    currentSelectedBtn = btnOptions.at(1);
    setSelectedValue(0);
}

void VerticalOptionSelectionControl::setValues(const QStringList &texts){
    clear();
    for(int i=0; i < texts.length(); ++i){
        SelectableValueButton *btn = new SelectableValueButton(i, texts.at(i), this);
        btn->setMinimumSize(45, 45);
        btn->setText(texts.at(i));
        btnOptions.append(btn);
        mainLayout->addWidget(btn, 0, Qt::AlignVCenter);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
    }
    currentSelectedBtn = btnOptions.at(1);
    setSelectedValue(0);
}

void VerticalOptionSelectionControl::setValues(const QStringList &texts, const QString &label){
    clear();
    mainLayout->addWidget(new QLabel(label));
    for(int i=0; i < texts.length(); ++i){
        SelectableValueButton *btn = new SelectableValueButton(i, texts.at(i), this);
        btn->setMinimumSize(45, 45);
        btn->setText(texts.at(i));
        btnOptions.append(btn);
        mainLayout->addWidget(btn, 0, Qt::AlignVCenter);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
    }
    currentSelectedBtn = btnOptions.at(1);
    setSelectedValue(0);
}

//Private methods
void VerticalOptionSelectionControl::clear(){
    btnOptions.clear();
    QLayoutItem *item;
    while((item = mainLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

//Getter and setter
QVariant VerticalOptionSelectionControl::getSelectedValue() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->getValue();
    else
        return 0;
}

QString VerticalOptionSelectionControl::getSelectedTexts() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->text();
    else
        return "";
}

int VerticalOptionSelectionControl::getSelectedID() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->getID();
    else
        return -1;
}