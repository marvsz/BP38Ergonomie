#include "utilityoption.h"
#include <QHBoxLayout>
#include "numberlineedit.h"
UtilityOption::UtilityOption(QString* name, UtilityOptionType optionType, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout;

    this->optionType = optionType;

    this->nameLabel = new QLabel();
    this->nameLabel->setText(*name);

    if(optionType == TEXT_OPTION)
        this->inputTextField = new TextLineEdit(this);
    else
        this->inputTextField = new NumberLineEdit(this);
    connect(this->inputTextField, SIGNAL(textChanged(QString)), this, SLOT(textChanged()));

    layout->addWidget(this->nameLabel);
    layout->addWidget(this->inputTextField);

    this->setLayout(layout);

}

QString UtilityOption::getTextValue(){
    if(this->optionType == TEXT_OPTION)
        return this->inputTextField->text();
    else
        return "";
}

int UtilityOption::getIntValue(){
    if(this->optionType == VALUE_OPTION)
        return this->inputTextField->text().toInt();
    else
        return -1;
}

void UtilityOption::setValue(int i){
    if(optionType == VALUE_OPTION)
        this->inputTextField->setText(QString::number(i));
}

void UtilityOption::setValue(QString text){
    if(optionType == TEXT_OPTION)
        this->inputTextField->setText(text);
}

void UtilityOption::clear(){
    this->inputTextField->clear();
}

void UtilityOption::setPlaceholder(QString placeholder){
    this->inputTextField->setPlaceholderText(placeholder);
}


void UtilityOption::textChanged(){
    if(optionType == TEXT_OPTION)
        emit valueChanged(this->inputTextField->text());
    else if (optionType == VALUE_OPTION)
        emit valueChanged(this->inputTextField->text().toInt());
}

