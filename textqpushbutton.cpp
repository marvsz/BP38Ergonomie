#include "textqpushbutton.h"
#include <QWidget>
#include <QString>
#include <QPushButton>

TextQPushButton::TextQPushButton(int id, QString text, QWidget *parent) :
    QPushButton(parent)
{
    this->id = id;
    this->setText(text);
    this->setSelected(false);

    connect(this, SIGNAL(pressed()), this, SLOT(qpbtnPressed()));
}


void TextQPushButton::setSelected(bool isSelected){
    this->isSel = isSelected;
    if(isSel)
        this->setStyleSheet(this->qssSelected);
    else
        this->setStyleSheet(this->qssNotSelected);
}

bool TextQPushButton::isSelected() const{
    return this->isSel;
}

int TextQPushButton::getID() const{
    return this->id;
}

void TextQPushButton::qpbtnPressed(){
    emit pressedWithID(this->id);
}

void TextQPushButton::changeText(QString text){
    this->setText(text);
    emit this->textChanged();
}

void TextQPushButton::setSelectedByText(QString text){
    if(this->text() == text){
        setSelected(true);
    }
    else {
        setSelected(false);
    }
}
