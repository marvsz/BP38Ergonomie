#include "timelineedit.h"
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
TimeLineEdit::TimeLineEdit(QWidget *parent, TimeLineType type) :
    TextLineEdit(parent),
    type(type)
{
    QRegularExpression regEx;
    QString inputMask;
    switch(this->type){
    case(TimeLineType::MINUTE_SECOND):
        regEx = QRegularExpression("^([0-5][0-9]:[0-5][0-9])$");
        inputMask="dd:dd";
        break;
    case(TimeLineType::HOUR_MINUTE):
        regEx = QRegularExpression("^((0[0-9]|1[0-9]|2[0-3]):[0-5][0-9])$");
        inputMask="dd:dd";
        break;
    case(TimeLineType::HOUR_MINUTE_SECOND):
        regEx = QRegularExpression("^((0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9])$");
        inputMask="dd:dd:dd";
        break;
    }
    this->setValidator(new QRegularExpressionValidator(regEx));
    //this->setInputMask(inputMask);
    this->setInputMethodHints(Qt::ImhDialableCharactersOnly);
}

QTime TimeLineEdit::getValue(){
    normalizeText();
    switch(this->type){
    case(TimeLineType::HOUR_MINUTE):
        return QTime(this->text().left(2).toInt(), this->text().right(2).toInt());
        break;
    case(TimeLineType::MINUTE_SECOND):
        return QTime(0,this->text().left(2).toInt(),this->text().right(2).toInt(),0);
        break;
    case(TimeLineType::HOUR_MINUTE_SECOND):
        return QTime(this->text().left(2).toInt(), this->text().right(4).left(2).toInt(), this->text().right(2).toInt(), 0);
        break;
    }
}

void TimeLineEdit::setValue(const QTime &value){
    switch(this->type){
    case(TimeLineType::MINUTE_SECOND):
        setText(value.toString("mm:ss"));
        qDebug() << this->text();
        break;
    case(TimeLineType::HOUR_MINUTE):
        setText(value.toString("HH:mm"));
        qDebug() << this->text();
        break;
    case(TimeLineType::HOUR_MINUTE_SECOND):
        setText(value.toString("HH:mm:ss"));
        break;
    }
}

void TimeLineEdit::normalizeText(){
    int inputLength = 0;
    switch(this->type){
    case(TimeLineType::MINUTE_SECOND):
        inputLength = 4;
        break;
    case(TimeLineType::HOUR_MINUTE):
        inputLength = 4;
        break;
    case(TimeLineType::HOUR_MINUTE_SECOND):
        inputLength = 6;
        break;
    }
    while(this->text().size() < inputLength){
        setText(this->text().append(QString::number(0)));
    }
}
