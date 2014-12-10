#include "selectablevaluebutton.h"
#include <QWidget>

const QString SelectableValueButton::qssHead = "QPushButton {font: 100 ";
const QString SelectableValueButton::qssSelected     = "px \"Serif\"; color: #FFFFFF; border: 2px solid #007aff; border-radius: 10px; background-color: #007aff; padding: 4px;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";
const QString SelectableValueButton::qssNotSelected  = "px \"Serif\"; color: #007aff; border: 2px solid #007aff; border-radius: 10px; background-color: #f5f5f5; padding: 4px;} QPushButton:pressed {color: #FFFFFF;background-color: #007aff;}";


SelectableValueButton::SelectableValueButton(int id, int value, QWidget *parent) :
    QPushButton(parent)
{
    this->id = id;
    this->setSelected(false);
    this->setValue(value);
    connect(this, SIGNAL(pressed()), this, SLOT(qpbtnPressed()));
}


void SelectableValueButton::setSelected(bool isSelected){
    this->isSel = isSelected;
    if(isSel)
        this->setStyleSheet(qssHead + QString().number(20) + qssSelected);
    else
        this->setStyleSheet(qssHead + QString().number(20) + qssNotSelected);
}

bool SelectableValueButton::isSelected() const{
    return this->isSel;
}

void SelectableValueButton::setID(int id){
    this->id = id;
}

int SelectableValueButton::getID() const{
    return this->id;
}

void SelectableValueButton::qpbtnPressed(){
    emit pressedWithID(this->id);
}

int SelectableValueButton::getValue(){
    return value;
}

void SelectableValueButton::setValue(int value){
    this->value = value;
}


int SelectableValueButton::getMaxFontSize(){
    int width = size().width() - 10;
    int fontSize = 5;
    QFont font = QFont("Serif", fontSize, 100, false);
    for(int i = fontSize; i < 20; ++i){
        font.setPointSize(i);
        QFontMetrics fm(font);
        int t_w = fm.width(this->text());
        if(t_w > width){
            return --i;
        }
    }
    return 20;
}

