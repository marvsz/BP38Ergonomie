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
    lblTotalDuration(new QLabel(tr("Total duration [min]:"))),
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

    emit selectedWorkplaceChanged(0);
}

// PUBLIC METHODS
QList<QAbstractButton*> * RotationGroupTaskView::getAdditionalNavigation() const{
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnAddWorkplace);
    return additions;
}

// PUBLIC SLOTS
void RotationGroupTaskView::setRotationGroupTask(QHash<QString, QVariant> values){
    txtBxName->clear();
    txtBxName->setText(values.value(DBConstants::COL_ROTATION_GROUP_TASK_NAME).toString());
}

void RotationGroupTaskView::setRotationGroupTaskDuration(int duration){
    lblTotalDurationValue->setText(QString::number(duration));
}

void RotationGroupTaskView::addRotationGroupTaskEntry(QHash<QString, QVariant> values){
    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_DURATION).toString());
    DetailedListItem *newListItem = new DetailedListItem(this, "workplaceIcon", values.value(DBConstants::COL_WORKPLACE_NAME).toString(), rotationGroupTaskEntryCaptions, true, false, false, false, false);
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
    DetailedListItem *newListItem = new DetailedListItem(this, "workplaceIcon", values.value(DBConstants::COL_WORKPLACE_NAME).toString(), workplaceCaptions, false, true, false, false, false);
    newListItem->setID(values.value(DBConstants::COL_WORKPLACE_ID).toInt());
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedWorkplaceChanged(int)));
    connect(newListItem, SIGNAL(deselected(int)), this, SLOT(deselectWorkplace(int)));
    connect(newListItem, SIGNAL(deleteItem(int)), this, SIGNAL(deleteRotationGroupTaskEntry(int)));
    connect(this, SIGNAL(selectedWorkplace(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    workplaceListLayout->addWidget(newListItem);
}

void RotationGroupTaskView::updateWorkplace(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int id = values.value(DBConstants::COL_WORKPLACE_ID).toInt();
    int i = 0;
    while((item = workplaceListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            dli->setName(values.value(DBConstants::COL_WORKPLACE_NAME).toString());
            break;
        }
        i++;
    }
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

void RotationGroupTaskView::onLeaving(){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    if(txtBxName->text() != "")
        values.insert(DBConstants::COL_ROTATION_GROUP_TASK_NAME, txtBxName->text());
    else{
        QString name = "";
        int length = rotationGroupTaskEntryListLayout->count();
        for(int i = 0; i < length - 1; ++i){
            DetailedListItem *dli = qobject_cast<DetailedListItem*>(rotationGroupTaskEntryListLayout->itemAt(i)->widget());
            name.append(dli->getName());
            name.append(" -> ");
        }
        name.append(qobject_cast<DetailedListItem*>(rotationGroupTaskEntryListLayout->itemAt(length - 1)->widget())->getName());
        values.insert(DBConstants::COL_ROTATION_GROUP_TASK_NAME, name);
    }
    values.insert(DBConstants::COL_ROTATION_GROUP_TASK_DURATION, lblTotalDurationValue->text().toInt());
    emit saveRotationGroupTask(values);
}

// PRIVATE SLOTS

void RotationGroupTaskView::selectedWorkplaceChanged(int id){
    selectedWorkplaceID = id;
    emit selectedWorkplace(id);
    if(selectedWorkplaceID > 0)
        btnAdd->setEnabled(true);
    else
        btnAdd->setEnabled(false);
}

void RotationGroupTaskView::deselectWorkplace(int id){
    if(id == selectedWorkplaceID){
        selectedWorkplaceID = 0;
        btnAdd->setEnabled(false);
    }
}

void RotationGroupTaskView::btnAddClicked(){
    if(selectedWorkplaceID > 0 && numBxWorkplaceDuration->getValue() > 0){
        QHash<QString, QVariant> values = QHash<QString, QVariant>();
        values.insert(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_WORKPLACE_ID, selectedWorkplaceID);
        values.insert(DBConstants::COL_ROTATION_GROUP_TASK_ENTRY_DURATION, numBxWorkplaceDuration->getValue());
        emit createRotationGroupTaskEntry(values);
        numBxWorkplaceDuration->clear();
        selectedWorkplaceChanged(0);
    }
    else
        emit showMessage(tr("You have to select a Workplace and enter a Duration!"), NotificationMessage::ERROR);
}

void RotationGroupTaskView::btnAddWorkplaceClicked(){
    showPopUp(PopUpType::WORKPLACE_POPUP);
}
