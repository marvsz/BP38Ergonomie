#include "shiftcalendar.h"
#include "flickcharm.h"
#include "QFont"
#include "../selectablevaluebutton.h"
#include <QDebug>
#include <QToolBar>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include "../separator.h"
#include "../detailedlistitem.h"

const QList<QStringList> ShiftCalendar::rotationGroupCaptions = QList<QStringList>() << (QStringList() << tr("Duration") << tr("Workplaces"));

ShiftCalendar::ShiftCalendar(QWidget *parent,  const QTime &beginTime, const QTime &endTime) :
    SimpleNavigateableWidget(tr("Calendar"), parent),
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
    lblBreakName(new QLabel(tr("Name:"))),
    txtBxBreakName(new TextLineEdit()),
    btnAddBreak(new QPushButton(this)),
    currentId(-1),
    painter(),
    picCalendar(),
    lblCalendar(new QLabel()),
    scCalendar(new QScrollArea()),
    calendarEntryLayout(new QVBoxLayout()),
    calendarEntries(new QVector<SelectableValueButton*>),
    btnMoveUp(new QPushButton(this)),
    btnMoveDown(new QPushButton(this)),
    btnDelete(new QPushButton(this))
{ 

    btnRotation->setFixedSize(45, 45);
    btnRotation->setObjectName("rotationIcon");
    connect(btnRotation, SIGNAL(clicked()), this, SLOT(btnRotationClicked()));
    // ROTATION GROUPS
    rotationGroupListContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scRotationGroups->setWidget(rotationGroupListContent);
    scRotationGroups->setWidgetResizable(true);
    scRotationGroups->setFixedHeight(400);
    scRotationGroups->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
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
    leftLayout->addWidget(lblBreakName, 5, 0, 1, 1, Qt::AlignLeft);
    leftLayout->addWidget(txtBxBreakName, 5, 1, 1, 1, Qt::AlignLeft);
    leftLayout->addWidget(btnAddBreak, 6, 0, 1, 2, Qt::AlignCenter);

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

    // Dummy Data
    addSelectionRotationGroup(0, 60, 3, "Rotationsgruppe 1");
    addSelectionRotationGroup(1, 120, 10, "Rotationsgruppe 2");
    addSelectionRotationGroup(2, 20, 1, "Rotationsgruppe 3");
    addSelectionRotationGroup(3, 60, 2, "Rotationsgruppe 4");

    addCalendarRotationGroup(0, 60, "Rotationsgruppe 1");
    addCalendarBreak(1, 70, "Pause");
    addCalendarRotationGroup(2, 60, "Rotationsgruppe 4");
    addCalendarRotationGroup(2, 60, "Rotationsgruppe 3");
    addCalendarBreak(1, 70, "Pause");
    addCalendarRotationGroup(2, 60, "Rotationsgruppe 3");

}


// PUBLIC
QList<QAbstractButton*> * ShiftCalendar::getAdditionalNavigation() const {
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnRotation);
    return additions;
}

// PUBLIC SLOTS

void ShiftCalendar::setBeginTime(const QTime &beginTime){
    this->beginTime = beginTime;
    drawBackground();
}

void ShiftCalendar::setEndTime(const QTime &endTime){
    this->endTime = endTime;
    drawBackground();
}

void ShiftCalendar::addSelectionRotationGroup(int id, int duration, int workplaces, const QString &name){
    QList<QStringList> values = QList<QStringList>() << (QStringList() << QString::number(duration).append(" min") << QString::number(workplaces));
    DetailedListItem *newItem = new DetailedListItem(0, "rotationIcon", name, rotationGroupCaptions, false, false, false, true);
    newItem->setValues(values);
    newItem->setID(id);
    connect(newItem, SIGNAL(addItem(int)), this, SIGNAL(createCalendarRotationGroup(int)));
    rotationGroupListLayout->addWidget(newItem);
}

