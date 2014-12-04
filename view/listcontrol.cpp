    #include "listcontrol.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "separator.h"

ListControl::ListControl(QString name, QVector<QString> *optionNames, QWidget *parent) :
    QGroupBox(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QVBoxLayout *listLayout = new QVBoxLayout;
    QHBoxLayout *listHLayout = new QHBoxLayout;
    QHBoxLayout *newNameLayout = new QHBoxLayout;
    QVBoxLayout *newLayout = new QVBoxLayout;
    QHBoxLayout *addRemLayout = new QHBoxLayout;

    currentTransportationId = -1;

    this->currentOptions = QVector<bool>();
    this->optionsTrueBtns = new QVector<SelectableValueButton*>;
    this->optionsFalseBtns = new QVector<SelectableValueButton*>;

    this->name = new QLabel(this);
    this->name->setText(name);
    this->newName = new QLabel(this);
    this->newName->setText("Bezeichnung");
    this->newNameEdit = new QLineEdit(this);
    this->newNameEdit->setPlaceholderText("Neues Transportmittel");
    this->newNameEdit->setMinimumHeight(60);
    this->addBtn = new SelectableValueButton(-1, 0, this);
    this->addBtn->setMinimumHeight(60);
    this->addBtn->setText("Transportmittel erstellen");
    this->addBtn->setMaximumWidth(300);
    this->remBtn = new SelectableValueButton(-2, 0, this);
    this->remBtn->setText("Transportmittel entfernen");
    this->remBtn->setMinimumHeight(60);
    this->remBtn->setMaximumWidth(300);

    this->options = new QVector<QLabel*>();
    for(int i = 0; i < optionNames->length(); i++){
        QLabel* option = new QLabel(this);
        option->setText(optionNames->at(i));
        options->append(option);

        SelectableValueButton* trueButton = new SelectableValueButton(i, 1, this);
        trueButton->setText("Ja");
        trueButton->setFixedSize(100, 60);
        optionsTrueBtns->append(trueButton);
        connect(trueButton, SIGNAL(pressedWithID(int)), this, SLOT(optionTruePressed(int)));

        SelectableValueButton* falseButton = new SelectableValueButton(i, 0, this);
        falseButton->setText("Nein");
        falseButton->setFixedSize(100, 60);
        optionsFalseBtns->append(falseButton);
        connect(falseButton, SIGNAL(pressedWithID(int)), this, SLOT(optionFalsePressed(int)));

        currentOptions.append(false);
    }

    this->transportations = new QList<Transportation*>();

    if(!transportations->isEmpty()){
        for(int i = 0; i < transportations->length(); i++){
            listLayout->addWidget(transportations->at(i));
            connect(transportations->at(i), SIGNAL(pressedWithID(int)), this, SLOT(transportationChanged(int)));
        }
    }

    connect(addBtn, SIGNAL(clicked()), this, SLOT(addTransportation()));
    connect(remBtn, SIGNAL(clicked()), this, SLOT(removeTransportation()));
    connect(newNameEdit, SIGNAL(textChanged(QString)), this, SLOT(disableSelection()));

    listHLayout->addWidget(this->name, 0, Qt::AlignCenter);
    listHLayout->addLayout(listLayout);

    newNameLayout->addWidget(newName);
    newNameLayout->addWidget(newNameEdit);

    QVBoxLayout *optionListLayout = new QVBoxLayout;
    optionListLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    for(int i = 0; i < options->length(); i++){
        QHBoxLayout *optionLayout = new QHBoxLayout;
        optionLayout->addWidget(options->at(i));
        optionLayout->addWidget(optionsTrueBtns->at(i));
        optionLayout->addWidget(optionsFalseBtns->at(i));
        optionListLayout->addLayout(optionLayout);
        optionListLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    }

    QVector<int>* weightValues = new QVector<int>;
    (*weightValues)<<2<<10<<50<<100<<1000;
    transportationWeight = new ValueControl(VALUE_CONTROL, this);
    transportationWeight->setValues(0, 2000, weightValues, new QString());
    transportationWeight->setUnit("kg");
    transportationWeight->setText("Leergewicht");
    optionListLayout->addWidget(transportationWeight);
    optionListLayout->addWidget(new Separator(Qt::Horizontal, 3, this));

    QVector<int>* maxLoadValues = new QVector<int>;
    (*maxLoadValues)<<100<<500<<2500<<500<<10000;
    transportationMaxLoad = new ValueControl(VALUE_CONTROL, this);
    transportationMaxLoad->setValues(0, 50000, maxLoadValues, new QString());
    transportationMaxLoad->setUnit("kg");
    transportationMaxLoad->setText("Maximale Last");
    optionListLayout->addWidget(transportationMaxLoad);

    addRemLayout->addWidget(addBtn);
    addRemLayout->addWidget(remBtn);
    newLayout->addLayout(newNameLayout);
    newLayout->addLayout(addRemLayout);
    newLayout->addLayout(optionListLayout);

    mainLayout->addLayout(listHLayout);
    mainLayout->addLayout(newLayout);
    mainLayout->setAlignment(this, Qt::AlignHCenter);
    this->setLayout(mainLayout);

}


