#include "listcon.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QErrorMessage>

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
    this->optionsTrueBtns = new QVector<TextQPushButton*>;
    this->optionsFalseBtns = new QVector<TextQPushButton*>;

    this->name = new QLabel(this);
    this->name->setText(name);
    this->newName = new QLabel(this);
    this->newName->setText("Bezeichnung");
    this->newNameEdit = new QLineEdit(this);
    this->newNameEdit->setPlaceholderText("Neues Hilfsmittel");
    this->newNameEdit->setMinimumHeight(60);
    this->addBtn = new TextQPushButton(4, "Hilfsmittel hinzufügen", this);
    this->addBtn->setMinimumHeight(60);
    this->addBtn->setMaximumWidth(300);
    this->remBtn = new TextQPushButton(5, "Hilfsmittel entfernen", this);
    this->remBtn->setMinimumHeight(60);
    this->remBtn->setMaximumWidth(300);

    this->options = new QVector<QLabel*>();
    for(int i = 0; i < optionNames->length(); i++){
        QLabel* option = new QLabel(this);
        option->setText(optionNames->at(i));
        options->append(option);

        TextQPushButton* trueButton = new TextQPushButton(i, "Ja", this);
        trueButton->setFixedSize(100, 60);
        optionsTrueBtns->append(trueButton);
        connect(trueButton, SIGNAL(pressedWithID(int)), this, SLOT(optionTruePressed(int)));

        TextQPushButton* falseButton = new TextQPushButton(i, "Nein", this);
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
        tools->at(currentToolId)->setOption(index, true);
    currentOptions.replace(index, true);
    optionChanged(index);
}

void ListCon::optionFalsePressed(int index){
    if(currentToolId > - 1)
        tools->at(currentToolId)->setOption(index, false);
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
       optionsTrueBtns->at(i)->setSelected(tools->at(id)->getOption(i));
       optionsFalseBtns->at(i)->setSelected(!tools->at(id)->getOption(i));
   }
}

void ListCon::setCurrentToolId(int id)
{
    if(currentToolId > -1)
        tools->at(currentToolId)->setSelected(false);
    currentToolId = id;
    if(currentToolId > -1)
        tools->at(id)->setSelected(true);
}

void ListCon::disableSelection(){
    if(currentToolId > -1 && !tools->isEmpty() && (newNameEdit->text() != "")){
        tools->at(currentToolId)->setSelected(false);
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

        Tool *t = new Tool(tools->length(), newNameEdit->text(), currentOptions, this);
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
    if(currentToolId > -1){
        this->layout()->itemAt(0)->layout()->itemAt(1)->layout()->removeWidget(tools->at(currentToolId));
        delete tools->at(currentToolId);
        for(int i = 0; i < options->length(); i++){
            optionsTrueBtns->at(i)->setSelected(false);
            optionsFalseBtns->at(i)->setSelected(false);
        }
        setCurrentToolId(-1);
    }


}
