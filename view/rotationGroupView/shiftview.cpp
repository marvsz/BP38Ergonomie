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
    btnRotation(new QPushButton()),
    btnEmployee(new QPushButton()),
    btnCalendar(new QPushButton())

{
    btnRotation->setFixedSize(45, 45);
    btnRotation->setObjectName("rotationIcon");

    btnEmployee->setFixedSize(45, 45);
    btnEmployee->setObjectName("employeeIcon");


    btnCalendar->setFixedSize(45, 45);
    btnCalendar->setObjectName("calendarIcon");

    connect(btnRotation, SIGNAL(clicked()), this, SLOT(btnRotationClicked()));
    connect(btnCalendar, SIGNAL(clicked()), this, SLOT(btnCalendarClicked()));
    connect(btnEmployee, SIGNAL(clicked()), this, SLOT(btnEmployeeClicked()));

    lblShiftData->setObjectName("lblHeader");

    oscShiftType->setValues(SHIFT_TEXTS);

    connect(oscShiftType, SIGNAL(selectionChanged(int)), this, SLOT(updateShiftTimes(int)));


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setAlignment(Qt::AlignTop);
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

    setLayout(mainLayout);
    setStartTime(QTime(6,0));
    setEndTime(QTime(14,0));
}

// PUBLIC
QList<QAbstractButton*> * ShiftView::getAdditionalNavigation() const {
    QList<QAbstractButton*> *additions = new QList<QAbstractButton*>();
    additions->append(btnRotation);
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

int ShiftView::getShiftType() const{
    return oscShiftType->getSelectedID();
}

// PUBLIC SLOTS
void ShiftView::setStartTime(const QTime &time){
    tsStart->setTime(time);
}

void ShiftView::setEndTime(const QTime &time){
    tsEnd->setTime(time);
}

void ShiftView::setShiftType(int type){
    oscShiftType->setSelectedValue(type);
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
    emit shiftTypeChanged(type);
    emit beginTimeChanged(tsStart->getTime());
    emit endTimeChanged(tsEnd->getTime());
}

void ShiftView::btnEmployeeClicked(){
    emit showView(ViewType::EMPLOYEE_VIEW);
}

void ShiftView::btnCalendarClicked(){
    emit showView(ViewType::SHIFT_CALENDAR_VIEW);
}

void ShiftView::btnRotationClicked(){
    emit showView(ViewType::ROTATION_GROUP_LIST_VIEW);
}

ShiftView::~ShiftView(){

}
