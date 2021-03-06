#include "subactivitycontrol.h"
#include "numberlineedit.h"
#include <QGuiApplication>
#include "separator.h"

SubActivityControl::SubActivityControl(QWidget *parent) :
    QWidget(parent),
    btnAdd(new QPushButton(this)),
    btnDelete(new QPushButton(this)),
    txtbxDescription(new TextLineEdit(this)),
    btnList(new QVector<SelectableValueButton*>()),
    btnListLayout(new QVBoxLayout),
    selectedBtn(NULL)
{
    QGridLayout *mainLayout = new QGridLayout;
    QHBoxLayout *btnAddDeleteLayout = new QHBoxLayout;

    btnAdd->setText(tr("add subactivity"));
    btnAdd->setMaximumWidth(250);
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(addSubActivity()));

    btnDelete->setText(tr("delete subactivity"));
    btnDelete->setMaximumWidth(250);
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(deleteSubActivity()));

    btnAddDeleteLayout->addWidget(btnAdd);
    btnAddDeleteLayout->addWidget(btnDelete);

    txtbxDescription->setPlaceholderText(tr("Description of the Subactivity"));
    txtbxDescription->setMinimumWidth(300);
    connect(txtbxDescription, SIGNAL(editingFinished()), QGuiApplication::inputMethod(), SLOT(hide()));

    mainLayout->addWidget(new QLabel(tr("subactivity")), 0, 0, 1, 2, Qt::AlignLeft);
    mainLayout->addLayout(btnListLayout, 1, 0, 1, 2, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 2, 0, 1, 2, 0);
    mainLayout->addWidget(new QLabel(tr("description:")), 3, 0, 1, 1, 0);
    mainLayout->addWidget(txtbxDescription, 3, 1, 1, 1, 0);
    mainLayout->addLayout(btnAddDeleteLayout, 4, 0, 1, 2, 0);

    this->setLayout(mainLayout);
}


void SubActivityControl::addSubActivity(){
    if(txtbxDescription->text() != QString("")){
        SelectableValueButton *btn = new SelectableValueButton(btnList->length(), 0, this);
        btn->setText(txtbxDescription->text());
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(subActivitySelected(int)));
        btnList->append(btn);
        btnListLayout->addWidget(btn);
        txtbxDescription->setText("");
    }
}

void SubActivityControl::deleteSubActivity(){
    if(selectedBtn != NULL){
        for(int i = selectedBtn->getID() + 1; i < btnList->length(); ++i)
            btnList->at(i)->setID(i - 1);
        btnList->removeAt(selectedBtn->getID());
        delete selectedBtn;
        selectedBtn = NULL;
        txtbxDescription->setText("");
    }
}

void SubActivityControl::subActivitySelected(int id){
    if(selectedBtn != NULL)
        selectedBtn->setSelected(false);
    selectedBtn = btnList->at(id);
    selectedBtn->setSelected(true);
    txtbxDescription->setText(selectedBtn->text());
}
