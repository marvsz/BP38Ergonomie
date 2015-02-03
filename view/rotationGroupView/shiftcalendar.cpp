#include "shiftcalendar.h"
#include "flickcharm.h"
#include "QFont"
#include <QPushButton>
#include <QDebug>
#include <QToolBar>
#include <QDialogButtonBox>

ShiftCalendar::ShiftCalendar(QWidget *parent,  const QTime &beginTime, const QTime &endTime) :
    SimpleNavigateableWidget(tr("Calendar"), parent),
    beginTime(beginTime),
    endTime(endTime),
    painter(),
    picCalendar(),
    lblCalendar(new QLabel()),
    scCalendar(new QScrollArea()),
    calendarEntryLayout(new QVBoxLayout())
{ 
    scCalendar->setWidget(lblCalendar);
    scCalendar->setAlignment(Qt::AlignTop);
    scCalendar->setWidgetResizable(true);
    scCalendar->setMinimumWidth(500);
    scCalendar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scCalendar);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    mainLayout->addWidget(scCalendar);
    mainLayout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    setLayout(mainLayout);

    calendarEntryLayout->setAlignment(Qt::AlignRight | Qt::AlignTop);
    calendarEntryLayout->setSpacing(0);
    calendarEntryLayout->setContentsMargins(0,0,0,0);
    calendarEntryLayout->addSpacerItem(new QSpacerItem(420, 50, QSizePolicy::Fixed, QSizePolicy::Fixed));

    addRotationGroup("Rotationsgruppe 1", 60);
    addRotationGroup("Rotationsgruppe 2", 90);
    addRotationGroup("Rotationsgruppe 3", 60);
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
    calendarEntryLayout->addItem(newItem);
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
