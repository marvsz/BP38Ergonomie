#include "rotationgrouptaskview.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include "../separator.h"
#include "../flickcharm.h"
#include "../detailedlistitem.h"
#include "../../databaseHandler/dbconstants.h"

RotationGroupTaskView::RotationGroupTaskView(QWidget *parent) :
    SimpleNavigateableWidget(tr("New Rotation Group"), parent),
    lblName(new QLabel(tr("Name:"))),
    lblTotalDuration(new QLabel(tr("Total duration:"))),
    txtBxName(new TextLineEdit(this)),
    lblTotalDurationValue(new QLabel()),
    rotationGroupTaskEntryListContent(new QWidget()),
    workplaceListContent(new QWidget()),
    rotationGroupTaskEntryListLayout(new QVBoxLayout()),
    workplaceListLayout(new QVBoxLayout()),
    scRotationGroupTaskEntries(new QScrollArea()),
    scWorkplaces(new QScrollArea()),
    lblAddWorkplace(new QLabel(tr("Add Workplace to Rotation Group"))),
    lblWorkplaceDuration(new QLabel(tr("Duration [min]:"))),
    numBxWorkplaceDuration(new NumberLineEdit()),
    btnAdd(new QPushButton(this)),
    btnAddWorkplace(new QPushButton(this))
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QGridLayout *leftLayout = new QGridLayout;
    QGridLayout *rightLayout = new QGridLayout;

    btnAddWorkplace->setObjectName("workplaceIcon");
    btnAddWorkplace->setFixedSize(45, 45);
    connect(btnAddWorkplace, SIGNAL(clicked()), this, SLOT(btnAddWorkplaceClicked()));

    // left part:

    scRotationGroupTaskEntries->setWidget(rotationGroupTaskEntryListContent);
    scRotationGroupTaskEntries->setWidgetResizable(true);
    scRotationGroupTaskEntries->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    FlickCharm *flickCharmRotation = new FlickCharm(this);
    flickCharmRotation->activateOn(scRotationGroupTaskEntries);

    rotationGroupTaskEntryListContent->setLayout(rotationGroupTaskEntryListLayout);
    rotationGroupTaskEntryListLayout->setAlignment(Qt::AlignTop);

    leftLayout->setAlignment(Qt::AlignTop);
    leftLayout->addWidget(lblName, 0, 0, 1, 1, 0);
    leftLayout->addWidget(txtBxName, 0, 1, 1, 1, 0);
    leftLayout->addWidget(lblTotalDuration, 1, 0, 1, 1, 0);
    leftLayout->addWidget(lblTotalDurationValue, 1, 1, 1, 1, 0);
    leftLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 2, 0, 1, 2, 0);
    leftLayout->addWidget(scRotationGroupTaskEntries, 3, 0, 1, 2, 0);

    // right part:
    lblAddWorkplace->setObjectName("lblHeader");

    btnAdd->setObjectName("plusIcon");
    btnAdd->setFixedSize(45, 45);
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));


    scWorkplaces->setWidget(workplaceListContent);
    scWorkplaces->setWidgetResizable(true);
    scWorkplaces->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    FlickCharm *flickCharmWorkplace = new FlickCharm(this);
    flickCharmWorkplace->activateOn(scWorkplaces);

    workplaceListContent->setLayout(workplaceListLayout);
    workplaceListLayout->setAlignment(Qt::AlignTop);

    rightLayout->setAlignment(Qt::AlignTop);
    rightLayout->addWidget(lblAddWorkplace, 0, 0, 1, 2, Qt::AlignCenter);
    rightLayout->addWidget(scWorkplaces, 1, 0, 1, 2, 0);
    rightLayout->addWidget(lblWorkplaceDuration, 2, 0, 1, 1, 0);
    rightLayout->addWidget(numBxWorkplaceDuration, 2, 1, 1, 1, 0);
    rightLayout->addWidget(btnAdd, 3, 0, 1, 2, Qt::AlignCenter);

    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    //emit selectedWorkplaceChanged(-1);
}


// PUBLIC METHODS

QString RotationGroupTaskView::getName() const{
    return txtBxName->text();
}

int RotationGroupTaskView::getSelectedWorkplace() const {
    return selectedWorkplaceID;
}

int RotationGroupTaskView::getWorkplaceDuration() const {
    return numBxWorkplaceDuration->getValue();
}