void ListControl::optionTruePressed(int index){
    if(currentTransportationId > - 1)
        transportationWithId(currentTransportationId)->setOption(index, true);
    currentOptions.replace(index, true);
    optionChanged(index);
}

void ListControl::optionFalsePressed(int index){
    if(currentTransportationId > - 1)
        transportationWithId(currentTransportationId)->setOption(index, false);
    currentOptions.replace(index, false);
    optionChanged(index);
}

void ListControl::optionChanged(int index){
    optionsTrueBtns->at(index)->setSelected(currentOptions.at(index));
    optionsFalseBtns->at(index)->setSelected(!currentOptions.at(index));
}


void ListControl::transportationChanged(int id)
{
   setCurrentTransportationId(id);
   for(int i = 0; i < options->length(); i++){
       optionsTrueBtns->at(i)->setSelected(transportationWithId(id)->getOption(i));
       optionsFalseBtns->at(i)->setSelected(!transportationWithId(id)->getOption(i));
   }
}

void ListControl::setCurrentTransportationId(int id)
{
    if(currentTransportationId > -1 && transportationWithId(currentTransportationId) != NULL)
        transportationWithId(currentTransportationId)->setSelected(false);
    currentTransportationId = id;
    if(currentTransportationId > -1 && transportationWithId(currentTransportationId) != NULL)
        transportationWithId(currentTransportationId)->setSelected(true);
}

void ListControl::disableSelection(){
    if(currentTransportationId > -1 && !transportations->isEmpty() && (newNameEdit->text() != "")){
        transportationWithId(currentTransportationId)->setSelected(false);
        for(int i = 0; i < options->length(); i++){
            optionsTrueBtns->at(i)->setSelected(false);
            optionsFalseBtns->at(i)->setSelected(false);
        }
    }
    setCurrentTransportationId(-1);
}

bool ListControl::isOptionChosen(){
    bool optionChosen = false;
    for(int i = 0; i < options->length(); i++){
        optionChosen = (optionsFalseBtns->at(i)->isSelected() || optionsTrueBtns->at(i)->isSelected());
        if(optionChosen == false)
            return false;
    }
    return true;
}

void ListControl::addTransportation()
{
    if(newNameEdit->text() != "" && isOptionChosen()){

        Transportation *t = new Transportation(newNameEdit->text(), currentOptions, 0, this);
        t->setMinimumSize(100, 60);
        transportations->append(t);
        connect(t, SIGNAL(pressedWithID(int)), this, SLOT(transportationChanged(int)));
        this->layout()->itemAt(0)->layout()->itemAt(1)->layout()->addWidget(t);
        newNameEdit->clear();

        for(int i = 0; i < options->length(); i++){
            optionsTrueBtns->at(i)->setSelected(false);
            optionsFalseBtns->at(i)->setSelected(false);
        }

    }
}

void ListControl::removeTransportation(){
    if(!transportations->isEmpty() && currentTransportationId > -1){
        int indexToRemove = transportationIndex(currentTransportationId);
        delete transportationWithId(currentTransportationId);
        transportations->removeAt(indexToRemove);

        for(int i = 0; i < options->length(); i++){
            optionsTrueBtns->at(i)->setSelected(false);
            optionsFalseBtns->at(i)->setSelected(false);
        }

        setCurrentTransportationId(-1);
    }
}

Transportation* ListControl::transportationWithId(int id){
    for(int i = 0; i < transportations->length(); i++)
        if(transportations->at(i)->getID() == id)
            return transportations->at(i);
    return NULL;
}

int ListControl::transportationIndex(int transportationId){
    for(int i = 0; i < transportations->length(); i++)
        if(transportations->at(i)->getID() == transportationId)
            return i;
    return -1;
}
