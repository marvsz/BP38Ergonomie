#include "textcon.h"
#include "textqpushbutton.h"
#include <QWidget>
#include <QLineEdit>
#include <QGroupBox>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>


TextCon::TextCon(int btnCount, QString btnValues[], QWidget *parent) :
    QGroupBox(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *txtEditLineLayout = new QHBoxLayout;
    QHBoxLayout *txtEditLayout = new QHBoxLayout;
    QHBoxLayout *btnLineLayout = new QHBoxLayout;

    this->btnCount = btnCount;

    lblValue = new QLabel(this);
    lblValue->setAlignment(Qt::AlignCenter);
    lblValue->setText("");

    lblText = new QLabel(this);

    txtEditLineLayout->addWidget(lblText);
    txtEditLayout->addWidget(lblValue);
    txtEditLineLayout->addLayout(txtEditLayout);

    lblValue->setFixedSize(300,60);

    this->btnTexts = QVector<TextQPushButton*>();
    for(int i = 0; i < btnCount; i++){
        TextQPushButton *currentBtn = new TextQPushButton(i, btnValues[i], this);
        btnTexts.append(currentBtn);
        connect(currentBtn, SIGNAL(pressedWithID(int)), this, SLOT(btnTextHasClicked(int)));
        btnLineLayout->addWidget(currentBtn);
        currentBtn->setMinimumSize(50,60);
    }

    mainLayout->addLayout(txtEditLineLayout);
    mainLayout->addLayout(btnLineLayout);
    this->setLayout(mainLayout);
    this->setMinimumSize(600, 300);
}

void TextCon::lblTextHasChanged(){
    btnHighlight(lblText->text());
}

void TextCon::btnTextHasClicked(int id){
    TextQPushButton *btn = btnTexts.at(id);
    QString s = btn->text();
    btnHighlight(s);
    lblValue->setText(s);
}

void TextCon::btnHighlight(QString text){
    for(int i = 0; i < btnCount; i++)
        btnTexts.at(i)->setSelectedByText(text);
}

void TextCon::setText(QString text){
    this->lblText->setText(text);
}

QString TextCon::getText() const{
    return lblText->text();
}
