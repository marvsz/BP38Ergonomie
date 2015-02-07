#include "shiftcalendar.h"
#include "flickcharm.h"
#include "QFont"
#include <QPushButton>
#include <QDebug>
#include <QToolBar>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include "../separator.h"

ShiftCalendar::ShiftCalendar(QWidget *parent,  const QTime &beginTime, const QTime &endTime) :
    SimpleNavigateableWidget(tr("Calendar"), parent),
    beginTime(beginTime),
    endTime(endTime),
    lblAddRotationGroup(new QLabel(tr("Add Rotation Group:"))),
    rotationGroupListContent(new QWidget()),
    scRotationGroups(new QScrollArea()),
    rotationGroupListLayout(new QVBoxLayout()),
    lblAddBreak(new QLabel(tr("Add break:"))),
    lblBreakDuration(new QLabel(tr("Duration [min]:"))),
    numBxBreakDuration(new NumberLineEdit()),
    btnAddBreak(new QPushButton()),
    painter(),
    picCalendar(),
    lblCalendar(new QLabel()),
    scCalendar(new QScrollArea()),
    calendarEntryLayout(new QVBoxLayout())
{ 
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
    lblCalendar->setAlignment(Qt::AlignTop);
    scCalendar->setWidget(lblCalendar);
    scCalendar->setAlignment(Qt::AlignTop);
    scCalendar->setWidgetResizable(true);
    scCalendar->setFixedWidth(500);
    scCalendar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lblCalendar->setLayout(calendarEntryLayout);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scCalendar);

    calendarEntryLayout->setAlignment(Qt::AlignRight | Qt::AlignTop);
    calendarEntryLayout->setSpacing(0);
    calendarEntryLayout->setContentsMargins(0,0,0,0);
    calendarEntryLayout->addSpacerItem(new QSpacerItem(420, 50, QSizePolicy::Fixed, QSizePolicy::Fixed));

    // LEFT PART
    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->setAlignment(Qt::AlignTop);
    leftLayout->addWidget(lblAddRotationGroup, 0, 0, 1, 3, Qt::AlignLeft);
    leftLayout->addWidget(scRotationGroups, 1, 0, 1, 3, 0);
    leftLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 2, 0, 1, 3, 0);
    leftLayout->addWidget(lblAddBreak, 3, 0, 1, 3, Qt::AlignLeft);
    leftLayout->addWidget(lblBreakDuration, 4, 0, 1, 1, Qt::AlignLeft);
    leftLayout->addWidget(numBxBreakDuration, 4, 1, 1, 1, Qt::AlignLeft);
    leftLayout->addWidget(btnAddBreak, 4, 2, 1, 1, Qt::AlignCenter);

    // RIGHT PART
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->setAlignment(Qt::AlignTop);
    rightLayout->addWidget(scCalendar);

    // MAIN LAYOUT
    QHBoxLayout *splitLayout = new QHBoxLayout;
    splitLayout->addLayout(leftLayout);
    splitLayout->addWidget(new Separator(Qt::Vertical, 3, this));
    splitLayout->addLayout(rightLayout);

    setLayout(splitLayout);

    addRotationGroup("Rotationsgruppe 1", 60);
    addRotationGroup("Rotationsgruppe 2", 90);
    addRotationGroup("Rotationsgruppe 3", 60);
    addBreak(90);
    addRotationGroup("Rotationsgruppe 1", 120);
    addRotationGroup("Rotationsgruppe 3", 30);
    addRotationGroup("Rotationsgruppe 2", 30);
    addBreak(90);
    addRotationGroup("Rotationsgruppe 1", 120);
    addRotationGroup("Rotationsgruppe 3", 30);
    addRotationGroup("Rotationsgruppe 2", 30);

    drawBackground();

}


// PUBLIC
void ShiftCalendar::setBeginTime(const QTime &beginTime){
    this->beginTime = beginTime;
    drawBackground();
}

void ShiftCalendar::setEndTime(const QTime &endTime){
    this->endTime = endTime;
    drawBackground();
}

// PUBLIC SLOTS

void ShiftCalendar::addRotationGroup(const QString &name, int duration){
    QPushButton *newItem = new QPushButton(name);
    newItem->setFixedSize(400, ((float) HOUR_HEIGHT / 60) * (float) duration);
    calendarEntryLayout->addWidget(newItem);
}

void ShiftCalendar::addBreak(int duration){
    QSpacerItem *newItem = new QSpacerItem(420, ((float) HOUR_HEIGHT / 60) * (float) duration);
    calendarEntryLayout->addSpacerItem(newItem);
}

void ShiftCalendar::clear(){
    QLayoutItem *item;
    while((item = calendarEntryLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
    calendarEntryLayout->addSpacerItem(new QSpacerItem(420, 50, QSizePolicy::Fixed, QSizePolicy::Fixed));
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

void ShiftCalendar::btnAddBreakClicked(){

}
