#include "transportationlistcontrol.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "separator.h"
#include <QDebug>

/**
 * @brief Constructs a TransportationListControl widget which is a child of parent.
 * @param name A QString describing the header of the list.
 * @param optionNames a QVector pointer of QStrings containing the names of the
 * desired boolean options to be displayed.
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
TransportationListControl::TransportationListControl(QString name, QVector<QString> *optionNames, QWidget *parent) :
    QGroupBox(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    listLayout = new QVBoxLayout;
    QHBoxLayout *newNameLayout = new QHBoxLayout;
    QVBoxLayout *newLayout = new QVBoxLayout;
    QHBoxLayout *addRemLayout = new QHBoxLayout;

    // VALID IDs START AT 0
    this->currentTransportationId = -1;

    // INIT VALUES
    this->currentWeight = 0;
    this->currentMaxLoad = 0;

    // INITIALIZE OPTIONS & BUTTONS
    this->currentOptions = QVector<bool>();
    this->optionsTrueBtns = new QVector<SelectableValueButton*>;
    this->optionsFalseBtns = new QVector<SelectableValueButton*>;

    // SET THE NAME OF THE LIST
    this->name = new QLabel(this);
    this->name->setText(name);

    // ADD A ROW FOR NEW TRANSPORTATION FUNCTIONALITY
    this->newName = new QLabel(this);
    this->newName->setText("Bezeichnung");
    this->newNameEdit = new QLineEdit(this);
    this->newNameEdit->setAlignment(Qt::AlignHCenter);
    this->newNameEdit->setPlaceholderText("Neues Transportmittel");
    this->newNameEdit->setMinimumSize(400, 60);

    // BUTTONS FOR ADDING/REMOVING
    this->addBtn = new SelectableValueButton(-1, 0, this);
    this->addBtn->setText("Transportmittel erstellen");
    this->addBtn->setMinimumSize(300, 60);
    this->remBtn = new SelectableValueButton(-2, 0, this);
    this->remBtn->setText("Transportmittel entfernen");
    this->remBtn->setMinimumSize(300, 60);

    // ADD A ROW WITH DESCRIPTION FOR EACH OPTION SPECIFIED IN THE VECTOR OF STRINGS
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

    // ADD INITIAL TRANSPORTATIONS TO THE LIST, IF AVAILABLE
    this->transportations = new QList<TransportationListElement*>();
    if(!transportations->isEmpty()){
        for(int i = 0; i < transportations->length(); i++){
            listLayout->addWidget(transportations->at(i));
            connect(transportations->at(i), SIGNAL(pressedWithID(int)), this, SLOT(transportationChanged(int)));
        }
    }

    // CONNECT BUTTONS AND LINEEDIT WITH DESIRED FUNCTIONALITY
    connect(addBtn, SIGNAL(clicked()), this, SLOT(addTransportation()));
    connect(remBtn, SIGNAL(clicked()), this, SLOT(removeTransportation()));
    connect(newNameEdit, SIGNAL(textChanged(QString)), this, SLOT(disableSelection()));

    listLayout->addWidget(this->name, 0, Qt::AlignCenter);
    newNameLayout->addWidget(newName, 1, Qt::AlignLeft);
    newNameLayout->addWidget(newNameEdit, 0, Qt::AlignCenter);

    // ADD BUTTONS FOR EACH OPTION AND A SEPARATOR BETWEEN EACH TWO
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

    // VALUECONTROL FOR WEIGHT
    QVector<int>* weightValues = new QVector<int>;
    (*weightValues)<<2<<10<<50<<100<<1000;
    transportationWeight = new ValueControl(VALUE_CONTROL, this);
    transportationWeight->setValues(0, 2000, weightValues, new QString());
    transportationWeight->setUnit("kg");
    transportationWeight->setText("Leergewicht");
    optionListLayout->addWidget(transportationWeight);
    optionListLayout->addWidget(new Separator(Qt::Horizontal, 3, this));

    // VALUECONTROL FOR MAXLOAD
    QVector<int>* maxLoadValues = new QVector<int>;
    (*maxLoadValues)<<100<<500<<2500<<5000<<10000;
    transportationMaxLoad = new ValueControl(VALUE_CONTROL, this);
    transportationMaxLoad->setValues(0, 50000, maxLoadValues, new QString());
    transportationMaxLoad->setUnit("kg");
    transportationMaxLoad->setText("Maximale Last");
    optionListLayout->addWidget(transportationMaxLoad);

    connect(transportationWeight, SIGNAL(valueChanged(int)), this, SLOT(weightChanged(int)));
    connect(transportationMaxLoad, SIGNAL(valueChanged(int)), this, SLOT(maxLoadChanged(int)));

    // LAYOUT
    addRemLayout->addWidget(addBtn, 0, Qt::AlignLeft);
    addRemLayout->addWidget(remBtn, 0, Qt::AlignRight);
    newLayout->addLayout(newNameLayout);
    newLayout->addLayout(addRemLayout);
    newLayout->addLayout(optionListLayout);

    mainLayout->addLayout(listLayout);
    mainLayout->addLayout(newLayout);
    mainLayout->setAlignment(this, Qt::AlignHCenter);
    this->setLayout(mainLayout);

}

// PRIVATE SLOTS

/**
 * @brief A slot that is called, when a true button for an option is pressed.
 * @param index
 */
