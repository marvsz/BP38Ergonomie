#include <QGridLayout>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "separator.h"
#include "shiftpauseview.h"



ShiftPauseView::ShiftPauseView(QWidget *parent) :
    QWidget(parent),
    btnBack(new QPushButton("Zurück", this)),
    lblViewDescription(new QLabel("Schicht- & Pausendaten", this)),
    lblShift(new QLabel("Schicht")),
    lblShiftType(new QLabel("Schichtart:")),
    conShiftType(new OptionSelectionControl(vecShiftType, this)),
    lblCycleTime(new QLabel("Taktzeit:")),
    timeCycleTime(new TimeLineEdit(this)),
    lblShiftBegin(new QLabel("Beginn:", this)),
    timeShiftBegin(new TimeLineEdit(this)),
    lblShiftEnd(new QLabel("Ende:", this)),
    timeShiftEnd(new TimeLineEdit(this)),
    lblQuantity(new QLabel("Stückzahl:")),
    txtQuantity(new NumberLineEdit(this)),
    lblAllowedTime(new QLabel("Vorgabezeiten", this)),
    lblSetupTime(new QLabel("Grundzeit:", this)),
    timeSetupTime(new TimeLineEdit(this)),
    lblBasicTime(new QLabel("Rüstzeit:", this)),
    timeBasicTime(new TimeLineEdit(this)),
    lblRestTime(new QLabel("Erholzeit:", this)),
    timeRestTime(new TimeLineEdit(this)),
    lblAllowanceTime(new QLabel("Verteilzeit:",this)),
    timeAllowanceTime(new TimeLineEdit(this)),
    lblBreaks(new QLabel("Pausen", this)),
    lblShortBreaks(new QLabel("Kurze Unterbrechungen:", this)),
    conShortBreaks(new OptionSelectionControl(vecShortBreaks, this)),
    lblShortBreaksBegin(new QLabel("Beginn:", this)),
    timeBreakBegin(new TimeLineEdit(this)),
    lblShortBreaksEnd(new QLabel("Ende:",this)),
    timeBreakEnd(new TimeLineEdit(this)),
    btnBreakAdd(new QPushButton("Hinzufügen",this)),
    btnBreakRemove(new QPushButton("Löschen",this))

{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *navigationBarLayout = new QGridLayout;
    QGridLayout *shiftLayout = new QGridLayout;
    QGridLayout *shiftBottomLineLayout = new QGridLayout;
    QGridLayout *allowedTimeLayout = new QGridLayout;
    QGridLayout *breakLayout = new QGridLayout;
    QGridLayout *breakBeginEndLayout = new QGridLayout;

    btnBack->setObjectName("btnNavigation");
    connect(btnBack, SIGNAL(clicked()), this, SLOT(backButtonClicked()));

    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewDescription, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, 0);

    timeCycleTime->setMaximumWidth(100);
    txtQuantity->setMaximumWidth(100);
    timeShiftBegin->setMaximumWidth(100);
    timeShiftEnd->setMaximumWidth(100);
    timeBasicTime->setMaximumWidth(100);
    timeSetupTime->setMaximumWidth(100);
    timeRestTime->setMaximumWidth(100);
    timeAllowanceTime->setMaximumWidth(100);
    timeBreakBegin->setMaximumWidth(100);
    timeBreakEnd->setMaximumWidth(100);

    shiftBottomLineLayout->addWidget(lblShiftBegin, 0, 0, 1, 1, Qt::AlignRight);
    shiftBottomLineLayout->addWidget(timeShiftBegin, 0, 1, 1, 1, Qt::AlignLeft);
    shiftBottomLineLayout->addWidget(lblShiftEnd, 0, 2, 1, 1, Qt::AlignRight);
    shiftBottomLineLayout->addWidget(timeShiftEnd, 0, 3, 1, 1, Qt::AlignLeft);
    shiftBottomLineLayout->addWidget(lblCycleTime, 0, 4, 1, 1, Qt::AlignRight);
    shiftBottomLineLayout->addWidget(timeCycleTime, 0, 5, 1, 1, Qt::AlignLeft);
    shiftBottomLineLayout->addWidget(lblQuantity, 0, 6, 1, 1, Qt::AlignRight);
    shiftBottomLineLayout->addWidget(txtQuantity, 0, 7, 1, 1, Qt::AlignLeft);

    shiftLayout->addWidget(lblShiftType,0,0,1,1,0);
    shiftLayout->addWidget(conShiftType,0,1,1,9,0);
    shiftLayout->addWidget(new Separator(Qt::Horizontal, 1, this), 1, 0, 1, 10, 0);
    shiftLayout->addLayout(shiftBottomLineLayout, 2, 0, 1, 10, 0);

    allowedTimeLayout->addWidget(lblSetupTime, 0, 0, 1, 1, Qt::AlignRight);
    allowedTimeLayout->addWidget(timeSetupTime, 0, 1, 1, 1, Qt::AlignLeft);
    allowedTimeLayout->addWidget(lblBasicTime, 0, 2, 1, 1, Qt::AlignRight);
    allowedTimeLayout->addWidget(timeBasicTime, 0, 3, 1, 1, Qt::AlignLeft);
    allowedTimeLayout->addWidget(lblRestTime, 0, 4, 1, 1, Qt::AlignRight);
    allowedTimeLayout->addWidget(timeRestTime, 0, 5, 1, 1, Qt::AlignLeft);
    allowedTimeLayout->addWidget(lblAllowanceTime, 0, 6, 1, 1, Qt::AlignRight);
    allowedTimeLayout->addWidget(timeAllowanceTime, 0, 7, 1, 1, Qt::AlignLeft);

    breakBeginEndLayout->addWidget(lblShortBreaksBegin,0,0,1,1, Qt::AlignRight);
    breakBeginEndLayout->addWidget(timeBreakBegin,0,1,1,1,Qt::AlignLeft);
    breakBeginEndLayout->addWidget(lblShortBreaksEnd,0,2,1,1,Qt::AlignRight);
    breakBeginEndLayout->addWidget(timeBreakEnd,0,3,1,1,Qt::AlignLeft);

    breakLayout->addWidget(lblShortBreaks, 0, 0, 1, 1, 0);
    breakLayout->addWidget(conShortBreaks, 0, 1, 1, 8, 0);
    breakLayout->addLayout(breakBeginEndLayout, 1, 0, 1, 9, 0);
    breakLayout->addWidget(new Separator(Qt::Vertical, 3), 0, 10, 2, 1, 0);
    breakLayout->addWidget(btnBreakAdd, 0, 11, 1, 1, 0);
    breakLayout->addWidget(btnBreakRemove, 1, 11, 1, 1, 0);

    mainLayout->addLayout(navigationBarLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));

    mainLayout->addWidget(lblShift);
    mainLayout->addLayout(shiftLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal,3,0));

    mainLayout->addWidget(lblAllowedTime);
    mainLayout->addLayout(allowedTimeLayout);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, 0));

    mainLayout->addWidget(lblBreaks);
    mainLayout->addLayout(breakLayout);

    mainLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));

    setLayout(mainLayout);
}

void ShiftPauseView::backButtonClicked(){
    emit back();
}
