#include "quicklegposturecontrol.h"
#include <QLabel>

QuickLegPostureControl::QuickLegPostureControl(QWidget *parent) :
    QWidget(parent),
    btnOptions(QVector<SelectableValueButton*>()),
    speciOptions(QVector<SelectableValueButton*>()),
    mainLayout(new QVBoxLayout),
    id(1),
    idSpeci(1),
    specification(3)
{
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);
}


//Public slots
void QuickLegPostureControl::setSelectedValue(int id){
    if(id >= 1 && id < btnOptions.length()+1 && currentSelectedBtn != NULL && currentSelectedBtn->getID() != id){
        btnOptions.at(currentSelectedBtn->getID()-1)->setSelected(false);
        currentSelectedBtn = btnOptions.at(id-1);
        currentSelectedBtn->setSelected(true);
        if(currentSelectedBtn->getID()==3){
            if(!speciOptions.at(0)->isSelected() && !speciOptions.at(1)->isSelected()){
                emit setSelectedSpecification(1);
                emit setSelectedSpecification(2);
            }
            specification = 3;
            emit selectionChanged(id,3);
            if(speciOptions.at(0)->isSelected()&&speciOptions.at(1)->isSelected()){
                specification = 3;
                emit selectionChanged(id,3);

            }
            else{
                if(speciOptions.at(0)->isSelected()){
                    specification = 1;
                    emit selectionChanged(id,1);

                }
                if(speciOptions.at(1)->isSelected()){
                    specification = 2;
                    emit selectionChanged(id,2);

                }

            }
        }
        else{
            speciOptions.at(0)->setSelected(false);
            speciOptions.at(1)->setSelected(false);
            specification = 3;
            emit selectionChanged(id,3);

        }



    }
    else if(currentSelectedBtn->getID() == id){
        currentSelectedBtn->setSelected(true);
    }
}

void QuickLegPostureControl::setSelectedSpecification(int id){
    if(id >= 0 && id < speciOptions.length()+1 && currentSpeciBtn != NULL){

        switch (id) {
        case 1:
            if(speciOptions.at(0)->isSelected()&&speciOptions.at(1)->isSelected()){
                speciOptions.at(0)->setSelected(false);
                specification = 2;
                emit specificationChanged(2);
                emit setSelectedValue(3);
                emit selectionChanged(3,2);

            }
            else{
                if(!speciOptions.at(0)->isSelected()&&speciOptions.at(1)->isSelected()){
                    speciOptions.at(0)->setSelected(true);
                    specification = 3;
                    emit specificationChanged(3);
                    emit setSelectedValue(3);
                    emit selectionChanged(3,3);
                }


                    else{
                        speciOptions.at(0)->setSelected(true);
                        specification = 1;
                        emit setSelectedValue(3);
                        emit selectionChanged(3,1);
                }
            }


            break;
        case 2:
            if(speciOptions.at(1)->isSelected()&&speciOptions.at(0)->isSelected()){
                speciOptions.at(1)->setSelected(false);
                specification = 1;
                emit specificationChanged(1);
                emit setSelectedValue(3);
                emit selectionChanged(3,1);

            }else{

            if(!speciOptions.at(1)->isSelected()&&speciOptions.at(0)->isSelected()){
                speciOptions.at(1)->setSelected(true);
                specification = 3;
                emit specificationChanged(3);
                emit setSelectedValue(3);
                emit selectionChanged(3,3);
            }


                else{
                    speciOptions.at(1)->setSelected(true);
                    specification = 2;
                    emit setSelectedValue(3);
                    emit selectionChanged(3,2);
                }
            }
            break;
        default:
            break;
        }
    }
    else{
        speciOptions.at(0)->setSelected(false);
        speciOptions.at(1)->setSelected(false);
        specification = 3;
    }
}


void QuickLegPostureControl::setValues(const QStringList &texts, const QStringList &differ, const QString &label){
    clear();
    QLabel *lblName = new QLabel(label);
    lblName->setObjectName("lblHeader");
    mainLayout->addWidget(lblName, 0, Qt::AlignHCenter);
    QHBoxLayout *generalButtonLayout = new QHBoxLayout();
    QVBoxLayout *variantButtonLayout = new QVBoxLayout();

    for(int i=0; i < texts.length(); i=i+2){

        if(texts.at(i+1)=="true"){
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
    speciOptions.at(0)->setSelected(false);
    speciOptions.at(1)->setSelected(false);
    currentSelectedBtn = btnOptions.at(0);
    currentSelectedBtn->setSelected(true);
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
        return 0;
}

int QuickLegPostureControl::getSelectedSpecification() const{
        return this->specification;
}
