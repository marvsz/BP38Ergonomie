#include "workprocesstypepicker.h"
#include <QHBoxLayout>

WorkProcessTypePicker::WorkProcessTypePicker(QWidget *parent) : QWidget(parent),
    btnLeft(new SelectableValueButton(AVType::LEFT, AVType::LEFT)),
    btnRight(new SelectableValueButton(AVType::RIGHT, AVType::RIGHT)),
    btnBasic(new SelectableValueButton(AVType::BASIC, AVType::BASIC)),
    selectedType(AVType::BASIC)
{
    btnLeft->setText(tr("Left"));
    btnLeft->setMinimumSize(45, 45);
    btnRight->setText(tr("Right"));
    btnRight->setMinimumSize(45, 45);
    btnBasic->setText(tr("AV"));
    btnBasic->setMinimumSize(45, 45);
    connect(btnLeft, SIGNAL(clickedWithID(int)), this, SLOT(btnAVTypeClicked(int)));
    connect(btnRight, SIGNAL(clickedWithID(int)), this, SLOT(btnAVTypeClicked(int)));
    connect(btnBasic, SIGNAL(clickedWithID(int)), this, SLOT(btnAVTypeClicked(int)));
    btnBasic->setSelected(true);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(btnLeft);
    mainLayout->addWidget(btnRight);
    mainLayout->addWidget(btnBasic);
    this->setLayout(mainLayout);
}

WorkProcessTypePicker::~WorkProcessTypePicker()
{

}

//PUBLIC SLOTS
void WorkProcessTypePicker::setSelectedType(AVType type){
    setSelectedType(type, false);
}

//PRIVATE SLOTS
void WorkProcessTypePicker::btnAVTypeClicked(int id){
    setSelectedType((AVType) id, true);
}


//PRIVATE METHODS
SelectableValueButton* WorkProcessTypePicker::getBtnByType(AVType type){
    switch(type){
        case AVType::LEFT: return btnLeft; break;
        case AVType::RIGHT: return btnRight; break;
        case AVType::BASIC: return btnBasic; break;
        default: return btnBasic; break;
    }
}

void WorkProcessTypePicker::setSelectedType(AVType type, bool emitSignal){
    if(selectedType != type){
        getBtnByType(selectedType)->setSelected(false);
        getBtnByType(type)->setSelected(true);
        selectedType = type;
        if(emitSignal)
            emit selectedTypeChanged(type);
    }
}


//GETTER
AVType WorkProcessTypePicker::getSelectedType() const{
    return selectedType;
}
