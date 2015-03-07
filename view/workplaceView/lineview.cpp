#include "lineview.h"
#include "../separator.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include "../flickcharm.h"
#include "../../databaseHandler/dbconstants.h"

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

void LineView::addLine(QHash<QString, QVariant> values){
    DetailedListItem *newListItem = new DetailedListItem(this, "lineIcon", values.value(DBConstants::COL_LINE_NAME).toString(), QList<QStringList>(), true, true, false, false, true);
    newListItem->setID(values.value(DBConstants::COL_LINE_ID).toInt());
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedLineChanged(int)));
    connect(this, SIGNAL(lineSelected(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteLine(int)));
    connect(newListItem, SIGNAL(editItem(int)), this, SLOT(editLineClicked(int)));
    listContentLayout->addWidget(newListItem);
}

void LineView::updateLine(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int id = values.value(DBConstants::COL_LINE_ID).toInt();
    int i = 0;
    while((item = listContentLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            dli->setName(values.value(DBConstants::COL_LINE_NAME).toString());
            break;
        }
        i++;
    }
}

void LineView::removeLine(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = listContentLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            listContentLayout->removeItem(item);
            delete item->widget();
            delete item;
            break;
        }
        i++;
    }
}

void LineView::selectedLine(QHash<QString, QVariant> values){
    emit lineSelected(values.value(DBConstants::COL_LINE_ID).toInt());
}

void LineView::clearLines(){
    QLayoutItem *item;
    while((item = listContentLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void LineView::onLeaving(){
    emit selectLine(selectedLineID);
}



//PRIVATE SLOTS
void LineView::selectedLineChanged(int id){
    selectedLineID = id;
    emit lineSelected(id);
}

void LineView::btnAddClicked(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_LINE_NAME, txtBxName->text());
    values.insert(DBConstants::COL_LINE_NUMBER_OF_WORKPLACES, numBxWorkplaceCount->getValue());
    values.insert(DBConstants::COL_LINE_DESCRIPTION, txtBxDescription->toPlainText());
    emit createLine(values);
    txtBxName->clear();
    txtBxDescription->clear();
    numBxWorkplaceCount->clear();
}

void LineView::editLineClicked(int id){
    emit showPopUp(PopUpType::LINE_POPUP);
    emit editLine(id);
}
