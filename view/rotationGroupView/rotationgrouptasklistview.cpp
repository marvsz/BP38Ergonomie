#include "rotationgrouptasklistview.h"
#include "../flickcharm.h"
#include "../detailedlistitem.h"
#include "../../databaseHandler/dbconstants.h"
#include <QList>

RotationGroupTaskListView::RotationGroupTaskListView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Rotation Groups"), parent),
    btnPlus(new QPushButton(this)),
    listContentLayout(new QVBoxLayout),
    scRotationGroups(new QScrollArea())
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QWidget *listContent = new QWidget;

    btnPlus->setObjectName("plusIcon");
    btnPlus->setFixedSize(45, 45);
    connect(btnPlus, SIGNAL(clicked()), this, SLOT(btnPlusClicked()));

    scRotationGroups->setWidget(listContent);
    scRotationGroups->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scRotationGroups);

    listContent->setLayout(listContentLayout);
    listContentLayout->setAlignment(Qt::AlignTop);

    mainLayout->addWidget(scRotationGroups);
    setLayout(mainLayout);

}

// PUBLIC SLOTS
void RotationGroupTaskListView::addRotationGroupTask(QHash<QString, QVariant> values){
    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_ROTATION_GROUP_TASK_DURATION).toString());
    DetailedListItem *newListItem = new DetailedListItem(this, "rotationIcon", values.value(DBConstants::COL_ROTATION_GROUP_TASK_NAME).toString(), rotationGroupCaptions, true, false, true, false, false);
    newListItem->setValues(dliValues);
    newListItem->setID(values.value(DBConstants::COL_ROTATION_GROUP_TASK_ID).toInt());
    connect(newListItem, SIGNAL(pressed(int)), this, SLOT(dliRotationGroupTaskClicked(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteRotationGroupTask(int)));
    listContentLayout->addWidget(newListItem);
}

void RotationGroupTaskListView::updateRotationGroupTask(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int i = 0;
    int id = values.value(DBConstants::COL_ROTATION_GROUP_TASK_ID).toInt();
    while((item = listContentLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            QList<QStringList> wpValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_ROTATION_GROUP_TASK_DURATION).toString());
            dli->setValues(wpValues);
            dli->setName(values.value(DBConstants::COL_ROTATION_GROUP_TASK_NAME).toString());
            break;
        }
        i++;
    }
}

void RotationGroupTaskListView::removeRotationGroupTask(int id){
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

void RotationGroupTaskListView::clearRotationGroupTasks(){
    QLayoutItem *item;
    while((item = listContentLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

// PUBLIC METHODS
QList<QAbstractButton*> * RotationGroupTaskListView::getAdditionalNavigation() const {
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnPlus);
    return additions;
}

// PRIVATE SLOTS
void RotationGroupTaskListView::btnPlusClicked(){
    emit createRotationGroupTask(QHash<QString, QVariant>());
}

void RotationGroupTaskListView::dliRotationGroupTaskClicked(int id){
    emit selectRotationGroupTask(id);
    emit showView(ViewType::ROTATION_GROUP_TASK_VIEW);
}
