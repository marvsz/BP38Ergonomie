#include "shiftview.h"
#include "separator.h"
#include "flickcharm.h"

ShiftView::ShiftView(QWidget *parent) :
    QWidget(parent),
    oscShiftType(new OptionSelectionControl()),
    timeBxStart(new TimeLineEdit(this, TimeLineType::HOUR_MINUTE)),
    timeBxEnd(new TimeLineEdit(this, TimeLineType::HOUR_MINUTE)),
    lblShiftData(new QLabel(tr("Shift data:"))),
    lblShiftType(new QLabel(tr("Shift Type:"))),
    lblStart(new QLabel(tr("Begin:"))),
    lblEnd(new QLabel(tr("End:"))),
    lblEmployee(new QLabel(tr("Choose Employee:"))),
    btnChooseEmployee(new QPushButton()),
    dliEmployee(new DetailedListItem(0, "", "Mitarbeiter:", QList<QStringList>(), false, false, false)),
    lblAddBreak(new QLabel(tr("Add break:"))),
    lblBreakDuration(new QLabel(tr("Duration [min]:"))),
    numBxBreakDuration(new NumberLineEdit()),
    btnAddBreak(new QPushButton()),
    lblAddRotationGroup(new QLabel(tr("Add Rotation Group:"))),
    rotationGroupListContent(new QWidget()),
    scRotationGroups(new QScrollArea()),
    rotationGroupListLayout(new QVBoxLayout()),
    btnMoreRotationGroups(new QPushButton()),
    calendar(new ShiftCalendar(0, QTime(6,0), QTime(14,0))),
    btnBack(new QPushButton()),
    lblViewName(new QLabel(tr("shift"))),
    btnFeedback(new QPushButton())
{
    btnBack->setFixedSize(45, 45);
    btnBack->setObjectName("leftIcon");

    btnFeedback->setFixedSize(45, 45);
    btnFeedback->setObjectName("feedbackIcon");

    btnChooseEmployee->setFixedSize(45, 45);
    btnChooseEmployee->setObjectName("editIcon");

    btnAddBreak->setFixedSize(45, 45);
    btnAddBreak->setObjectName("plusIcon");

    btnMoreRotationGroups->setFixedSize(45, 45);
    btnMoreRotationGroups->setObjectName("editIcon");

    connect(btnBack, SIGNAL(clicked()), this, SIGNAL(back()));

    connect(timeBxStart, SIGNAL(editingFinished()), this, SLOT(updateCalendarStart()));
    connect(timeBxEnd, SIGNAL(editingFinished()), this, SLOT(updateCalendarEnd()));

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

    QGridLayout *navigationBarLayout = new QGridLayout;
    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewName, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(btnFeedback, 0, 2, 1, 1, Qt::AlignRight);

    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->setContentsMargins(0,0,0,0);
    leftLayout->addWidget(lblShiftData, 0, 0, 1, 4, Qt::AlignLeft);
    leftLayout->addWidget(lblShiftType, 1, 0, 1, 4, Qt::AlignLeft);
    leftLayout->addWidget(oscShiftType, 2, 0, 1, 4, 0);
    leftLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 3, 0, 1, 4, 0);
    leftLayout->addWidget(lblStart, 4, 0, 1, 2, Qt::AlignCenter);
    leftLayout->addWidget(lblEnd, 4, 2, 1, 2, Qt::AlignCenter);
    leftLayout->addWidget(timeBxStart, 5, 0, 1, 2, Qt::AlignCenter);
    leftLayout->addWidget(timeBxEnd, 5, 2, 1, 2, Qt::AlignCenter);
    leftLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 6, 0, 1, 4, 0);
    leftLayout->addWidget(lblEmployee, 7, 0, 1, 2, Qt::AlignLeft);
    leftLayout->addWidget(btnChooseEmployee, 7, 2, 1, 2, Qt::AlignCenter);
    leftLayout->addWidget(dliEmployee, 8, 0, 1, 4, 0);
    leftLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 9, 0, 1, 4, 0);
    leftLayout->addWidget(lblAddBreak, 10, 0, 1, 4, Qt::AlignLeft);
    leftLayout->addWidget(lblBreakDuration, 11, 0, 1, 1, Qt::AlignCenter);
    leftLayout->addWidget(numBxBreakDuration, 11, 1, 2, 2, Qt::AlignCenter);
    leftLayout->addWidget(btnAddBreak, 11, 3, 1, 1, Qt::AlignCenter);
    leftLayout->addWidget(new Separator(Qt::Horizontal, 3, 0), 12, 0, 1, 4, 0);
    leftLayout->addWidget(lblAddRotationGroup, 13, 0, 1, 4, 0);
    leftLayout->addWidget(scRotationGroups, 14, 0, 1, 4, 0);
    leftLayout->addWidget(btnMoreRotationGroups, 15, 0, 1, 4, Qt::AlignCenter);
    leftLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 16, 0, 1, 4, 0);

    QHBoxLayout *splitLayout = new QHBoxLayout;
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addLayout(leftLayout);
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addWidget(new Separator(Qt::Vertical, 3, 0));
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
    splitLayout->addWidget(calendar);
    splitLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));
    mainLayout->addLayout(splitLayout);

    setStartTime(QTime(6,0));
    setEndTime(QTime(14,0));

    setLayout(mainLayout);

}

// PUBLIC
QTime ShiftView::getStartTime() const{
    return timeBxStart->getValue();
}

QTime ShiftView::getEndTime() const{
    return timeBxEnd->getValue();
}

QString ShiftView::getType() const{
    return oscShiftType->getSelectedTexts();
}

// PUBLIC SLOTS
void ShiftView::setStartTime(const QTime &time){
    timeBxStart->setValue(time);
    calendar->setBeginTime(time);
}

void ShiftView::setEndTime(const QTime &time){
    timeBxEnd->setValue(time);
    calendar->setEndTime(time);
}

// PRIVATE SLOTS
void ShiftView::updateCalendarStart(){
    setStartTime(timeBxStart->getValue());
}

void ShiftView::updateCalendarEnd(){
    setEndTime(timeBxEnd->getValue());
}

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
