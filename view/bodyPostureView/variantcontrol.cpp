#include "variantcontrol.h"
#include "separator.h"

VariantControl::VariantControl(QWidget *parent) : QWidget(parent),
    variantsLayout(new QVBoxLayout),
    valueControlLayout(new QVBoxLayout),
    mainContent(new QWidget()),
    btnName(new QPushButton()),
    valueControls(new QVector<QVector<ValueControl*>*>())
{
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
    variantsLayout->addWidget(btn);
    valueControls->append(new QVector<ValueControl*>());
    connect(btn, SIGNAL(clickedWithID(int,SelectableValueButton*)), this, SLOT(btnVariantClicked(int,SelectableValueButton*)));
}

int VariantControl::addSubVariant(int variantID, ValueControl *vc){
    QVector<ValueControl*> *conList = valueControls->at(variantID);
    conList->append(vc);
    connect(vc, SIGNAL(valueChanged(QVariant)), this, SIGNAL(valueChanged(QVariant)));
    connect(vc, SIGNAL(valueChanged(QVariant)), this, SLOT(vcValueChanged(QVariant)));
}

void VariantControl::setSpecification(VariantSpecification *varSpeci){
    this->varSpeci = varSpeci;
    variantsLayout->addWidget(varSpeci);
}

void VariantControl::setSelectedSpecification(int speciID){
    if(varSpeci != NULL)
        varSpeci->setSelected(speciID);
}


//PUBLIC SLOTS
void VariantControl::hideContent(){
    mainContent->hide();
}

void VariantControl::showContent(){
    mainContent->show();
}

void VariantControl::setName(const QString &name){
    btnName->setText(name);
}

void VariantControl::setSelectedVariant(int variantID){
    btnVariantClicked(variantID, NULL);
}


//PRIVATE SLOTS
void VariantControl::btnVariantClicked(int id, SelectableValueButton *btn){
    if(svBtnCurrentSel != NULL){
        QVector<ValueControl*> *oldControls = valueControls->at(svBtnCurrentSel->getValue().toInt());
        svBtnCurrentSel->setSelected(false);
        for(int i = 0; i < oldControls->length(); ++i)
            oldControls->at(i)->hide();
    }
    QVector<ValueControl*> *controls = valueControls->at(id);
    svBtnCurrentSel = btn;
    svBtnCurrentSel->setSelected(true);
    for(int i = 0; i < controls->length(); ++i)
        controls->at(i)->show();
}

void VariantControl::vcValueChanged(const QVariant &value){
    if(varSpeci != NULL)
        emit valueChanged(varSpeci->getSelectedID(), value);
}


//GETTER/SETTER
QString VariantControl::getName() const{
    return btnName->text();
}

int VariantControl::getValue(int variantID, int subVariantID) const{
    return valueControls->at(variantID)->at(subVariantID)->getValue();
}

QString VariantControl::getTextValue(int variantID, int subVariantID) const{
    return valueControls->at(variantID)->at(subVariantID)->getTextValue();
}
