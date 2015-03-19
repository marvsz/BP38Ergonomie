#include "verticaloptionselectioncontrol.h"
#include <QLabel>

VerticalOptionSelectionControl::VerticalOptionSelectionControl(QWidget *parent) :
    QWidget(parent),
    btnOptions(QVector<SelectableValueButton*>()),
    mainLayout(new QVBoxLayout),
    id(1)
{
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);
}


//Public slots
void VerticalOptionSelectionControl::setSelectedValue(int id){
    if(id >= 0 && id < btnOptions.length()+1 && currentSelectedBtn != NULL && currentSelectedBtn->getID() != id){
        btnOptions.at(currentSelectedBtn->getID()-1)->setSelected(false);
        currentSelectedBtn = btnOptions.at(id-1);
        currentSelectedBtn->setSelected(true);
        emit selectionChanged(id);
    }
    else if(currentSelectedBtn->getID() == id){
        currentSelectedBtn->setSelected(true);
    }
}

void VerticalOptionSelectionControl::setValues(const QStringList &texts, const QString &label){
    clear();
    QLabel *lblName = new QLabel(label);
    lblName->setObjectName("lblHeader");
    mainLayout->addWidget(lblName, 0, Qt::AlignHCenter);
    for(int i=0; i < texts.length(); ++i){
        SelectableValueButton *btn = new SelectableValueButton(id++, texts.at(i), this);
        btn->setMinimumSize(45, 45);
        btn->setText(texts.at(i));
        btnOptions.append(btn);
        mainLayout->addWidget(btn, 0, Qt::AlignVCenter);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
    }
    currentSelectedBtn = btnOptions.at(1);
    setSelectedValue(1);
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
