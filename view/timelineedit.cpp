#include "timelineedit.h"

TimeLineEdit::TimeLineEdit(QWidget *parent) :
    TextLineEdit(parent)
{
    this->setInputMask("dd:dd");
}

int TimeLineEdit::getValue() const{
    return this->text().toInt();
}

void TimeLineEdit::setValue(int value){
 this->setText(QString::number(value));

}
