#include "numberlineedit.h"
#include <QIntValidator>

NumberLineEdit::NumberLineEdit(QWidget *parent) :
    TextLineEdit(parent)
{
    this->setValidator(new QIntValidator(this));
}
