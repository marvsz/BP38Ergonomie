#include "optionselectioncontrol.h"

OptionSelectionControl::OptionSelectionControl(const QVector<QString> &options, QWidget *parent) :
    QWidget(parent)
{
    mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    btnOptions = new QVector<SelectableValueButton*>();

    for(int i=0; i < options.length(); ++i){
        SelectableValueButton *btn = new SelectableValueButton(i, i, this);
        btn->setMinimumSize(45, 45);
        btn->setText(options.at(i));
        btnOptions->append(btn);
        mainLayout->addWidget(btn, 0, Qt::AlignVCenter);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
    }
    currentSelectedBtnID = 1;
    this->setLayout(mainLayout);
    setSelectedValue(0);
}

//Public slots
void OptionSelectionControl::setSelectedValue(int id){
    if(currentSelectedBtnID != id){
        btnOptions->at(currentSelectedBtnID)->setSelected(false);
        btnOptions->at(id)->setSelected(true);
        currentSelectedBtnID = id;
        emit selectionChanged(id);
    }
}

//Getter and setter
QString OptionSelectionControl::getSelectedValue(){
    return btnOptions->at(currentSelectedBtnID)->text();
}

int OptionSelectionControl::getSelectedID(){
    return currentSelectedBtnID;
}

void OptionSelectionControl::setSelectedValue(const QString &name){
    for(int i = 0; i < this-> btnOptions->count(); ++i){
        if (btnOptions->at(i)->text().compare(name) == 0)
            setSelectedValue(btnOptions->at(i)->getID());
    }
}

