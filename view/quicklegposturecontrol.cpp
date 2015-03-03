#include "quicklegposturecontrol.h"
#include <QLabel>

QuickLegPostureControl::QuickLegPostureControl(QWidget *parent) :
    QWidget(parent),
    btnOptions(QVector<SelectableValueButton*>()),
    speciOptions(QVector<SelectableValueButton*>()),
    //leftOptions(QVector<SelectableValueButton*>()),
    //rightOptions(QVector<SelectableValueButton*>()),
    mainLayout(new QVBoxLayout),
    id(0),
    idSpeci(0)
    //idLeft(0),
    //idRight(0)
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
        //emit selectionChanged(id);
        if(currentSelectedBtn->getID()==2){
            speciOptions.at(0)->setSelected(true);
            speciOptions.at(1)->setSelected(true);
            emit selectionChanged(id,2);
            if(speciOptions.at(0)->isSelected()&&speciOptions.at(1)->isSelected()){
                emit selectionChanged(id,2);
            }
            else{
                if(speciOptions.at(0)->isSelected()){
                    emit selectionChanged(id,0);
                }
                if(speciOptions.at(1)->isSelected()){
                    emit selectionChanged(id,1);
                }

            }
        }
        else{
            speciOptions.at(0)->setSelected(false);
            speciOptions.at(1)->setSelected(false);
            emit selectionChanged(id,3);
        }



    }
}

void QuickLegPostureControl::setSelectedSpecification(int id){
    if(id >= 0 && id < speciOptions.length() && currentSpeciBtn != NULL && currentSelectedBtn->getID() == 2){
        switch (id) {
        case 0:
            if(!speciOptions.at(0)->isSelected()){
                speciOptions.at(0)->setSelected(true);
                emit specificationChanged(2);
            }
            else{
                if(speciOptions.at(0)->isSelected()&&speciOptions.at(1)->isSelected()){
                    speciOptions.at(0)->setSelected(false);
                    emit specificationChanged(1);
                }
            }
            break;
        case 1:
            if(!speciOptions.at(1)->isSelected()){
                speciOptions.at(1)->setSelected(true);
                emit specificationChanged(2);
            }
            else{
                if(speciOptions.at(1)->isSelected()&&speciOptions.at(0)->isSelected()){
                    speciOptions.at(1)->setSelected(false);
                    emit specificationChanged(0);
                }
            }
            break;
        default:
            break;
        }

        /*
        if(currentSpeciBtn->getID() != id){
            //speciOptions.at(currentSpeciBtn->getID())->setSelected(false);
            currentSpeciBtn = speciOptions.at(id);
            currentSpeciBtn->setSelected(true);
            emit specificationChanged(id);
        }
        else{
            //if(currentSpeciBtn->isSelected()){
                speciOptions.at(currentSpeciBtn->getID())->setSelected(false);
                currentSpeciBtn = speciOptions.at(id);
                emit specificationChanged(id);
            //}
        }*/
    }
}

/*void QuickLegPostureControl::setSelectedLeft(int id){
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
}*/
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
            SelectableValueButton *leftBtn = new SelectableValueButton(idSpeci++, QVariant(differ.at(0)), this);
            SelectableValueButton *rightBtn = new SelectableValueButton(idSpeci++, QVariant(differ.at(1)), this);

            btn->setMinimumSize(45, 45);
            leftBtn->setMinimumSize(45, 45);
            rightBtn->setMinimumSize(45, 45);

            btn->setText(texts.at(i));
            leftBtn->setText(differ.at(0));
            rightBtn->setText(differ.at(1));

            btnOptions.append(btn);
            speciOptions.append(leftBtn);
            speciOptions.append(rightBtn);

            variantButtonLayout->addWidget(leftBtn);
            variantButtonLayout->addWidget(rightBtn);
            generalButtonLayout->addWidget(btn, 0, Qt::AlignVCenter);
            generalButtonLayout->addLayout(variantButtonLayout);
            mainLayout->addLayout(generalButtonLayout);

            connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedValue(int)));
            connect(leftBtn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedSpecification(int)));
            connect(rightBtn, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedSpecification(int)));
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
    if(!speciOptions.isEmpty()){
        currentSpeciBtn = speciOptions.at(0);
        //currentLeftBtn->setSelected(true);
        setSelectedSpecification(0);
    }
    if(!speciOptions.isEmpty()){
        currentSpeciBtn = speciOptions.at(1);
        //currentRightBtn->setSelected(true);
        setSelectedSpecification(1);
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
