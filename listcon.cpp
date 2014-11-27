#include "listcon.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QErrorMessage>

ListCon::ListCon(QString name, QString opt1Name, QString opt2Name, QWidget *parent) :
    QGroupBox(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QVBoxLayout *listLayout = new QVBoxLayout;
    QHBoxLayout *listHLayout = new QHBoxLayout;
    QHBoxLayout *newNameLayout = new QHBoxLayout;
    QHBoxLayout *opt1Layout = new QHBoxLayout;
    QHBoxLayout *opt2Layout = new QHBoxLayout;
    QHBoxLayout *optLayout = new QHBoxLayout;
    QVBoxLayout *newLayout = new QVBoxLayout;

    currentToolId = -1;
    this->name = new QLabel(this);
    this->name->setText(name);
    this->newName = new QLabel(this);
    this->newName->setText("Bezeichnung");
    this->newNameEdit = new QLineEdit(this);
    this->newNameEdit->setPlaceholderText("Neues Hilfsmittel");
    this->opt1 = new QLabel(this);
    this->opt1->setText(opt1Name);
    this->opt2 = new QLabel(this);
    this->opt2->setText(opt2Name);
    this->opt1TrueBtn = new TextQPushButton(0, "Ja", this);
    this->opt1FalseBtn = new TextQPushButton(1, "Nein", this);
    this->opt2TrueBtn = new TextQPushButton(2, "Ja", this);
    this->opt2FalseBtn = new TextQPushButton(3, "Nein", this);
    this->opt1TrueBtn->setFixedSize(100, 60);
    this->opt1FalseBtn->setFixedSize(100, 60);
    this->opt2TrueBtn->setFixedSize(100, 60);
    this->opt2FalseBtn->setFixedSize(100, 60);
    this->addBtn = new TextQPushButton(4, "Hilfsmittel hinzufügen", this);
    this->addBtn->setMinimumHeight(100);
    this->addBtn->setMaximumWidth(400);

    this->tools = QList<Tool*>();
    if(!tools.isEmpty()){
        for(int i = 0; i < tools.length(); i++){
            listLayout->addWidget(tools.at(i));
            connect(tools.at(i), SIGNAL(pressedWithID(int)), this, SLOT(toolChanged(int)));
        }

        setCurrentToolId(0);
        opt1TrueBtn->setSelected(tools.at(0)->getOpt1());
        opt1FalseBtn->setSelected(!tools.at(0)->getOpt1());
        opt2TrueBtn->setSelected(tools.at(0)->getOpt2());
        opt2TrueBtn->setSelected(!tools.at(0)->getOpt2());
    }

    connect(opt1TrueBtn, SIGNAL(clicked()), this, SLOT(opt1TruePressed()));
    connect(opt1FalseBtn, SIGNAL(clicked()), this, SLOT(opt1FalsePressed()));
    connect(opt2TrueBtn, SIGNAL(clicked()), this, SLOT(opt2TruePressed()));
    connect(opt2FalseBtn, SIGNAL(clicked()), this, SLOT(opt2FalsePressed()));
    connect(addBtn, SIGNAL(clicked()), this, SLOT(addTool()));
    connect(newNameEdit, SIGNAL(textChanged(QString)), this, SLOT(disableSelection()));

    listHLayout->addWidget(this->name, 0, Qt::AlignCenter);
    listHLayout->addLayout(listLayout);

    newNameLayout->addWidget(newName);
    newNameLayout->addWidget(newNameEdit);

    opt1Layout->addWidget(opt1);
    opt1Layout->addWidget(opt1TrueBtn);
    opt1Layout->addWidget(opt1FalseBtn);
    opt2Layout->addWidget(opt2);
    opt2Layout->addWidget(opt2TrueBtn);
    opt2Layout->addWidget(opt2FalseBtn);
    optLayout->addLayout(opt1Layout);
    optLayout->addLayout(opt2Layout);

    newLayout->addLayout(newNameLayout);
    newLayout->addLayout(optLayout);
    newLayout->addWidget(addBtn);

    mainLayout->addLayout(listHLayout);
    mainLayout->addLayout(newLayout);
    mainLayout->setAlignment(this, Qt::AlignHCenter);
    this->setLayout(mainLayout);

}

void ListCon::opt1TruePressed()
{
    if(currentToolId > -1)
        tools.at(currentToolId)->setOpt1(true);
    currOpt1 = true;
    opt1Changed();
}

void ListCon::opt1FalsePressed()
{
    if(currentToolId > -1)
        tools.at(currentToolId)->setOpt1(false);
    currOpt1 = false;
    opt1Changed();
}

void ListCon::opt2TruePressed()
{
    if(currentToolId > -1)
        tools.at(currentToolId)->setOpt2(true);
    currOpt2 = true;
    opt2Changed();
}

void ListCon::opt2FalsePressed(){
    if(currentToolId > -1)
        tools.at(currentToolId)->setOpt2(false);
    currOpt2 = false;
    opt2Changed();
}

void ListCon::opt1Changed()
{
    opt1TrueBtn->setSelected(currOpt1);
    opt1FalseBtn->setSelected(!currOpt1);
}

void ListCon::opt2Changed()
{
    opt2TrueBtn->setSelected(currOpt2);
    opt2FalseBtn->setSelected(!currOpt2);
}

void ListCon::toolChanged(int id)
{
   setCurrentToolId(id);
   opt1TrueBtn->setSelected(tools.at(id)->getOpt1());
   opt1FalseBtn->setSelected(!tools.at(id)->getOpt1());
   opt2TrueBtn->setSelected(tools.at(id)->getOpt2());
   opt2FalseBtn->setSelected(!tools.at(id)->getOpt2());

}

void ListCon::setCurrentToolId(int id)
{
    if(currentToolId > -1)
        tools.at(currentToolId)->setSelected(false);
    currentToolId = id;
    if(currentToolId > -1)
        tools.at(id)->setSelected(true);
}

void ListCon::disableSelection(){
    if(currentToolId > -1 && !tools.isEmpty() && (newNameEdit->text() != "")){
        tools.at(currentToolId)->setSelected(false);
        opt1TrueBtn->setSelected(false);
        opt1FalseBtn->setSelected(false);
        opt2TrueBtn->setSelected(false);
        opt2FalseBtn->setSelected(false);
    }
    setCurrentToolId(-1);
}

void ListCon::addTool()
{
    if(newNameEdit->text() != ""){
        Tool *t = new Tool(tools.length(), newNameEdit->text(), currOpt1, currOpt2, this);
        t->setMinimumSize(100, 60);
        tools.append(t);
        connect(t, SIGNAL(pressedWithID(int)), this, SLOT(toolChanged(int)));
        this->layout()->itemAt(0)->layout()->itemAt(1)->layout()->addWidget(t);
        newNameEdit->clear();
        opt1TrueBtn->setSelected(false);
        opt1FalseBtn->setSelected(false);
        opt2TrueBtn->setSelected(false);
        opt2FalseBtn->setSelected(false);
    }
    else {
        QErrorMessage *e = new QErrorMessage(this);
        e->showMessage("Sie müssen einen Namen für das Hilfsmittel eingeben", "OK");
    }
}
