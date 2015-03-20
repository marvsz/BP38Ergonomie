#include "datelineedit.h"
#include <QRegularExpressionValidator>
#include <QDebug>

const QRegularExpression DateLineEdit::regEx = QRegularExpression("^(((0?[0-9])|(1[0-9])|(2[0-9])|(3[0-1]))[\\.|\\-|\\/]((0?[0-9])|(1[0-2]))[\\.|\\-|\\/]([0-9][0-9][0-9][0-9]))?$");

DateLineEdit::DateLineEdit(QWidget *parent) :
    TextLineEdit(parent)
{
    this->setValidator(new QRegularExpressionValidator(regEx));
    this->setInputMethodHints(Qt::ImhDialableCharactersOnly);

    connect(this, SIGNAL(editingFinished()), this, SLOT(updateDate()));
}

QDate DateLineEdit::getDate() const {
    return this->currentDate;
}

void DateLineEdit::setDate(const QDate &date){
    if(date.isValid())
        currentDate = date;
    else
        currentDate = QDate::currentDate();
    updateText();
}

void DateLineEdit::increaseDay(){
    currentDate = currentDate.addDays(1);
    updateText();
}

void DateLineEdit::increaseMonth(){
    currentDate = currentDate.addMonths(1);
    updateText();
}

void DateLineEdit::increaseYear(){
    currentDate = currentDate.addYears(1);
    updateText();
}

void DateLineEdit::decreaseDay(){
    currentDate = currentDate.addDays(-1);
    updateText();
}

void DateLineEdit::decreaseMonth(){
    currentDate = currentDate.addMonths(-1);
    updateText();
}

void DateLineEdit::decreaseYear(){
    currentDate = currentDate.addYears(-1);
    updateText();
}

void DateLineEdit::updateText(){
    setText(currentDate.toString("dd.MM.yyyy"));
    emit dateChanged();
}

void DateLineEdit::updateDate(){
    QStringList dmy = this->text().split(QRegularExpression("\\.|\\-|\\/"));
    if(dmy.length() == 3)
        currentDate = QDate(dmy.at(2).toInt(), dmy.at(1).toInt(), dmy.at(0).toInt());
}