// PUBLIC METHODS
QList<QAbstractButton*> * RotationGroupTaskView::getAdditionalNavigation() const{
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnAddWorkplace);
    return additions;
}

// PUBLIC SLOTS
void RotationGroupTaskView::setRotationGroupTask(QHash<QString, QVariant> values){
    txtBxName->setText(values.value(DBConstants::COL_ROTATION_GROUP_TASK_NAME).toString().append(" min"));
    lblTotalDuration->setText(values.value(DBConstants::COL_ROTATION_GROUP_TASK_DURATION).toString());
}

void RotationGroupTaskView::addRotationGroupTaskEntry(QHash<QString, QVariant> values){
    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_DURATION).toString());
    DetailedListItem *newListItem = new DetailedListItem(this, "workplaceIcon", "", rotationGroupTaskEntryCaptions, true, false, false, false, false);
    newListItem->setValues(dliValues);
    newListItem->setID(values.value(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_ID).toInt());
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteRotationGroupTaskEntry(int)));
    rotationGroupTaskEntryListLayout->addWidget(newListItem);
}

void RotationGroupTaskView::removeRotationGroupTaskEntry(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = rotationGroupTaskEntryListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            rotationGroupTaskEntryListLayout->removeItem(item);
            delete item->widget();
            delete item;
            break;
        }
        i++;
    }
}

void RotationGroupTaskView::clearRotationGroupTaskEntries(){
    QLayoutItem *item;
    while((item = rotationGroupTaskEntryListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void RotationGroupTaskView::addWorkplace(QHash<QString, QVariant> values){

}

void RotationGroupTaskView::updateWorkplace(QHash<QString, QVariant> values){

}

void RotationGroupTaskView::removeWorkplace(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = workplaceListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            workplaceListLayout->removeItem(item);
            delete item->widget();
            delete item;
            break;
        }
        i++;
    }
}

void RotationGroupTaskView::clearWorkplaces(){
    QLayoutItem *item;
    while((item = workplaceListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

/*
void RotationGroupView::setRotationGroupName(const QString &name){
    txtBxName->setText(name);
}

void RotationGroupView::setRotationGroupDuration(int duration){
    lblTotalDurationValue->setText(QString::number(duration).append(" min"));
}

void RotationGroupView::setWorkplaceDuration(int duration){
    numBxWorkplaceDuration->setValue(duration);
}

void RotationGroupView::addRotationGroupTask(int id, const QString &name, int duration){
    QList<QStringList> values = QList<QStringList>() << (QStringList() << QString::number(duration).append(" min"));
    DetailedListItem *newListItem = new DetailedListItem(this, "workplaceIcon", name, rotationGroupTaskCaptions, true, false, false);
    newListItem->setID(id);
    newListItem->setValues(values);
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(removeRotationGroupTaskEntry(int)));
    rotationGroupTaskListLayout->addWidget(newListItem);
}

void RotationGroupView::clearRotationGroupTasks(){
    QLayoutItem *item;
    while((item = rotationGroupTaskListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void RotationGroupView::addWorkplace(int id, const QString &name, int duration){
    QList<QStringList> values = QList<QStringList>() << (QStringList() << QString::number(duration).append(" min"));
    DetailedListItem *newListItem = new DetailedListItem(this, "workplaceIcon", name, workplaceCaptions, false, true, false);
    newListItem->setID(id);
    newListItem->setValues(values);
    connect(this, SIGNAL(selectedWorkplaceChanged(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(setSelectedWorkplace(int)));
    workplaceListLayout->addWidget(newListItem);
}

void RotationGroupView::clearWorkplaces(){
    QLayoutItem *item;
    while((item = workplaceListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}
*/

// PRIVATE SLOTS

void RotationGroupTaskView::setSelectedWorkplace(int id){
    selectedWorkplaceID = id;
    emit selectWorkplace(id);
    // dann soll bitte die duration auf die standard duration (summe aller activities)
    // gesetzt werden
}

void RotationGroupTaskView::btnAddClicked(){
    if(selectedWorkplaceID > -1){
        //emit createRotationGroupTask();
        numBxWorkplaceDuration->clear();
        setSelectedWorkplace(-1);
    }
}

void RotationGroupTaskView::btnAddWorkplaceClicked(){
    showPopUp(PopUpType::WORKPLACE_POPUP);
}
