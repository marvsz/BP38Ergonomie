#include "rotationgroupview.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include "../view/separator.h"
#include "../view/flickcharm.h"
#include "../view/detailedlistitem.h"
#include "../view/iconconstants.h"

const QList<QStringList> RotationGroupView::rotationGroupTaskCaptions = QList<QStringList>() << (QStringList() << tr("Duration:"));
const QList<QStringList> RotationGroupView::workplaceCaptions = QList<QStringList>() << (QStringList() << tr("Duration:"));

RotationGroupView::RotationGroupView(QWidget *parent) :
    SimpleNavigateableWidget(tr("New Rotation Group"), parent),
    lblName(new QLabel(tr("Name:"))),
    lblTotalDuration(new QLabel(tr("Total duration:"))),
    txtBxName(new TextLineEdit(this)),
    lblTotalDurationValue(new QLabel()),
    rotationGroupTaskListContent(new QWidget()),
    workplaceListContent(new QWidget()),
    rotationGroupTaskListLayout(new QVBoxLayout()),
    workplaceListLayout(new QVBoxLayout()),
    scRotationGroupTasks(new QScrollArea()),
    scWorkplaces(new QScrollArea()),
    lblAddWorkplace(new QLabel(tr("Add Workplace to Rotation Group"))),
    lblWorkplaceDuration(new QLabel(tr("Duration [min]:"))),
    numBxWorkplaceDuration(new NumberLineEdit()),
    btnAdd(new QPushButton(this))
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QGridLayout *leftLayout = new QGridLayout;
    QGridLayout *rightLayout = new QGridLayout;

    // left part:

    scRotationGroupTasks->setWidget(rotationGroupTaskListContent);
    scRotationGroupTasks->setWidgetResizable(true);
    scRotationGroupTasks->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    FlickCharm *flickCharmRotation = new FlickCharm(this);
    flickCharmRotation->activateOn(scRotationGroupTasks);

    rotationGroupTaskListContent->setLayout(rotationGroupTaskListLayout);
    rotationGroupTaskListLayout->setAlignment(Qt::AlignTop);

    leftLayout->setAlignment(Qt::AlignTop);
    leftLayout->addWidget(lblName, 0, 0, 1, 1, 0);
    leftLayout->addWidget(txtBxName, 0, 1, 1, 1, 0);
    leftLayout->addWidget(lblTotalDuration, 1, 0, 1, 1, 0);
    leftLayout->addWidget(lblTotalDurationValue, 1, 1, 1, 1, 0);
    leftLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 2, 0, 1, 2, 0);
    leftLayout->addWidget(scRotationGroupTasks, 3, 0, 1, 2, 0);

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
    rightLayout->addWidget(lblAddWorkplace, 0, 0, 1, 2, Qt::AlignLeft);
    rightLayout->addWidget(scWorkplaces, 1, 0, 1, 2, 0);
    rightLayout->addWidget(lblWorkplaceDuration, 2, 0, 1, 1, 0);
    rightLayout->addWidget(numBxWorkplaceDuration, 2, 1, 1, 1, 0);
    rightLayout->addWidget(btnAdd, 3, 0, 1, 2, Qt::AlignCenter);

    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);


    // DUMMY DATA
    setRotationGroupDuration(160);
    addRotationGroupTask(0, "Arbeitsplatz 1", 10);
    addRotationGroupTask(1, "Arbeitsplatz 2", 20);
    addRotationGroupTask(2, "Arbeitsplatz 3", 50);
    addRotationGroupTask(0, "Arbeitsplatz 1", 10);
    addRotationGroupTask(1, "Arbeitsplatz 2", 20);
    addRotationGroupTask(2, "Arbeitsplatz 3", 50);


    addWorkplace(0, "Arbeitsplatz 1", 10);
    addWorkplace(1, "Arbeitsplatz 2", 20);
    addWorkplace(2, "Arbeitsplatz 3", 50);

    emit selectedWorkplaceChanged(-1);
}


// PUBLIC METHODS

QString RotationGroupView::getName() const{
    return txtBxName->text();
}

int RotationGroupView::getSelectedWorkplace() const {
    return selectedWorkplaceID;
}

int RotationGroupView::getWorkplaceDuration() const {
    return numBxWorkplaceDuration->getValue();
}

// PUBLIC SLOTS

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
    DetailedListItem *newListItem = new DetailedListItem(this, IconConstants::ICON_WORKPLACE, name, rotationGroupTaskCaptions, true, false, false);
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
    DetailedListItem *newListItem = new DetailedListItem(this, IconConstants::ICON_WORKPLACE, name, workplaceCaptions, false, true, false);
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

// PRIVATE SLOT

void RotationGroupView::setSelectedWorkplace(int id){
    selectedWorkplaceID = id;
    emit selectedWorkplaceChanged(id);
    // dann soll bitte die duration auf die standard duration (summe aller activities)
    // gesetzt werden
}

void RotationGroupView::btnAddClicked(){
    if(selectedWorkplaceID > -1){
        emit createRotationGroupTaskEntry();
        numBxWorkplaceDuration->clear();
        setSelectedWorkplace(-1);
    }
}


