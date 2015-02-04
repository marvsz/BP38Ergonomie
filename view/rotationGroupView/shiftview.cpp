#include "shiftview.h"
#include "separator.h"
#include "flickcharm.h"

ShiftView::ShiftView(QWidget *parent) :
    SimpleNavigateableWidget(tr("Shift Data"), parent),
    oscShiftType(new OptionSelectionControl()),
    tsStart(new TimeSpinner(this)),
    tsEnd(new TimeSpinner(this)),
    lblShiftData(new QLabel(tr("Shift data"))),
    lblShiftType(new QLabel(tr("Shift Type:"))),
    lblShiftTimes(new QLabel(tr("Shift times:"))),
    lblStart(new QLabel(tr("Begin:"))),
    lblEnd(new QLabel(tr("End:"))),
    lblAddBreak(new QLabel(tr("Add break:"))),
    lblBreakDuration(new QLabel(tr("Duration [min]:"))),
    numBxBreakDuration(new NumberLineEdit()),
    btnAddBreak(new QPushButton()),
    lblAddRotationGroup(new QLabel(tr("Add Rotation Group:"))),
    rotationGroupListContent(new QWidget()),
    scRotationGroups(new QScrollArea()),
    rotationGroupListLayout(new QVBoxLayout()),
    btnMoreRotationGroups(new QPushButton()),
    btnEmployee(new QPushButton()),
    btnCalendar(new QPushButton())

{
    btnEmployee->setFixedSize(45, 45);
    btnEmployee->setObjectName("employeeIcon");

    btnAddBreak->setFixedSize(45, 45);
    btnAddBreak->setObjectName("plusIcon");

    btnMoreRotationGroups->setFixedSize(45, 45);
    btnMoreRotationGroups->setObjectName("editIcon");

    btnCalendar->setFixedSize(45, 45);
    btnCalendar->setObjectName("calendarIcon");

    connect(btnCalendar, SIGNAL(clicked()), this, SLOT(btnCalendarClicked()));
    connect(btnAddBreak, SIGNAL(clicked()), this, SLOT(btnAddBreakClicked()));
    connect(btnMoreRotationGroups, SIGNAL(clicked()), this, SLOT(btnMoreRotationGroupsClicked()));
    connect(btnEmployee, SIGNAL(clicked()), this, SLOT(btnEmployeeClicked()));

    lblShiftData->setObjectName("lblHeader");

    oscShiftType->setValues(SHIFT_TEXTS);

    connect(oscShiftType, SIGNAL(selectionChanged(int)), this, SLOT(updateShiftTimes(int)));

    rotationGroupListContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scRotationGroups->setWidget(rotationGroupListContent);
    scRotationGroups->setWidgetResizable(true);
    scRotationGroups->setFixedHeight(130);
    scRotationGroups->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    scRotationGroups->setObjectName("saBordered");
    rotationGroupListContent->setLayout(rotationGroupListLayout);

    FlickCharm *flickCharmProducts = new FlickCharm(this);
    flickCharmProducts->activateOn(scRotationGroups);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(lblShiftData, 0, 0, 1, 4, Qt::AlignLeft);
    mainLayout->addWidget(lblShiftType, 1, 0, 1, 4, Qt::AlignLeft);
    mainLayout->addWidget(oscShiftType, 2, 0, 1, 4, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 3, 0, 1, 4, 0);
    mainLayout->addWidget(lblShiftTimes, 4, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(lblStart, 5, 0, 1, 2, Qt::AlignCenter);
    mainLayout->addWidget(lblEnd, 5, 2, 1, 2, Qt::AlignCenter);
    mainLayout->addWidget(tsStart, 6, 0, 1, 2, Qt::AlignCenter);
    mainLayout->addWidget(tsEnd, 6, 2, 1, 2, Qt::AlignCenter);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 7, 0, 1, 4, 0);
    mainLayout->addWidget(lblAddBreak, 8, 0, 1, 4, Qt::AlignLeft);
    mainLayout->addWidget(lblBreakDuration, 9, 0, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(numBxBreakDuration, 9, 1, 2, 2, Qt::AlignLeft);
    mainLayout->addWidget(btnAddBreak, 9, 3, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 10, 0, 1, 4, 0);
    mainLayout->addWidget(lblAddRotationGroup, 11, 0, 1, 4, 0);
    mainLayout->addWidget(scRotationGroups, 12, 0, 1, 4, 0);
    mainLayout->addWidget(btnMoreRotationGroups, 13, 0, 1, 4, Qt::AlignCenter);
    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 14, 0, 1, 4, 0);

    setLayout(mainLayout);
    setStartTime(QTime(6,0));
    setEndTime(QTime(14,0));
}

// PUBLIC
QList<QAbstractButton*> * ShiftView::getAdditionalNavigation() const {
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnEmployee);
    additions->append(btnCalendar);
    return additions;
}

QTime ShiftView::getStartTime() const{
    return tsStart->getTime();
}

QTime ShiftView::getEndTime() const{
    return tsEnd->getTime();
}

QString ShiftView::getType() const{
    return oscShiftType->getSelectedTexts();
}

// PUBLIC SLOTS
void ShiftView::setStartTime(const QTime &time){
    tsStart->setTime(time);
}

void ShiftView::setEndTime(const QTime &time){
    tsEnd->setTime(time);
}

// PRIVATE SLOTS
void ShiftView::updateShiftTimes(int type){
    switch(type){
    case(0):
        setStartTime(QTime(6,0));
        setEndTime(QTime(14, 0));
        break;
    case(1):
        setStartTime(QTime(14,0));
        setEndTime(QTime(22, 0));
        break;
    case(2):
        setStartTime(QTime(22,0));
        setEndTime(QTime(6, 0));
        break;
    case(3):
        setStartTime(QTime(0,0));
        setEndTime(QTime(0, 0));
        break;
    }
}

void ShiftView::btnAddBreakClicked(){

}

void ShiftView::btnEmployeeClicked(){
    emit show(ViewType::EMPLOYEE_VIEW);
}

void ShiftView::btnCalendarClicked(){
    emit show(ViewType::SHIFT_CALENDAR_VIEW);
}

void ShiftView::btnMoreRotationGroupsClicked(){
    emit show(ViewType::ROTATION_GROUP_VIEW);
}
