#include "workplacelistview.h"
#include "../flickcharm.h"
#include <QVBoxLayout>
#include <QList>
#include <QStringList>

WorkplaceListView::WorkplaceListView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Workplaces"), parent),
    btnPlus(new QPushButton(this)),
    listContentLayout(new QVBoxLayout),
    scWorkplaces(new QScrollArea())
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QWidget *listContent = new QWidget;

    btnPlus->setObjectName("plusIcon");
    btnPlus->setFixedSize(45, 45);

    connect(btnPlus, SIGNAL(clicked()), this, SLOT(btnPlusClicked()));

    scWorkplaces->setWidget(listContent);
    scWorkplaces->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scWorkplaces);

    listContent->setLayout(listContentLayout);
    listContentLayout->setAlignment(Qt::AlignTop);

    mainLayout->addWidget(scWorkplaces);

    this->setLayout(mainLayout);
}

//PUBLIC SLOTS
void WorkplaceListView::addWorkplace(QHash<QString, QVariant> values){
    QList<QStringList> wpValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_WORKPLACE_DESCRIPTION).toString() << values.value(DBConstants::COL_WORKPLACE_CODE).toString());
    DetailedListItem *newListItem = new DetailedListItem(this, "workplaceIcon", values.value(DBConstants::COL_WORKPLACE_NAME).toString(), workplaceCaptions, true, false, true);
    newListItem->setValues(wpValues);
    newListItem->setID(values.value(DBConstants::COL_WORKPLACE_ID).toInt());
    connect(newListItem, SIGNAL(pressed(int)), this, SLOT(dliWorkplaceClicked(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteWorkplace(int)));
    listContentLayout->addWidget(newListItem);
}

void WorkplaceListView::updateWorkplace(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int i = 0;
    int id = values.value(DBConstants::COL_WORKPLACE_ID).toInt();
    while((item = listContentLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            QList<QStringList> wpValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_WORKPLACE_DESCRIPTION).toString() << values.value(DBConstants::COL_WORKPLACE_CODE).toString());
            dli->setValues(wpValues);
            dli->setName(values.value(DBConstants::COL_WORKPLACE_NAME).toString());
            break;
        }
        i++;
    }
}

void WorkplaceListView::removeWorkplace(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = listContentLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            item = listContentLayout->takeAt(i);
            delete item->widget();
            delete item;
            break;
        }
        i++;
    }
}

void WorkplaceListView::clearWorkplaces(){
    QLayoutItem *item;
    while((item = listContentLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

//PUBLIC METHODS
QList<QAbstractButton*> * WorkplaceListView::getAdditionalNavigation() const{
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnPlus);
    return additions;
}

//PRIVATE SLOTS
void WorkplaceListView::btnPlusClicked(){
    emit createWorkplace(QHash<QString, QVariant>());
}

void WorkplaceListView::dliWorkplaceClicked(int id){
    emit selectWorkplace(id);
    emit showView(ViewType::WORKPLACE_VIEW);
}
