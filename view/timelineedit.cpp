#include "timelineedit.h"

TimeLineEdit::TimeLineEdit(QWidget *parent) :
    TextLineEdit(parent)
{
    //this->setInputMask("dd:dd");
    this->setInputMethodHints(Qt::ImhDialableCharactersOnly);
}

QTime TimeLineEdit::getValue() const{
    return QTime(0,this->text().left(2).toInt(),this->text().right(2).toInt(),0);
}

void TimeLineEdit::setValue(const QTime &value){

 this->setText(value.toString("mm:ss"));

}