void TransportationListControl::optionTruePressed(int index){
    if(currentTransportationId > - 1)
        transportationWithId(currentTransportationId)->setOption(index, true);
    currentOptions.replace(index, true);
    optionChanged(index);
}

void TransportationListControl::optionFalsePressed(int index){
    if(currentTransportationId > - 1)
        transportationWithId(currentTransportationId)->setOption(index, false);
    currentOptions.replace(index, false);
    optionChanged(index);
}

void TransportationListControl::optionChanged(int index){
    optionsTrueBtns->at(index)->setSelected(currentOptions.at(index));
    optionsFalseBtns->at(index)->setSelected(!currentOptions.at(index));
}

void TransportationListControl::weightChanged(int newWeight){
    currentWeight = newWeight;
    if(currentTransportationId > -1)
        transportationWithId(currentTransportationId)->setWeight(newWeight);
}

void TransportationListControl::maxLoadChanged(int newMaxLoad){
    currentMaxLoad = newMaxLoad;
    if(currentTransportationId > -1)
        transportationWithId(currentTransportationId)->setMaxLoad(newMaxLoad);
}


void TransportationListControl::transportationChanged(int id)
{
   setCurrentTransportationId(id);
   TransportationListElement* t = transportationWithId(id);
   for(int i = 0; i < options->length(); i++){
       optionsTrueBtns->at(i)->setSelected(t->getOption(i));
       optionsFalseBtns->at(i)->setSelected(!t->getOption(i));
       transportationWeight->setValue(t->getWeight());
       transportationMaxLoad->setValue(t->getMaxLoad());
   }
}

void TransportationListControl::setCurrentTransportationId(int id)
{
    if(currentTransportationId > -1 && transportationWithId(currentTransportationId) != NULL)
        transportationWithId(currentTransportationId)->setSelected(false);
    currentTransportationId = id;
    if(currentTransportationId > -1 && transportationWithId(currentTransportationId) != NULL)
        transportationWithId(currentTransportationId)->setSelected(true);
}

void TransportationListControl::disableSelection(){
    if(currentTransportationId > -1 && !transportations->isEmpty() && (newNameEdit->text() != "")){
        transportationWithId(currentTransportationId)->setSelected(false);
        for(int i = 0; i < options->length(); i++){
            currentOptions.replace(i, false);
            optionsTrueBtns->at(i)->setSelected(false);
            optionsFalseBtns->at(i)->setSelected(false);
        }
    }
    this->transportationWeight->setValue(0);
    this->transportationMaxLoad->setValue(0);
    setCurrentTransportationId(-1);
}

void TransportationListControl::addTransportation()
{
    if(newNameEdit->text() != ""){

        TransportationListElement *t = new TransportationListElement(newNameEdit->text(), currentOptions, currentWeight, currentMaxLoad, this);
        t->setMinimumSize(100, 60);
        transportations->append(t);
        connect(t, SIGNAL(pressedWithID(int)), this, SLOT(transportationChanged(int)));
        this->listLayout->addWidget(t);
        newNameEdit->clear();

        for(int i = 0; i < options->length(); i++){
            optionsTrueBtns->at(i)->setSelected(false);
            optionsFalseBtns->at(i)->setSelected(false);
        }

        this->transportationWeight->setValue(0);
        this->transportationMaxLoad->setValue(0);

    }
}

void TransportationListControl::removeTransportation(){
    if(!transportations->isEmpty() && currentTransportationId > -1){
        int indexToRemove = transportationIndex(currentTransportationId);
        delete transportationWithId(currentTransportationId);
        transportations->removeAt(indexToRemove);

        for(int i = 0; i < options->length(); i++){
            optionsTrueBtns->at(i)->setSelected(false);
            optionsFalseBtns->at(i)->setSelected(false);
        }

        setCurrentTransportationId(-1);
        this->transportationWeight->setValue(0);
        this->transportationMaxLoad->setValue(0);
    }
}


// PRIVATE FUNCTIONS
TransportationListElement* TransportationListControl::transportationWithId(int id){
    for(int i = 0; i < transportations->length(); i++)
        if(transportations->at(i)->getID() == id)
            return transportations->at(i);
    return NULL;
}

int TransportationListControl::transportationIndex(int transportationId){
    for(int i = 0; i < transportations->length(); i++)
        if(transportations->at(i)->getID() == transportationId)
            return i;
    return -1;
}
