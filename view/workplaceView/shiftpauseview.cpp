#include <QGridLayout>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTime>
#include "separator.h"
#include "shiftpauseview.h"



ShiftPauseView::ShiftPauseView(QWidget *parent) :
    QWidget(parent),
    btnBack(new QPushButton("Zurück", this)),
    lblViewDescription(new QLabel("Schicht- & Pausendaten", this)),
    lblShift(new QLabel("Schicht")),
    lblShiftType(new QLabel("Schichtart:")),
    conShiftType(new OptionSelectionControl(vecShiftType, this)),
    lblShiftBegin(new QLabel("Beginn:", this)),
    timeShiftBegin(new TimeLineEdit(this)),
    lblShiftEnd(new QLabel("Ende:", this)),
    timeShiftEnd(new TimeLineEdit(this)),
    lblQuantity(new QLabel("Stückzahl:")),
    txtQuantity(new NumberLineEdit(this)),
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
    QGridLayout *breakLayout = new QGridLayout;
    QGridLayout *breakBeginEndLayout = new QGridLayout;

    btnBack->setObjectName("btnNavigation");
    connect(btnBack, SIGNAL(clicked()), this, SLOT(backButtonClicked()));

    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewDescription, 0, 1, 1, 1, Qt::AlignCenter);
    navigationBarLayout->addWidget(new QLabel(), 0, 2, 1, 1, 0);

    txtQuantity->setMaximumWidth(100);
    timeShiftBegin->setMaximumWidth(100);
    timeShiftEnd->setMaximumWidth(100);
    timeBreakBegin->setMaximumWidth(100);
    timeBreakEnd->setMaximumWidth(100);

    shiftBottomLineLayout->addWidget(lblShiftBegin, 0, 0, 1, 1, Qt::AlignRight);
    shiftBottomLineLayout->addWidget(timeShiftBegin, 0, 1, 1, 1, Qt::AlignLeft);
    shiftBottomLineLayout->addWidget(lblShiftEnd, 0, 2, 1, 1, Qt::AlignRight);
    shiftBottomLineLayout->addWidget(timeShiftEnd, 0, 3, 1, 1, Qt::AlignLeft);
    shiftBottomLineLayout->addWidget(lblQuantity, 0, 4, 1, 1, Qt::AlignRight);
    shiftBottomLineLayout->addWidget(txtQuantity, 0, 5, 1, 1, Qt::AlignLeft);

    shiftLayout->addWidget(lblShiftType,0,0,1,1,0);
    shiftLayout->addWidget(conShiftType,0,1,1,9,0);
    shiftLayout->addWidget(new Separator(Qt::Horizontal, 1, this), 1, 0, 1, 10, 0);
    shiftLayout->addLayout(shiftBottomLineLayout, 2, 0, 1, 10, 0);

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

    mainLayout->addWidget(lblBreaks);
    mainLayout->addLayout(breakLayout);

    mainLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));

    setLayout(mainLayout);
}

//PUBLIC SLOTS

void ShiftPauseView::setShift(const QString &shiftType, const QTime &shiftBegin, const QTime &shiftEnd){
    conShiftType->setSelectedValue(shiftType);
    timeShiftBegin->setValue(shiftBegin);
    timeShiftEnd->setValue(shiftEnd);
}

void ShiftPauseView::setBreak(const QTime &breakBegin, const QTime &breakEnd){
    timeBreakBegin->setValue(breakBegin);
    timeBreakEnd->setValue(breakEnd);
}


QTime ShiftPauseView::getShiftBegin() const{
    timeShiftBegin->getValue();
}

QTime ShiftPauseView::getShiftEnd() const{
    timeShiftEnd->getValue();
}

int ShiftPauseView::getQuantity() const{
    txtQuantity->getValue();
}

QTime ShiftPauseView::getBreakBegin() const{
    timeBreakBegin->getValue();
}

QTime ShiftPauseView::getBreakEnd() const{
    timeBreakEnd->getValue();
}

//PRIVATE SLOTS
void ShiftPauseView::backButtonClicked(){
    emit back();
}

// GETTER
