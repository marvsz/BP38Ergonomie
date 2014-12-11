#include "utilityoption.h"
#include <QHBoxLayout>
#include "numberlineedit.h"
UtilityOption::UtilityOption(UtilityOptionType optionType, QWidget *parent) :
    QWidget(parent)
{
    this->optionType = optionType;

    if(optionType == TEXT_OPTION)
        this->inputTextField = new TextLineEdit(this);
    else
        this->inputTextField = new NumberLineEdit(this);

    connect(this->inputTextField, SIGNAL(textChanged(QString)), this, SLOT(textChanged()));
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

