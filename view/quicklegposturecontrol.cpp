#include "quicklegposturecontrol.h"
#include <QLabel>

QuickLegPostureControl::QuickLegPostureControl(QWidget *parent) :
    QWidget(parent),
    btnOptions(QVector<SelectableValueButton*>()),
    leftOptions(QVector<SelectableValueButton*>()),
    rightOptions(QVector<SelectableValueButton*>()),
    mainLayout(new QVBoxLayout),
    id(0),
    idLeft(0),
    idRight(0)
{
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);
}


//Public slots
void QuickLegPostureControl::setSelectedValue(int id){
    if(id >= 0 && id < btnOptions.length() && currentSelectedBtn != NULL && currentSelectedBtn->getID() != id){
        btnOptions.at(currentSelectedBtn->getID())->setSelected(false);
        currentSelectedBtn = btnOptions.at(id);
        currentSelectedBtn->setSelected(true);
        if(currentSelectedBtn->getID()!=2){
            currentLeftBtn->setSelected(false);
            currentRightBtn->setSelected(false);
        }
        else{
            currentLeftBtn->setSelected(true);
            currentRightBtn->setSelected(true);
        }
        emit selectionChanged(id);

    }
}

void QuickLegPostureControl::setSelectedLeft(int id){
    if(id >= 0 && id < leftOptions.length() && currentLeftBtn != NULL  && (currentSelectedBtn->getID() == 2)){
        if(!leftOptions.at(currentLeftBtn->getID() != id)->isSelected()){
            leftOptions.at(currentLeftBtn->getID())->setSelected(false);
            currentLeftBtn = leftOptions.at(id);
            currentLeftBtn->setSelected(true);
            emit selectionChanged(id);
        }
        else{
            if(currentRightBtn->isSelected()){
                leftOptions.at(currentLeftBtn->getID())->setSelected(false);
                currentLeftBtn = leftOptions.at(id);
                emit selectionChanged(id);
            }
        }
    }
}

void QuickLegPostureControl::setSelectedRight(int id){
    if(id >= 0 && id < rightOptions.length() && currentRightBtn != NULL && (currentSelectedBtn->getID() == 2)){
        if(!rightOptions.at(currentRightBtn->getID() != id)->isSelected()){
            rightOptions.at(currentRightBtn->getID())->setSelected(false);
            currentRightBtn = rightOptions.at(id);
            currentRightBtn->setSelected(true);
            emit selectionChanged(id);
        }
        else{
            if(currentLeftBtn->isSelected()){
                rightOptions.at(currentRightBtn->getID())->setSelected(false);
                currentRightBtn = rightOptions.at(id);
                emit selectionChanged(id);
            }
        }
    }
}
void QuickLegPostureControl::setSelectedValue(const QString &text){
    for(int i = 0; i < btnOptions.length(); ++i){
        SelectableValueButton *btn = btnOptions.at(i);
        if(btn->text().compare(text) == 0){
            setSelectedValue(btn->getID());
            break;
        }
    }
}

void QuickLegPostureControl::setSelectedByValue(int value){
    for(int i = 0; i < btnOptions.length(); ++i){
        SelectableValueButton *btn = btnOptions.at(i);
        if(btn->getValue().toInt() == value){
            setSelectedValue(btn->getID());
            break;
        }
    }
}

void QuickLegPostureControl::setValues(const QStringList &texts, const QVector<QVariant> &values){
    clear();
    for(int i=0; i < texts.length(); ++i){
        SelectableValueButton *btn = new SelectableValueButton(i, values.at(i), this);
        btn->setMinimumSize(45, 45);
        btn->setText(texts.at(i));
        btnOptions.append(btn);
        mainLayout->addWidget(btn, 0, Qt::AlignVCenter);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
    }
    currentSelectedBtn = btnOptions.at(0);
    setSelectedValue(0);
}

void QuickLegPostureControl::setValues(const QStringList &texts){
    clear();
    for(int i=0; i < texts.length(); ++i){
        SelectableValueButton *btn = new SelectableValueButton(i, texts.at(i), this);
        btn->setMinimumSize(45, 45);
        btn->setText(texts.at(i));
        btnOptions.append(btn);
        mainLayout->addWidget(btn, 0, Qt::AlignVCenter);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
    }
    currentSelectedBtn = btnOptions.at(0);
    setSelectedValue(0);
}

void QuickLegPostureControl::setValues(const QStringList &texts, const QStringList &differ, const QString &label){
    clear();
    mainLayout->addWidget(new QLabel(label));
    for(int i=0; i < texts.length(); i=i+2){

        if(texts.at(i+1)=="true"){

            QHBoxLayout *generalButtonLayout = new QHBoxLayout();
            QVBoxLayout *variantButtonLayout = new QVBoxLayout();

            SelectableValueButton *btn = new SelectableValueButton(id++, QVariant(texts.at(i)), this);
            SelectableValueButton *leftBtn = new SelectableValueButton(idLeft++, QVariant(differ.at(0)), this);
            SelectableValueButton *rightBtn = new SelectableValueButton(idRight++, QVariant(differ.at(1)), this);

            btn->setMinimumSize(45, 45);
            leftBtn->setMinimumSize(45, 45);
            rightBtn->setMinimumSize(45, 45);

            btn->setText(texts.at(i));
            leftBtn->setText(differ.at(0));
            rightBtn->setText(differ.at(1));

            btnOptions.append(btn);
            leftOptions.append(leftBtn);
            rightOptions.append(rightBtn);

            variantButtonLayout->addWidget(leftBtn);
            variantButtonLayout->addWidget(rightBtn);
            generalButtonLayout->addWidget(btn, 0, Qt::AlignVCenter);
            generalButtonLayout->addLayout(variantButtonLayout);
            mainLayout->addLayout(generalButtonLayout);

            connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
            connect(leftBtn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedLeft(int)));
            connect(rightBtn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedRight(int)));
        }
        else{
            SelectableValueButton *btn = new SelectableValueButton(id++, QVariant(texts.at(i)), this);
            btn->setMinimumSize(45, 45);
            btn->setText(texts.at(i));
            btnOptions.append(btn);
            mainLayout->addWidget(btn, 0, Qt::AlignVCenter);
            connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
        }

    }

    currentSelectedBtn = btnOptions.at(0);
    currentSelectedBtn->setSelected(true);
    setSelectedValue(-1);
    if(!leftOptions.isEmpty()){
        currentLeftBtn = leftOptions.at(0);
        //currentLeftBtn->setSelected(true);
        setSelectedLeft(-1);
    }
    if(!rightOptions.isEmpty()){
        currentRightBtn = rightOptions.at(0);
        //currentRightBtn->setSelected(true);
        setSelectedRight(-1);
    }
}

//Private methods
void QuickLegPostureControl::clear(){
    btnOptions.clear();
    QLayoutItem *item;
    while((item = mainLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

//Getter and setter
QVariant QuickLegPostureControl::getSelectedValue() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->getValue();
    else
        return 0;
}

QString QuickLegPostureControl::getSelectedTexts() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->text();
    else
        return "";
}

int QuickLegPostureControl::getSelectedID() const{
    if(currentSelectedBtn != NULL)
        return currentSelectedBtn->getID();
    else
        return -1;
}
