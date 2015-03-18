#include "variantcontrol.h"
#include "../../separator.h"

VariantControl::VariantControl(QWidget *parent) : QWidget(parent),
    name(QString("")),
    variantsLayout(new QVBoxLayout),
    valueControlLayout(new QVBoxLayout),
    mainContent(new QWidget()),
    btnName(new QPushButton()),
    hasSpeci(false),
    svBtnCurrentSel(0),
    valueControls(new QVector<QVector<ValueControl*>*>()),
    variantBtns(new QVector<SelectableValueButton*>()),
    shown(false)
{
    btnName->setMaximumWidth(150);
    connect(btnName, SIGNAL(clicked()), this, SLOT(btnNameClicked()));

    QHBoxLayout *mainContentLayout = new QHBoxLayout;
    mainContentLayout->addLayout(variantsLayout);
    mainContentLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    mainContentLayout->addLayout(valueControlLayout);
    mainContent->setLayout(mainContentLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(btnName);
    mainLayout->addWidget(mainContent);

    this->setLayout(mainLayout);
}

VariantControl::~VariantControl()
{

}

//PUBLIC METHODS
int VariantControl::addVariant(const QString &name){
    SelectableValueButton *btn = new SelectableValueButton(valueControls->length(), valueControls->length());
    btn->setText(name);
    btn->setMinimumWidth(150);
    variantBtns->append(btn);
    variantsLayout->addWidget(btn);
    valueControls->append(new QVector<ValueControl*>());
    connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(btnVariantClicked(int)));
    return valueControls->length() - 1;
}

int VariantControl::addSubVariant(int variantID, ValueControl *vc){
    QVector<ValueControl*> *conList = valueControls->at(variantID);
    conList->append(vc);
    valueControlLayout->addWidget(vc);
    vc->hide();
    connect(vc, SIGNAL(valueChanged(QVariant)), this, SIGNAL(valueChanged(QVariant)));
    connect(vc, SIGNAL(valueChanged(QVariant)), this, SLOT(vcValueChanged(QVariant)));
    return conList->length() - 1;
}

void VariantControl::setSpecification(VariantSpecification *varSpeci){
    this->varSpeci = varSpeci;
    variantsLayout->addWidget(varSpeci);
    variantsLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
    hasSpeci = true;
}

void VariantControl::setSelectedSpecification(AVType type){
    if(hasSpeci)
        varSpeci->setSelected(type);
}

void VariantControl::setExclusiveDisplayByName(const QString &name){
    if((name.compare(this->name) == 0) && !shown){
        showContent();
        shown = true;
    }
    else{
        hideContent();
        shown = false;
    }
}


//PUBLIC SLOTS
void VariantControl::hideContent(){
    mainContent->hide();
}

void VariantControl::showContent(){
    mainContent->show();
}

void VariantControl::setName(const QString &name){
    this->name = name;
}

void VariantControl::setButtonIcon(const QString &objectName, const QSize &size){
    btnName->setObjectName(objectName);
    btnName->setFixedSize(size);
}

void VariantControl::setSelectedVariant(int variantID){
    for(int i = 0; i < variantBtns->length(); ++i){
        SelectableValueButton* btn = variantBtns->at(i);
        if(btn->getID() == variantID){
            btnVariantClicked(variantID);
            break;
        }
    }
}


//PRIVATE SLOTS
void VariantControl::btnVariantClicked(int id){
    SelectableValueButton *btn = variantBtns->at(id);
    if(svBtnCurrentSel != NULL){
        QVector<ValueControl*> *oldControls = valueControls->at(svBtnCurrentSel->getValue().toInt());
        svBtnCurrentSel->setSelected(false);
        for(int i = 0; i < oldControls->length(); ++i)
            oldControls->at(i)->hide();
    }
    QVector<ValueControl*> *controls = valueControls->at(id);
    svBtnCurrentSel = btn;
    svBtnCurrentSel->setSelected(true);
    for(int i = 0; i < controls->length(); ++i){
        controls->at(i)->show();
    }
}

void VariantControl::vcValueChanged(const QVariant &value){
    if(hasSpeci)
        emit valueChanged(varSpeci->getSelectedID(), value);
}

void VariantControl::btnNameClicked() {
    emit requestShowContent(this->name);
}

//GETTER/SETTER
QString VariantControl::getName() const{
    return this->name;
}

int VariantControl::getValue(int variantID, int subVariantID) const{
    return valueControls->at(variantID)->at(subVariantID)->getValue();
}

QString VariantControl::getTextValue(int variantID, int subVariantID) const{
    return valueControls->at(variantID)->at(subVariantID)->getTextValue();
}