void ShiftCalendar::clearSelection(){
    QLayoutItem *item;
    while((item = rotationGroupListLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void ShiftCalendar::addCalendarRotationGroup(int id, int duration, const QString &name){
    SelectableValueButton *newItem = new SelectableValueButton(id, name, 0);
    newItem->setText(name);
    newItem->setFixedSize(350, ((float) HOUR_HEIGHT / 60) * (float) duration);
    calendarEntryLayout->addWidget(newItem);
    calendarEntries->append(newItem);
}

void ShiftCalendar::addCalendarBreak(int id, int duration, const QString &name){
    SelectableValueButton *newItem = new SelectableValueButton(id, name, 0);
    newItem->setText(name);
    newItem->setFixedSize(350, ((float) HOUR_HEIGHT / 60) * (float) duration);
    connect(newItem, SIGNAL(clickedWithID(int)), this, SLOT(setSelectedId(int)));
    calendarEntries->append(newItem);
    calendarEntryLayout->addWidget(newItem);
}

void ShiftCalendar::clearCalendar(){
    QLayoutItem *item;
    while((item = calendarEntryLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
    currentId = -1;
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

    painter.setPen(QPen(QColor("#007AFF"), 1, Qt::SolidLine, Qt::FlatCap));
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
    emit createBreak();
    numBxBreakDuration->clear();
    txtBxBreakName->clear();
}

void ShiftCalendar::btnRotationClicked(){
    emit showView(ViewType::ROTATION_GROUP_LIST_VIEW);
}

void ShiftCalendar::setSelectedId(int id){
    currentId = id;
    for(int i = 0; i < calendarEntries->length(); ++i) {
        SelectableValueButton *entry = calendarEntries->at(i);
        entry->setSelected(entry->getID() == id);
    }

    /*if(id >= 0 && id < calendarEntries->length()){
            for(int i = 0; i < calendarEntries->length(); ++i){
                SelectableValueButton *btn = calendarEntries->at(i);
                if(btn->getID() == id){
                   btn->setSelected(true);
                }
                else
                    btn->setSelected(false);
            }
            btnDelete->setEnabled(true);
    } else{
        btnDelete->setEnabled(false);
    }

    if ( id <= 0){
        btnMoveUp->setEnabled(false);
    } else{
        btnMoveUp->setEnabled(true);
    }
    if (id >= calendarEntries->length()-1){
        btnMoveDown->setEnabled(false);
    } else{
        btnMoveDown->setEnabled(true);
    }*/
}

void ShiftCalendar::btnMoveUpClicked(){
    /*SelectableValueButton* item = calendarEntries->at(currentId);
    calendarEntryLayout->removeWidget(item);
    calendarEntryLayout->insertWidget(currentId-1, item);

    calendarEntries->at(currentId)->setID(currentId-1);
    calendarEntries->at(currentId-1)->setID(currentId);

    calendarEntries->replace(currentId, calendarEntries->at(currentId-1));
    calendarEntries->replace(currentId -1, item);

    setSelectedId(currentId-1);*/
}

void ShiftCalendar::btnMoveDownClicked(){
    /*SelectableValueButton* item = calendarEntries->at(currentId);
    calendarEntryLayout->removeWidget(item);
    calendarEntryLayout->insertWidget(currentId+1, item);

    calendarEntries->at(currentId)->setID(currentId+1);
    calendarEntries->at(currentId+1)->setID(currentId);

    calendarEntries->replace(currentId, calendarEntries->at(currentId+1));
    calendarEntries->replace(currentId+1, item);

    setSelectedId(currentId+1);*/
}

void ShiftCalendar::btnDeleteClicked(){
    /*SelectableValueButton* item = calendarEntries->at(currentId);
    calendarEntryLayout->removeWidget(item);
    delete item;

    for(int i = currentId; i < calendarEntries->length(); i++){
        calendarEntries->at(i)->setID(i-1);
    }

    calendarEntries->removeAt(currentId);
    nextID--;
    setSelectedId(-1);*/

}

ShiftCalendar::~ShiftCalendar(){

}

