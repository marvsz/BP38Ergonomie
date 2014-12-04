#include "valuecontrol.h"
#include <QGuiApplication>
#include <QVBoxLayout>

#include "selectablevaluebutton.h"

ValueControl::ValueControl(QString unit, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *txtEditLineLayout = new QHBoxLayout;
    QWidget* txtEdit = new QWidget(this);
    QHBoxLayout *txtEditLayout = new QHBoxLayout;
    btnLineLayout = new QHBoxLayout;
    QHBoxLayout *sldrLineLayout = new QHBoxLayout;

    this->btnValues = new QVector<SelectableValueButton*>();
    this->btnRanges = new QVector<int>();
    this->unit = unit;

    lblText = new QLabel(this);
    lblText->setText("");
    lblText->setMinimumSize(300,60);

    lblMin = new QLabel(this);
    lblMin->setFixedSize(90,60);
    lblMax = new QLabel(this);
    lblMax->setFixedSize(90,60);

    txtBxValue = new QLineEdit(this);
    txtBxValue->setAlignment(Qt::AlignCenter);
    txtBxValue->setInputMask("#000");
    txtBxValue->setFixedSize(100,60);
    connect(txtBxValue, SIGNAL(editingFinished()), this, SLOT(txtBxValueHasChanged()));
    connect(txtBxValue, SIGNAL(editingFinished()), QGuiApplication::inputMethod(), SLOT(hide()));

    btnPlus = new QPushButton (this);
    btnPlus->setText("+");
    btnPlus->setFixedSize(60,60);
    connect(btnPlus, SIGNAL(pressed()), this, SLOT(btnPlusClicked()));

    btnMinus = new QPushButton (this);
    btnMinus->setText("-");
    btnMinus->setFixedSize(60,60);
    connect(btnMinus, SIGNAL(pressed()), this, SLOT(btnMinusClicked()));

    txtEditLayout->addWidget(btnMinus);
    txtEditLayout->addWidget(txtBxValue);
    txtEditLayout->addWidget(btnPlus);
    txtEdit->setLayout(txtEditLayout);

    txtEditLineLayout->addWidget(lblText, 0, Qt::AlignLeft);
    txtEditLineLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    txtEditLineLayout->addWidget(txtEdit, 0, Qt::AlignCenter);
    txtEditLineLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));

    sldrValue = new QSlider(this);
    sldrValue->setOrientation(Qt::Horizontal);
    sldrValue->setMinimumSize(400, 60);
    sldrValue->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    connect(sldrValue, SIGNAL(valueChanged(int)), this, SLOT(sldrValueHasChanged()));

    sldrLineLayout->addWidget(lblMin);
    sldrLineLayout->addWidget(sldrValue);
    sldrLineLayout->addWidget(lblMax);

    mainLayout->addLayout(txtEditLineLayout);
    mainLayout->addLayout(btnLineLayout);
    mainLayout->addLayout(sldrLineLayout);

    this->setLayout(mainLayout);
    this->setMinimumSize(600, 250);
    this->setMaximumHeight(300);
}

void ValueControl::setValue(int value){
    sldrValue->setValue(value);
}

void ValueControl::setValues(int min, int max, QVector<int>* btnValues, QString* iconSetPath){
    btnRanges = new QVector<int>();
    btnRanges->append(min);
    for(int i = 0; i < btnValues->length() - 1; ++i)
        btnRanges->append(btnValues->at(i) + (btnValues->at(i+1) - btnValues->at(i))/2);
    btnRanges->append(max+1);


    for(int i = 0; i < this->btnValues->length(); i++){
        btnLineLayout->removeWidget(this->btnValues->at(i));
        delete this->btnValues->at(i);
    }
    this->btnValues->clear();

    for(int i = 0; i < btnValues->length(); i++){
        SelectableValueButton *currentBtn = new SelectableValueButton(i, btnValues->at(i), this);
        currentBtn->setText((QString().number(btnValues->at(i))).append(unit));
        try{
            QString s = (*iconSetPath);
            s.append(QString::number(btnValues->at(i))+".png");
            currentBtn->setIcon(QIcon(s));
            currentBtn->setIconSize(QSize(50,50));
        }catch(...){}
        this->btnValues->append(currentBtn);
        connect(currentBtn, SIGNAL(pressedWithID(int)), this, SLOT(btnValueHasClicked(int)));
        btnLineLayout->addWidget(currentBtn);
        currentBtn->setMinimumSize(50,60);
    }


    lblMin->setText(QString().number(min));
    lblMax->setText(QString().number(max));
    currentSelectedBtnID = 0;
    sldrValue->setRange(min, max);
    sldrValueHasChanged();
}

void ValueControl::txtBxValueHasChanged(){
    sldrValue->setValue(txtBxValue->text().toInt());
    sldrValueHasChanged();
}

void ValueControl::sldrValueHasChanged(){
    txtBxValue->setText(QString().number(sldrValue->value()));
    btnHighlight(sldrValue->value());
    emit valueChanged(sldrValue->value());
}

void ValueControl::btnValueHasClicked(int id){
    SelectableValueButton *btn = this->btnValues->at(id);
    btnHighlight(btn->getValue());
    sldrValue->setValue(btn->getValue());
}

void ValueControl::btnHighlight(int value){
    this->btnValues->at(currentSelectedBtnID)->setSelected(false);
    for(int i = 0; i < btnValues->length(); ++i){
        if(btnValues->at(i)->getValue() >= value){
            currentSelectedBtnID = i;
            break;
        }
    }
    this->btnValues->at(currentSelectedBtnID)->setSelected(true);

}

void ValueControl::btnPlusClicked(){
    sldrValue->setValue(sldrValue->value() + 1);
}

void ValueControl::btnMinusClicked(){
    sldrValue->setValue(sldrValue->value() - 1);
}

void ValueControl::setText(QString text){
    this->lblText->setText(text);
}

QString ValueControl::getText() const{
    return lblText->text();
}




