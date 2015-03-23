#include "shiftcalendar.h"
#include "../flickcharm.h"
#include "../../databaseHandler/dbconstants.h"
#include "QFont"
#include "../selectablevaluebutton.h"
#include <QDebug>
#include <QToolBar>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include "../separator.h"
#include "../detailedlistitem.h"


ShiftCalendar::ShiftCalendar(QWidget *parent,  const QTime &beginTime, const QTime &endTime) :
    SimpleNavigateableWidget(tr("Calendar"), parent),
    selectedOrderID(0),
    beginTime(beginTime),
    endTime(endTime),
    btnRotation(new QPushButton(this)),
    lblAddRotationGroup(new QLabel(tr("Add Rotation Group:"))),
    rotationGroupListContent(new QWidget()),
    scRotationGroups(new QScrollArea()),
    rotationGroupListLayout(new QVBoxLayout()),
    lblAddBreak(new QLabel(tr("Add break:"))),
    lblBreakDuration(new QLabel(tr("Duration [min]:"))),
    numBxBreakDuration(new NumberLineEdit()),
    btnAddBreak(new QPushButton(this)),
    currentId(-1),
    painter(),
    picCalendar(),
    lblCalendar(new QLabel()),
    scCalendar(new QScrollArea()),
    calendarEntryLayout(new QVBoxLayout()),
    btnMoveUp(new QPushButton(this)),
    btnMoveDown(new QPushButton(this)),
    btnDelete(new QPushButton(this))
{ 

    btnRotation->setFixedSize(45, 45);
    btnRotation->setObjectName("rotationIcon");
    connect(btnRotation, SIGNAL(clicked()), this, SLOT(btnRotationClicked()));

    // ROTATION GROUPS
    rotationGroupListLayout->setAlignment(Qt::AlignTop);
    rotationGroupListContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scRotationGroups->setWidget(rotationGroupListContent);
    scRotationGroups->setWidgetResizable(true);
    scRotationGroups->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scRotationGroups->setObjectName("saBordered");
    rotationGroupListContent->setLayout(rotationGroupListLayout);

    FlickCharm *flickCharmProducts = new FlickCharm(this);
    flickCharmProducts->activateOn(scRotationGroups);

    btnAddBreak->setFixedSize(45, 45);
    btnAddBreak->setObjectName("plusIcon");
    connect(btnAddBreak, SIGNAL(clicked()), this, SLOT(btnAddBreakClicked()));

    // CALENDAR
    QVBoxLayout *calendarLayout = new QVBoxLayout;
    calendarLayout->addSpacerItem(new QSpacerItem(0, 50, QSizePolicy::Fixed, QSizePolicy::Fixed));
    calendarLayout->setSpacing(0);
    calendarLayout->setContentsMargins(0,0,0,0);
    calendarLayout->addLayout(calendarEntryLayout);

    lblCalendar->setAlignment(Qt::AlignTop);
    scCalendar->setWidget(lblCalendar);
    scCalendar->setAlignment(Qt::AlignTop);
    scCalendar->setWidgetResizable(true);
    scCalendar->setFixedWidth(500);
    scCalendar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lblCalendar->setLayout(calendarLayout);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scCalendar);

    calendarEntryLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    calendarEntryLayout->setSpacing(0);
    calendarEntryLayout->setContentsMargins(0,0,0,0);

    btnMoveUp->setFixedSize(45, 45);
    btnMoveUp->setObjectName("upIcon");
    btnMoveUp->setEnabled(false);
    connect(btnMoveUp, SIGNAL(clicked()), this, SLOT(btnMoveUpClicked()));

    btnMoveDown->setFixedSize(45, 45);
    btnMoveDown->setObjectName("downIcon");
    btnMoveDown->setEnabled(false);
    connect(btnMoveDown, SIGNAL(clicked()), this, SLOT(btnMoveDownClicked()));

    btnDelete->setFixedSize(45, 45);
    btnDelete->setObjectName("resetIcon");
    btnDelete->setEnabled(false);
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(btnDeleteClicked()));

    // LEFT PART
    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->setAlignment(Qt::AlignTop);
    leftLayout->addWidget(lblAddRotationGroup, 0, 0, 1, 2, Qt::AlignLeft);
    leftLayout->addWidget(scRotationGroups, 1, 0, 1, 2, 0);
    leftLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 2, 0, 1, 2, 0);
    leftLayout->addWidget(lblAddBreak, 3, 0, 1, 2, Qt::AlignLeft);
    leftLayout->addWidget(lblBreakDuration, 4, 0, 1, 1, Qt::AlignLeft);
    leftLayout->addWidget(numBxBreakDuration, 4, 1, 1, 1, Qt::AlignLeft);
    leftLayout->addWidget(btnAddBreak, 5, 0, 1, 2, Qt::AlignCenter);

    // RIGHT PART
    QHBoxLayout *rightBottomLayout = new QHBoxLayout;
    rightBottomLayout->addWidget(btnMoveUp);
    rightBottomLayout->addWidget(btnMoveDown);
    rightBottomLayout->addWidget(btnDelete);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->setAlignment(Qt::AlignTop);
    rightLayout->addWidget(scCalendar);
    rightLayout->addLayout(rightBottomLayout);

    // MAIN LAYOUT
    QHBoxLayout *splitLayout = new QHBoxLayout;
    splitLayout->addLayout(leftLayout);
    splitLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    splitLayout->addLayout(rightLayout);

    setLayout(splitLayout);

    drawBackground();
}


