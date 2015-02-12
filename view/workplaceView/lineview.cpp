#include "lineview.h"
#include "separator.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include "flickcharm.h"
#include "iconconstants.h"

LineView::LineView(QWidget *parent) : SimpleNavigateableWidget(tr("Line"), parent),
    listContentLayout(new QVBoxLayout),
    scLines(new QScrollArea),
    lblSelectLine(new QLabel(tr("chose line:"))),
    lblAddLine(new QLabel(tr("add line:"))),
    lblName(new QLabel(tr("label:"))),
    lblWorkplaceCount(new QLabel(tr("workplace count:"))),
    lblDescription(new QLabel(tr("description:"))),
    txtBxName(new TextLineEdit()),
    numBxWorkplaceCount(new NumberLineEdit()),
    txtBxDescription(new TextEdit()),
    btnAdd(new QPushButton())
{
    txtBxDescription->setMaximumHeight(100);
    txtBxName->setPlaceholderText(tr("name of the line"));
    numBxWorkplaceCount->setPlaceholderText(tr("amount of work places"));

    btnAdd->setObjectName("plusIcon");
    btnAdd->setFixedSize(45, 45);

    lblSelectLine->setObjectName("lblHeader");
    lblAddLine->setObjectName("lblHeader");

    connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));

    lblAddLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    lblName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    txtBxName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    lblWorkplaceCount->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    numBxWorkplaceCount->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    lblDescription->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    txtBxDescription->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    btnAdd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    QGridLayout *lineAddLayout = new QGridLayout;
    lineAddLayout->setContentsMargins(0,0,0,0);
    lineAddLayout->addWidget(lblAddLine, 0, 0, 1, 2, 0);
    lineAddLayout->addWidget(lblName, 1, 0, 1, 1, 0);
    lineAddLayout->addWidget(txtBxName, 1, 1, 1, 1, 0);
    lineAddLayout->addWidget(lblWorkplaceCount, 1, 2, 1, 1, 0);
    lineAddLayout->addWidget(numBxWorkplaceCount, 1, 3, 1, 1, 0);
    lineAddLayout->addWidget(lblDescription, 2, 0, 1, 2, 0);
    lineAddLayout->addWidget(txtBxDescription, 2, 1, 1, 4, 0);
    lineAddLayout->addWidget(btnAdd, 3, 0, 1, 4, Qt::AlignCenter);    

    QWidget *listContent = new QWidget;
    listContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scLines->setWidget(listContent);
    scLines->setWidgetResizable(true);
    scLines->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listContent->setLayout(listContentLayout);
    listContentLayout->setAlignment(Qt::AlignTop);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scLines);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(lineAddLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addWidget(lblSelectLine);
    mainLayout->addWidget(scLines);

    lineAddLayout->setAlignment(Qt::AlignTop);

    setLayout(mainLayout);
}

LineView::~LineView(){

}

//PUBLIC SLOTS
void LineView::setLine(const QString &name, const QString &description, int workplaceCount){
    txtBxName->setText(name);
    txtBxDescription->setText(description);
    numBxWorkplaceCount->setValue(workplaceCount);
}

void LineView::addLine(int id, const QString &name){

    DetailedListItem *newListItem = new DetailedListItem(this, IconConstants::ICON_LINE, name, QList<QStringList>(), true, true, false);
    newListItem->setID(id);
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedLineChanged(int)));
    connect(this, SIGNAL(lineSelected(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteLine(int)));
    listContentLayout->addWidget(newListItem);
}

void LineView::clear(){
    QLayoutItem *item;
    while((item = listContentLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void LineView::setSelectedLine(int id){
    selectedLineChanged(id);
}


//PRIVATE SLOTS
void LineView::selectedLineChanged(int id){
    selectedLineID = id;
    emit lineSelected(id);
}

void LineView::btnAddClicked(){
    emit saveLine();
    txtBxName->clear();
    txtBxDescription->clear();
    numBxWorkplaceCount->clear();
}

//GETTER and SETTER
QString LineView::getName() const{
    return txtBxName->text();
}
QString LineView::getDescription() const{
    return txtBxDescription->toPlainText();
}
int LineView::getWorkplaceCount() const{
    return numBxWorkplaceCount->getValue();
}
