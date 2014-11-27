#include "owncon.h"
#include <QWidget>
#include <QGuiApplication>
#include <QLineEdit>
#include <QSlider>
#include <QGroupBox>
#include <QVector>
#include <QString>
#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "ownqpushbutton.h"

OwnCon::OwnCon(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *txtEditLineLayout = new QHBoxLayout;
    QWidget* txtEdit = new QWidget(this);
    QHBoxLayout *txtEditLayout = new QHBoxLayout;
    btnLineLayout = new QHBoxLayout;
    QHBoxLayout *sldrLineLayout = new QHBoxLayout;

    this->btnCount = 0;
    this->btnAngles = new QVector<OwnQPushButton*>();

    lblText = new QLabel(this);
    lblText->setText("");
    lblText->setMinimumSize(300,60);

    lblMin = new QLabel(this);


    lblMax = new QLabel(this);


    txtBxAngle = new QLineEdit(this);
    txtBxAngle->setAlignment(Qt::AlignCenter);
    txtBxAngle->setInputMask("#000");
    connect(txtBxAngle, SIGNAL(editingFinished()), this, SLOT(txtBxAngleHasChanged()));
    connect(txtBxAngle, SIGNAL(editingFinished()), QGuiApplication::inputMethod(), SLOT(hide()));

    btnPlus = new OwnQPushButton (0, 0, "", 0, 0, this);
    btnPlus->setText("+");
    connect(btnPlus, SIGNAL(pressed()), this, SLOT(btnPlusClicked()));

    btnMinus = new OwnQPushButton (0, 0, "", 0, 0, this);
    btnMinus->setText("-");
    connect(btnMinus, SIGNAL(pressed()), this, SLOT(btnMinusClicked()));
    txtEditLineLayout->addWidget(lblText, 0, Qt::AlignLeft);
    txtEditLineLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    txtEditLayout->addWidget(btnMinus);
    txtEditLayout->addWidget(txtBxAngle);
    txtEditLayout->addWidget(btnPlus);
    txtEdit->setLayout(txtEditLayout);
    txtEditLineLayout->addWidget(txtEdit, 0, Qt::AlignCenter);
    txtEditLineLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    btnPlus->setFixedSize(60,60);
    btnMinus->setFixedSize(60,60);
    txtBxAngle->setFixedSize(100,60);
    lblMin->setFixedSize(90,60);
    lblMax->setFixedSize(90,60);


    sldrAngle = new QSlider(this);
    sldrAngle->setOrientation(Qt::Horizontal);
    sldrAngle->setMinimumSize(400, 60);
    sldrAngle->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    sldrLineLayout->addWidget(lblMin, 1 , 0);
    sldrLineLayout->addWidget(sldrAngle, 8 , 0);
    sldrLineLayout->addWidget(lblMax, 1 , Qt::AlignRight);

    connect(sldrAngle, SIGNAL(valueChanged(int)), this, SLOT(sldrAngleHasChanged()));


    mainLayout->addLayout(txtEditLineLayout);
    mainLayout->addLayout(btnLineLayout);
    mainLayout->addLayout(sldrLineLayout);
    this->setLayout(mainLayout);
    this->setMinimumSize(600, 250);
    this->setMaximumHeight(300);
}

void OwnCon::setValues(int min, int max, QVector<int>* btnValues, QString* iconSetPath){
    this->min = min;
    this->max = max;
    this->btnCount = btnValues->length();

    QVector<int> *btnRanges = new QVector<int>();
    btnRanges->append(min);
    for(int i = 0; i < btnValues->length() - 1; ++i)
        btnRanges->append(btnValues->at(i) + (btnValues->at(i+1) - btnValues->at(i))/2);
    btnRanges->append(max+1);


    for(int i = 0; i < btnAngles->length(); i++){
        btnLineLayout->removeWidget(btnAngles->at(i));
        delete btnAngles->at(i);
    }
    this->btnAngles->clear();

    for(int i = 0; i < btnValues->length(); i++){
        OwnQPushButton *currentBtn = new OwnQPushButton(i, btnValues->at(i), "°", btnRanges->at(i), btnRanges->at(i+1) - 1, this);
        try{
            QString s = (*iconSetPath);
            s.append(QString::number(btnValues->at(i))+".png");
            currentBtn->setIcon(QIcon(s));
            currentBtn->setIconSize(QSize(50,50));
        }catch(...){}
        btnAngles->append(currentBtn);
        connect(currentBtn, SIGNAL(pressedWithID(int)), this, SLOT(btnAngleHasClicked(int)));
        btnLineLayout->addWidget(currentBtn);
        currentBtn->setMinimumSize(50,60);
    }

    sldrAngle->setRange(min, max);
    lblMin->setText(QString().number(min));
    lblMax->setText(QString().number(max));



    sldrAngleHasChanged();
}

void OwnCon::txtBxAngleHasChanged(){
    sldrAngle->setValue(txtBxAngle->text().toInt());
    sldrAngleHasChanged();
}

void OwnCon::sldrAngleHasChanged(){
        QString s;
        s = s.number(sldrAngle->value());
        txtBxAngle->setText(s);
        btnHighlight(sldrAngle->value());
}

void OwnCon::btnAngleHasClicked(int id){
    OwnQPushButton *btn = btnAngles->at(id);
    btnHighlight(btn->getValue());
    sldrAngle->setValue(btn->getValue());
}

void OwnCon::btnHighlight(int value){
    for(int i = 0; i < btnCount; i++)
        btnAngles->at(i)->setSelectedByValue(value);
}

void OwnCon::btnPlusClicked(){
    sldrAngle->setValue(sldrAngle->value() + 1);
}

void OwnCon::btnMinusClicked(){
    sldrAngle->setValue(sldrAngle->value() - 1);
}

void OwnCon::setText(QString text){
    this->lblText->setText(text);
}

QString OwnCon::getText() const{
    return lblText->text();
}