// PUBLIC
QList<QAbstractButton*> * ShiftCalendar::getAdditionalNavigation() const {
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnRotation);
    return additions;
}

// PUBLIC SLOTS
// IRotationGroupTaskList
void  ShiftCalendar::addRotationGroupTask(QHash<QString, QVariant> values){
    QList<QStringList> dliValues = QList<QStringList>() << (QStringList() << values.value(DBConstants::COL_ROTATION_GROUP_TASK_DURATION).toString());
    DetailedListItem *newListItem = new DetailedListItem(this, "rotationIcon", values.value(DBConstants::COL_ROTATION_GROUP_TASK_NAME).toString(), rotationGroupCaptions, false, false, false, true, false);
    newListItem->setValues(dliValues);
    newListItem->setID(values.value(DBConstants::COL_ROTATION_GROUP_TASK_ID).toInt());
    connect(newListItem, SIGNAL(addItem(int)), this, SLOT(dliRotationGroupTaskAddClicked(int)));
    rotationGroupListLayout->addWidget(newListItem);
}

void ShiftCalendar::updateRotationGroupTask(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int i = 0;
    int id = values.value(DBConstants::COL_ROTATION_GROUP_TASK_ID).toInt();
    while((item = rotationGroupListLayout->itemAt(i)) != NULL){
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

void ShiftCalendar::removeRotationGroupTask(int id){
    QLayoutItem *item;
    int i = 0;
    while((item = rotationGroupListLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == id){
            rotationGroupListLayout->removeItem(item);
            delete item->widget();
            delete item;
            break;
        }
        i++;
    }
}

void ShiftCalendar::clearRotationGroupTasks(){
    QLayoutItem *item;
    while((item = rotationGroupListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

// IRotationGroup
void ShiftCalendar::addRotationGroupEntry(QHash<QString, QVariant> values){
    DetailedListItem *newListItem = new DetailedListItem(this, "workplaceIcon", values.value(DBConstants::COL_ROTATION_GROUP_TASK_NAME).toString(), QList<QStringList>(), false, true, false, false, false);
    int orderNumber = values.value(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER).toInt();
    newListItem->setID(orderNumber);
    newListItem->setFixedSize(350, ((float) HOUR_HEIGHT / 60) * (float) values.value(DBConstants::COL_ROTATION_GROUP_TASK_DURATION).toInt());
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedEntryChanged(int)));
    connect(newListItem, SIGNAL(deselected(int)), this, SLOT(deselectEntry(int)));
    connect(this, SIGNAL(selectedEntry(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    if(calendarEntryLayout->count() == 0)
        calendarEntryLayout->addWidget(newListItem);
    else{
        QLayoutItem *item;
        int i = 0;
        while((item = calendarEntryLayout->itemAt(i)) != NULL){
            DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
            if(dli->getID() == orderNumber - 1)
                calendarEntryLayout->insertWidget(i+1, newListItem);
            i++;
        }
    }

}

void ShiftCalendar::updateRotationGroupEntry(QHash<QString, QVariant> values){
    QLayoutItem *item;
    int i = 0;
    while((item = calendarEntryLayout->itemAt(i)) != NULL){
        DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
        if(dli->getID() == values.value(DBConstants::COL_ROTATION_GROUP_ENTRY_ID)){
                dli->setName(values.value(DBConstants::COL_ROTATION_GROUP_TASK_NAME).toString());
                dli->setFixedSize(350, ((float) HOUR_HEIGHT / 60) * (float) values.value(DBConstants::COL_ROTATION_GROUP_TASK_DURATION).toInt());
            break;
        }
        i++;
    }
}

void ShiftCalendar::addRotationGroupBreakEntry(QHash<QString, QVariant> values){
    DetailedListItem *newListItem = new DetailedListItem(this, "btnIcon", tr("Break"), QList<QStringList>(), false, true, false, false, false);
    int orderNumber = values.value(DBConstants::COL_ROTATION_GROUP_ORDER_NUMBER).toInt();
    newListItem->setID(orderNumber);
    newListItem->setFixedSize(350, ((float) HOUR_HEIGHT / 60) * (float) values.value(DBConstants::COL_BREAK_DURATION).toInt());
    connect(newListItem, SIGNAL(selected(int)), this, SLOT(selectedEntryChanged(int)));
    connect(newListItem, SIGNAL(deselected(int)), this, SLOT(deselectEntry(int)));
    connect(this, SIGNAL(selectedEntry(int)), newListItem, SLOT(selectExclusiveWithID(int)));
    if(calendarEntryLayout->count() == 0)
        calendarEntryLayout->addWidget(newListItem);
    else{
        QLayoutItem *item;
        int i = 0;
        while((item = calendarEntryLayout->itemAt(i)) != NULL){
            DetailedListItem *dli = qobject_cast<DetailedListItem*>(item->widget());
            if(dli->getID() == orderNumber - 1)
                calendarEntryLayout->insertWidget(i+1, newListItem);
            i++;
        }
    }
}

void ShiftCalendar::clearRotationGroup(){
    QLayoutItem *item;
    while((item = calendarEntryLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

// IShift
void ShiftCalendar::setShift(QHash<QString, QVariant> values){
    beginTime = values.value(DBConstants::COL_SHIFT_START).toTime();
    endTime = values.value(DBConstants::COL_SHIFT_END).toTime();
    drawBackground();
}

// PRIVATE
void ShiftCalendar::drawBackground(){
    int begin = beginTime.hour();
    int end = endTime.minute() > 0 ? endTime.hour() + 1 : endTime.hour();

    // if shift goes from one day to the next
    if (end <= begin)
        end += 24;

    int range = end - begin +1;

    painter.begin(&picCalendar);
    QFont font = painter.font();
    font.setPointSize(18);
    painter.setFont(font);
    int fontHeight = painter.fontMetrics().height();

    painter.setRenderHint(QPainter::Antialiasing);

    // So the picture does not align top left with empty space
    painter.setPen(QPen(QColor(255,255,255,0), 0, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(0, 0, 1, 0);

    painter.setPen(QPen(QColor("#8e8e93"), 1, Qt::SolidLine, Qt::FlatCap));
    for(int i = 0; i < range; ++i){
        int y = 50+i*HOUR_HEIGHT;
        painter.drawText(0, y + fontHeight / 2, QTime((begin+i) % 24, 0).toString("HH:mm"));
        painter.drawLine(50, y, 480, y);
    }

    painter.setPen(QPen(QColor(255,255,255,0), 0, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(0, 50 + range * HOUR_HEIGHT, 1, 50 + range * HOUR_HEIGHT);

    painter.end();

    lblCalendar->setPicture(picCalendar);
    lblCalendar->repaint();
    lblCalendar->adjustSize();
}

// PRIVATE SLOTS
void ShiftCalendar::btnAddBreakClicked(){
    if(numBxBreakDuration->getValue() > 0){
        QHash<QString, QVariant> values = QHash<QString, QVariant>();
        values.insert(DBConstants::COL_BREAK_DURATION, numBxBreakDuration->getValue());
        emit createRotationGroupBreakEntry(values);
        numBxBreakDuration->clear();
    }
    else
        emit showMessage(tr("You have to enter a duration for the break!"), NotificationMessage::ERROR);
}

void ShiftCalendar::btnRotationClicked(){
    emit showView(ViewType::ROTATION_GROUP_TASK_LIST_VIEW);
}

void ShiftCalendar::dliRotationGroupTaskAddClicked(int id){
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(DBConstants::COL_ROTATION_GROUP_ENTRY_ID, id);
    emit createRotationGroupEntry(values);
}

void ShiftCalendar::btnMoveUpClicked(){
    emit requestMoveEntryUp(selectedOrderID);
    selectedEntryChanged(0);
}

void ShiftCalendar::btnMoveDownClicked(){
    emit requestMoveEntryDown(selectedOrderID);
    selectedEntryChanged(0);
}

void ShiftCalendar::btnDeleteClicked(){
    emit requestRemoveEntry(selectedOrderID);
    selectedEntryChanged(0);
}

void ShiftCalendar::selectedEntryChanged(int id){
    selectedOrderID = id;
    if(selectedOrderID != 0)
        btnDelete->setEnabled(true);
    else{
        btnDelete->setEnabled(false);
        btnMoveUp->setEnabled(false);
        btnMoveDown->setEnabled(false);
    }
    if(selectedOrderID == 1)
        btnMoveUp->setEnabled(false);
    if(selectedOrderID == calendarEntryLayout->count())
        btnMoveDown->setEnabled(false);
    if(selectedOrderID > 1)
        btnMoveUp->setEnabled(true);
    if(selectedOrderID > 0 && selectedOrderID < calendarEntryLayout->count())
        btnMoveDown->setEnabled(true);

    emit selectedEntry(id);
}

void ShiftCalendar::deselectEntry(int id){
    if(id == selectedOrderID)
        selectedEntryChanged(0);
}


ShiftCalendar::~ShiftCalendar(){

}

