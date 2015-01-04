#include "numberlineedit.h"
#include <QIntValidator>

NumberLineEdit::NumberLineEdit(QWidget *parent) :
    TextLineEdit(parent)
{
    this->setValidator(new QIntValidator(this));
}

int NumberLineEdit::getValue() const {
    return this->text().toInt();
}

void NumberLineEdit::setValue(int value){
    this->setText(QString::number(value));
}
