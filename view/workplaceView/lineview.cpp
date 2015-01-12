#include "lineview.h"
#include "separator.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include "flickcharm.h"

LineView::LineView(QWidget *parent) : QWidget(parent),
    listContentLayout(new QVBoxLayout),
    scLines(new QScrollArea),
    lblViewName(new QLabel(tr("Line"))),
    lblSelectLine(new QLabel(tr("chose line:"))),
    lblAddLine(new QLabel(tr("add line:"))),
    lblName(new QLabel(tr("label:"))),
    lblWorkplaceCount(new QLabel(tr("workplace count:"))),
    lblDescription(new QLabel(tr("description:"))),
    txtBxName(new TextLineEdit()),
    numBxWorkplaceCount(new NumberLineEdit()),
    txtBxDescription(new TextEdit()),
    btnBack(new QPushButton()),
    btnAdd(new QPushButton())
{
    btnBack->setObjectName("leftIcon");
    btnBack->setFixedSize(45, 45);
    txtBxDescription->setMaximumHeight(100);

    btnAdd->setObjectName("plusIcon");
    btnAdd->setFixedSize(45, 45);

    lblSelectLine->setObjectName("lblHeader");
    lblAddLine->setObjectName("lblHeader");

    connect(btnBack, SIGNAL(clicked()), this, SLOT(btnBackClicked()));
    connect(btnAdd, SIGNAL(clicked()), this, SIGNAL(saveLine()));

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, 0);

    QGridLayout *lineAddLayout = new QGridLayout;
    lineAddLayout->addWidget(lblAddLine, 0, 0, 1, 2, 0);
    lineAddLayout->addWidget(lblName, 1, 0, 1, 1, 0);
    lineAddLayout->addWidget(txtBxName, 1, 1, 1, 1, 0);
    lineAddLayout->addWidget(lblWorkplaceCount, 1, 2, 1, 1, 0);
    lineAddLayout->addWidget(numBxWorkplaceCount, 1, 3, 1, 1, 0);
    lineAddLayout->addWidget(lblDescription, 2, 0, 1, 2, 0);
    lineAddLayout->addWidget(txtBxDescription, 3, 0, 1, 4, 0);
    lineAddLayout->addWidget(btnAdd, 2, 3, 1, 1, Qt::AlignCenter);

    QWidget *listContent = new QWidget;
    listContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scLines->setWidget(listContent);
    scLines->setWidgetResizable(true);
    listContent->setLayout(listContentLayout);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scLines);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addWidget(lblSelectLine);
    mainLayout->addWidget(scLines);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    mainLayout->addLayout(lineAddLayout);

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

    DetailedListItem *newListItem = new DetailedListItem(this, "", name, QList<QStringList>(), true, true, false);
    newListItem->setID(id);
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedLineChanged(int)));
    connect(this, SIGNAL(lineSelected(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteLine(int)));
    listContentLayout->addWidget(newListItem);
}

void LineView::clearLines(){
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
void LineView::btnBackClicked(){
    emit back();
    emit saveSelectedLine(selectedLineID);
}

void LineView::selectedLineChanged(int id){
    selectedLineID = id;
    emit lineSelected(id);
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
