#include <QGridLayout>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "separator.h"
#include "shiftandpausedata.h"



ShiftAndPauseData::ShiftAndPauseData(QWidget *parent) :
    QWidget(parent),
    btnBack(new QPushButton("Zurück", this)),
    lblViewDescription(new QLabel("Schicht- & Pausendaten", this)),
    lblShift(new QLabel("Shicht")),
    lblShiftType(new QLabel("Schichtart:")),
    conShiftType(new OptionSelectionControl(vecShiftType, this)),
    lblCycleTime(new QLabel("Taktzeit")),
    timeCycleTime(new TimeLineEdit(this)),
    lblShiftBegin(new QLabel("Begin:", this)),
    timeShiftBegin(new TimeLineEdit(this)),
    lblShiftEnd(new QLabel("Ende:", this)),
    timeShiftEnd(new TimeLineEdit(this)),
    lblAllowedTime(new QLabel("Vorgabezeiten", this)),
    lblSetupTime(new QLabel("Grundzeit", this)),
    timeSetupTime(new TimeLineEdit(this)),
    lblBasicTime(new QLabel("Rüstzeit", this)),
    timeBasicTime(new TimeLineEdit(this)),
    lblRestTime(new QLabel("Erholzeit", this)),
    timeRestTime(new TimeLineEdit(this)),
    lblAllowanceTime(new QLabel("Verteilzeit",this)),
    lblBreaks(new QLabel("Pausen", this)),
    lblShortBreaks(new QLabel("Kurze Unterbrechungen:", this)),
    conShortBreaks(new OptionSelectionControl(vecShortBreaks, this)),
    lblShortBreaksBegin(new QLabel("Begin", this)),
    timeBreakBegin(new TimeLineEdit(this)),
    lblShortBreaksEnd(new QLabel("Ende:",this)),
    timeBreakEnd(new TimeLineEdit(this)),
    btnBreakAdd(new QPushButton("Hinzufügen",this)),
    btnBreakRemove(new QPushButton("Löschen",this))

{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *navigationBarLayout = new QGridLayout;
    QGridLayout *shiftLayout = new QGridLayout;
    QHBoxLayout *allowedTimeLayout = new QHBoxLayout;
    QGridLayout *breakLayout = new QGridLayout;

    btnBack->setObjectName("btnNavigation");
    connect(btnBack, SIGNAL(clicked()), this, SLOT(backButtonClicked()));

    navigationBarLayout->addWidget(btnBack, 0, 0, 1, 1, Qt::AlignLeft);
    navigationBarLayout->addWidget(lblViewDescription, 0, 1, 1, 1, Qt::AlignCenter);

    shiftLayout->addWidget(lblShiftType,0,0,1,1,0);
    shiftLayout->addWidget(conShiftType,0,1,1,1,0);
    shiftLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 0, 2, 1, 1, 0);
    shiftLayout->addWidget(lblCycleTime,0,3,1,1,0);
    shiftLayout->addWidget(timeCycleTime,0,4,1,1,0);
    shiftLayout->addWidget(lblShiftBegin,1,0,1,1,0);
    shiftLayout->addWidget(timeShiftBegin,1,1,1,1,0);
    shiftLayout->addWidget(lblShiftEnd,1,2,1,1,0);
    shiftLayout->addWidget(timeShiftEnd,1,3,1,1,0);
    shiftLayout->addItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed), 1, 4, 1, 1, 0);
    shiftLayout->addWidget(lblQuantity,1,5,1,1,0);
    shiftLayout->addWidget(txtQuantity,1,6,1,1,0);

    allowedTimeLayout->addWidget(lblSetupTime);
    allowedTimeLayout->addWidget(timeSetupTime);
    allowedTimeLayout->addWidget(lblBasicTime);
    allowedTimeLayout->addWidget(timeBasicTime);
    allowedTimeLayout->addWidget(lblRestTime);
    allowedTimeLayout->addWidget(timeRestTime);
    allowedTimeLayout->addWidget(lblAllowanceTime);
    allowedTimeLayout->addWidget(timeAllowanceTime);

    breakLayout->addWidget(lblShortBreaks,0,0,1,1,0);
    breakLayout->addWidget(conShortBreaks,0,1,1,1,0);
    breakLayout->addWidget(lblShortBreaksBegin,1,0,1,1,0);
    breakLayout->addWidget(timeBreakBegin,1,1,1,1,0);
    breakLayout->addWidget(lblShortBreaksEnd,1,2,1,1,0);
    breakLayout->addWidget(timeBreakEnd,1,3,1,1,0);
    breakLayout->addWidget(btnBreakAdd,1,4,1,1,0);
    breakLayout->addWidget(btnBreakRemove,1,5,1,1,0);

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

    setLayout(mainLayout);




}

void ShiftAndPauseData::backButtonClicked(){
    /*emit saveShiftAndPauseData();
    emit showMetadataView();*/
}
