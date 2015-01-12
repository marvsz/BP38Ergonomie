#include "numberlineedit.h"
#include <QIntValidator>

NumberLineEdit::NumberLineEdit(QWidget *parent) :
    TextLineEdit(parent)
{
    this->setValidator(new QIntValidator(this));
    this->setInputMethodHints(Qt::ImhDialableCharactersOnly);
}

int NumberLineEdit::getValue() const {
    return this->text().toInt();
}

void NumberLineEdit::setValue(int value){
    this->setText(QString::number(value));
}
