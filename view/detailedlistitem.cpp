#include "detailedlistitem.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QSpacerItem>
#include <QDebug>
#include <QStylePainter>
#include <QStyleOption>

DetailedListItem::DetailedListItem(QWidget *parent, const QString &objectName, const QString &name, const QList<QStringList> &scheme, bool isDeletable, bool isCheckable, bool hasForwardButton, bool canBeAdded, bool isEditable) :
    QAbstractButton(parent),
    isCheckable(isCheckable),
    layout(new QGridLayout),
    lblIcon(new QPushButton()),
    lblName(new QLabel(name)),
    btnDelete(new QPushButton()),
    btnAdd(new QPushButton()),
    btnEdit(new QPushButton()),
    checkBox(new QCheckBox()),
    btnForward(new QPushButton),
    listLblValues(QList<QList<QLabel*>>())
{
    // SETTINGS FOR GENERAL ELEMENTS
    lblName->setObjectName("lblHeader");
    if(objectName != "")
        lblIcon->setObjectName(objectName);
    else
        lblIcon->setObjectName("transparent");
    lblIcon->setFixedSize(45, 45);
    connect(lblIcon, SIGNAL(clicked()), this, SIGNAL(clicked()));
    checkBox->setChecked(false);
    checkBox->setEnabled(false);
    btnDelete->setFixedSize(45, 45);
    btnDelete->setObjectName("resetIcon");
    btnAdd->setFixedSize(45, 45);
    btnAdd->setObjectName("plusIcon");
    btnEdit->setFixedSize(45, 45);
    btnEdit->setObjectName("editIcon");
    btnForward->setFixedSize(45, 45);
    btnForward->setObjectName("rightIcon");
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(deleteItem()));
    connect(btnForward, SIGNAL(clicked()), this, SIGNAL(clicked()));

    // ADD SCHEME (DESCRIPTIONS)
    for(int i = 0; i < scheme.count(); ++i){
        QList<QLabel*> listLblsRow;
        for(int j = 0; j < scheme.at(i).count(); ++j){

            QLabel *lblCaption = new QLabel(scheme.at(i).at(j));
            lblCaption->setObjectName("lblCaption");

            QLabel *lblValue = new QLabel("");
            lblValue->setMinimumWidth(100);
            lblValue->setObjectName("lblValue");

            listLblsRow.append(lblValue);

            layout->addWidget(lblCaption, i+1, 1+2*j, 1, 1, Qt::AlignLeft);
            layout->addWidget(lblValue, i+1, 2+2*j, 1, 1, Qt::AlignLeft);
        }
        listLblValues.append(listLblsRow);
    }

    // ADD GENERAL ELEMENTS (OR SPACERS)
    layout->addWidget(lblIcon, 0, 0, layout->rowCount(), 1, Qt::AlignLeft);
    layout->addWidget(lblName, 0, 1, 1, layout->columnCount(), Qt::AlignLeft);

    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, layout->columnCount(), layout->rowCount(), 1, 0);
    if(isDeletable){
        layout->addWidget(btnDelete, 0, layout->columnCount(), layout->rowCount(), 1, Qt::AlignRight);
    }
    if(canBeAdded){
        layout->addWidget(btnAdd, 0, layout->columnCount(), layout->rowCount(), 1, Qt::AlignRight);
        connect(btnAdd, SIGNAL(clicked()), this, SLOT(addItem()));
    }
    if(isEditable){
        layout->addWidget(btnEdit, 0, layout->columnCount(), layout->rowCount(), 1, Qt::AlignRight);
        connect(btnEdit, SIGNAL(clicked()), this, SLOT(editItem()));
    }
    if(isCheckable){
        layout->addWidget(checkBox, 0, layout->columnCount(), layout->rowCount(), 1, Qt::AlignRight);
        connect(this, SIGNAL(clicked()), this, SLOT(changeSelection()));
    }
    if(hasForwardButton){
        layout->addWidget(btnForward, 0, layout->columnCount(), layout->rowCount(), 1, Qt::AlignRight);
    }
    else {
        layout->addItem(new QSpacerItem(50, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), layout->columnCount(), layout->rowCount(), 1, Qt::AlignRight);
    }
    setLayout(layout);

    connect(this, SIGNAL(clicked()), this, SLOT(itemPressed()));
}

void DetailedListItem::paintEvent(QPaintEvent *e){
    QStylePainter p(this);
    QStyleOption opt;
    opt.initFrom(this);
    p.drawPrimitive(QStyle::PE_Widget, opt);}

// PRIVATE SLOTS
void DetailedListItem::deleteItem(){
    emit deleteItem(id);
}

void DetailedListItem::addItem(){
    emit addItem(id);
}

void DetailedListItem::editItem(){
    emit editItem(id);
}

void DetailedListItem::itemPressed(){
    emit pressed(id);
}

// PUBLIC SLOTS
void DetailedListItem::
checkState(int id){
}

void DetailedListItem::setValues(const QList<QStringList> &values){
    for(int i = 0; i < values.count(); ++i){
        for(int j = 0; j < values.at(i).count(); ++j){
            listLblValues.at(i).at(j)->setText(values.at(i).at(j));
        }
    }
}

void DetailedListItem::setName(const QString &name){
    lblName->setText(name);
}

void DetailedListItem::changeSelection(){
    if(isCheckable){
        if(checkBox->isChecked())
            deselect();
        else
            select();
    }
}

void DetailedListItem::select(int id){
    if(this->id == id)
        select();
}

void DetailedListItem::deselect(int id){
    if(this->id == id)
        deselect();
}

void DetailedListItem::select(){
    if(isCheckable && !checkBox->isChecked()){
        checkBox->setChecked(true);
        emit selected(id);
    }
}

void DetailedListItem::deselect(){
    if(isCheckable && checkBox->isChecked()){
        checkBox->setChecked(false);
        emit deselected(id);
    }
}

void DetailedListItem::selectExclusiveWithID(int id){
    if(this->id != id)
        deselect();
    else
        select();
}
// PUBLIC

int DetailedListItem::getID() const{
    return id;
}
void DetailedListItem::setID(int id){
    this->id = id;
}
