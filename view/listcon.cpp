#include "listcon.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QErrorMessage>
#include <QDebug>

ListCon::ListCon(QString name, QVector<QString> *optionNames, QWidget *parent) :
    QGroupBox(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QVBoxLayout *listLayout = new QVBoxLayout;
    QHBoxLayout *listHLayout = new QHBoxLayout;
    QHBoxLayout *newNameLayout = new QHBoxLayout;
    QVBoxLayout *newLayout = new QVBoxLayout;
    QHBoxLayout *addRemLayout = new QHBoxLayout;

    currentToolId = -1;

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

    this->tools = new QList<Tool*>();

    if(!tools->isEmpty()){
        for(int i = 0; i < tools->length(); i++){
            listLayout->addWidget(tools->at(i));
            connect(tools->at(i), SIGNAL(pressedWithID(int)), this, SLOT(toolChanged(int)));
        }
    }

    connect(addBtn, SIGNAL(clicked()), this, SLOT(addTool()));
    connect(remBtn, SIGNAL(clicked()), this, SLOT(removeTool()));
    connect(newNameEdit, SIGNAL(textChanged(QString)), this, SLOT(disableSelection()));

    listHLayout->addWidget(this->name, 0, Qt::AlignCenter);
    listHLayout->addLayout(listLayout);

    newNameLayout->addWidget(newName);
    newNameLayout->addWidget(newNameEdit);

    QVBoxLayout *optionListLayout = new QVBoxLayout;
    for(int i = 0; i < options->length(); i++){
        QHBoxLayout *optionLayout = new QHBoxLayout;
        optionLayout->addWidget(options->at(i));
        optionLayout->addWidget(optionsTrueBtns->at(i));
        optionLayout->addWidget(optionsFalseBtns->at(i));
        optionListLayout->addLayout(optionLayout);
    }

    addRemLayout->addWidget(addBtn);
    addRemLayout->addWidget(remBtn);
    newLayout->addLayout(newNameLayout);
    newLayout->addLayout(optionListLayout);
    newLayout->addLayout(addRemLayout);

    mainLayout->addLayout(listHLayout);
    mainLayout->addLayout(newLayout);
    mainLayout->setAlignment(this, Qt::AlignHCenter);
    this->setLayout(mainLayout);

}


void ListCon::optionTruePressed(int index){
    if(currentToolId > - 1)
        toolWidthId(currentToolId)->setOption(index, true);
    currentOptions.replace(index, true);
    optionChanged(index);
}

void ListCon::optionFalsePressed(int index){
    if(currentToolId > - 1)
        toolWidthId(currentToolId)->setOption(index, false);
    currentOptions.replace(index, false);
    optionChanged(index);
}

void ListCon::optionChanged(int index){
    optionsTrueBtns->at(index)->setSelected(currentOptions.at(index));
    optionsFalseBtns->at(index)->setSelected(!currentOptions.at(index));
}


void ListCon::toolChanged(int id)
{
   setCurrentToolId(id);
   for(int i = 0; i < options->length(); i++){
       optionsTrueBtns->at(i)->setSelected(toolWidthId(id)->getOption(i));
       optionsFalseBtns->at(i)->setSelected(!toolWidthId(id)->getOption(i));
   }
}

void ListCon::setCurrentToolId(int id)
{
    if(currentToolId > -1 && toolWidthId(currentToolId) != NULL)
        toolWidthId(currentToolId)->setSelected(false);
    currentToolId = id;
    if(currentToolId > -1 && toolWidthId(currentToolId) != NULL)
        toolWidthId(currentToolId)->setSelected(true);
}

void ListCon::disableSelection(){
    if(currentToolId > -1 && !tools->isEmpty() && (newNameEdit->text() != "")){
        toolWidthId(currentToolId)->setSelected(false);
        for(int i = 0; i < options->length(); i++){
            optionsTrueBtns->at(i)->setSelected(false);
            optionsFalseBtns->at(i)->setSelected(false);
        }
    }
    setCurrentToolId(-1);
}

bool ListCon::isOptionChosen(){
    bool optionChosen = false;
    for(int i = 0; i < options->length(); i++){
        optionChosen = (optionsFalseBtns->at(i)->isSelected() || optionsTrueBtns->at(i)->isSelected());
        if(optionChosen == false)
            return false;
    }
    return true;
}

void ListCon::addTool()
{
    if(newNameEdit->text() != "" && isOptionChosen()){

        Tool *t = new Tool(newNameEdit->text(), currentOptions, this);
        t->setMinimumSize(100, 60);
        tools->append(t);
        connect(t, SIGNAL(pressedWithID(int)), this, SLOT(toolChanged(int)));
        this->layout()->itemAt(0)->layout()->itemAt(1)->layout()->addWidget(t);
        newNameEdit->clear();

        for(int i = 0; i < options->length(); i++){
            optionsTrueBtns->at(i)->setSelected(false);
            optionsFalseBtns->at(i)->setSelected(false);
        }

    }
    else {
        QErrorMessage *e = new QErrorMessage(this);
        e->showMessage("Sie müssen einen Namen und Attribute für das Hilfsmittel eingeben", "OK");
    }
}

void ListCon::removeTool(){
    if(!tools->isEmpty() && currentToolId > -1){
        int indexToRemove = toolIndex(currentToolId);
        delete toolWidthId(currentToolId);
        tools->removeAt(indexToRemove);

        for(int i = 0; i < options->length(); i++){
            optionsTrueBtns->at(i)->setSelected(false);
            optionsFalseBtns->at(i)->setSelected(false);
        }

        setCurrentToolId(-1);
    }
}

Tool* ListCon::toolWidthId(int id){
    for(int i = 0; i < tools->length(); i++)
        if(tools->at(i)->getID() == id)
            return tools->at(i);
    return NULL;
}

int ListCon::toolIndex(int toolId){
    for(int i = 0; i < tools->length(); i++)
        if(tools->at(i)->getID() == toolId)
            return i;
    return -1;
}
