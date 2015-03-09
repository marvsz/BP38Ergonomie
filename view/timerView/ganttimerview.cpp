#include "ganttimerview.h"
#include "../flickcharm.h"
#include <QVBoxLayout>
#include <QScrollArea>

GantTimerView::GantTimerView(QWidget *parent) :
    TitledWidget(tr("Gant diagram"), parent),
    secPixel(100),
    selWP_ID(0),
    selWP_Type(AVType::BASIC),
    numBxFrequenz(new NumberLineEdit()),
    btnZoomIn(new QPushButton()),
    btnZoomOut(new QPushButton()),
    btnFrequenzPlus(new QPushButton()),
    btnFrequenzMinus(new QPushButton()),
    leftWP(new QHBoxLayout),
    rightWP(new QHBoxLayout),
    basicWP(new QHBoxLayout),
    leftWorkProcesses(new QVector<QVariant>()),
    rightWorkProcesses(new QVector<QVariant>()),
    basicWorkProcesses(new QVector<QVariant>())
{
    btnZoomIn->setFixedSize(45, 45);
    btnZoomIn->setObjectName("zoomInIcon");

    btnZoomOut->setFixedSize(45, 45);
    btnZoomOut->setObjectName("zoomOutIcon");

    btnFrequenzPlus->setFixedSize(45, 45);
    btnFrequenzPlus->setObjectName("plusIcon");

    btnFrequenzMinus->setFixedSize(45, 45);
    btnFrequenzMinus->setObjectName("minusIcon");

    connect(btnZoomIn, SIGNAL(clicked()), this, SLOT(btnZoomInClicked()));
    connect(btnZoomOut, SIGNAL(clicked()), this, SLOT(btnZoomOutClicked()));
    connect(btnFrequenzMinus, SIGNAL(clicked()), this, SLOT(btnMinus()));
    connect(btnFrequenzPlus, SIGNAL(clicked()), this, SLOT(btnPlus()));

    numBxFrequenz->setEnabled(false);
    numBxFrequenz->setMaximumWidth(100);
    numBxFrequenz->setFixedHeight(45);
    numBxFrequenz->setValue(1);

    QVBoxLayout *mainContentLayout = new QVBoxLayout;
    mainContentLayout->addLayout(leftWP);
    mainContentLayout->addLayout(rightWP);
    mainContentLayout->addLayout(basicWP);

    QWidget *mainWidget = new QWidget(this);
    QScrollArea *scMain = new QScrollArea(this);
    scMain->setWidgetResizable(true);

    FlickCharm *flickCharm = new FlickCharm(scMain);
    flickCharm->activateOn(scMain);

    mainWidget->setLayout(mainContentLayout);
    scMain->setWidget(mainWidget);

    QHBoxLayout *lastLineLayout = new QHBoxLayout;
    lastLineLayout->addWidget(btnFrequenzMinus, 0, Qt::AlignCenter);
    lastLineLayout->addWidget(numBxFrequenz, 0, Qt::AlignCenter);
    lastLineLayout->addWidget(btnFrequenzPlus, 0, Qt::AlignCenter);
    lastLineLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Fixed));
    lastLineLayout->addWidget(btnZoomIn);
    lastLineLayout->addWidget(btnZoomOut);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(scMain);
    mainLayout->addLayout(lastLineLayout);

    setLayout(mainLayout);
}

GantTimerView::~GantTimerView()
{

}

//PUBLIC SLOTS
void GantTimerView::initiliazeWorkProcesses(QList<QHash<QString, QVariant> > values){
    leftWorkProcesses = new QVector<QVariant>();
    rightWorkProcesses = new QVector<QVariant>();
    basicWorkProcesses = new QVector<QVariant>();
    for(int i = 0; i < values.count(); ++i){
        QHash<QString, QVariant> row = values.at(i);
        AVType type = (AVType) row.value(DBConstants::COL_WORK_PROCESS_TYPE).toInt();
        int id = row.value(DBConstants::COL_WORK_PROCESS_ID).toInt();
        QTime start = row.value(DBConstants::COL_WORK_PROCESS_BEGIN).toTime();
        QTime end = row.value(DBConstants::COL_WORK_PROCESS_END).toTime();
        switch(type){
        case AVType::LEFT: leftWorkProcesses->append(id);leftWorkProcesses->append(start);leftWorkProcesses->append(end);break;
        case AVType::RIGHT: rightWorkProcesses->append(id);rightWorkProcesses->append(start);rightWorkProcesses->append(end);break;
        case AVType::BASIC: basicWorkProcesses->append(id);basicWorkProcesses->append(start);basicWorkProcesses->append(end);break;
        }
    }
    update();
}

void GantTimerView::addWorkProcess(QHash<QString, QVariant> values){
    AVType type = (AVType) values.value(DBConstants::COL_WORK_PROCESS_TYPE).toInt();
    int id = values.value(DBConstants::COL_WORK_PROCESS_ID).toInt();
    QTime start = values.value(DBConstants::COL_WORK_PROCESS_BEGIN).toTime();
    QTime end = values.value(DBConstants::COL_WORK_PROCESS_END).toTime();
    switch(type){
    case AVType::LEFT: leftWorkProcesses->append(id);leftWorkProcesses->append(start);leftWorkProcesses->append(end);break;
    case AVType::RIGHT: rightWorkProcesses->append(id);rightWorkProcesses->append(start);rightWorkProcesses->append(end);break;
    case AVType::BASIC: basicWorkProcesses->append(id);basicWorkProcesses->append(start);basicWorkProcesses->append(end);break;
    }
    update();
}

void GantTimerView::setSelectedWorkProcess(QHash<QString, QVariant> values){
    selWP_ID = values.value(DBConstants::COL_WORK_PROCESS_ID).toInt();
    selWP_Type = (AVType) values.value(DBConstants::COL_WORK_PROCESS_TYPE).toInt();
    numBxFrequenz->setValue(values.value(DBConstants::COL_WORK_PROCESS_FREQUENCY).toInt());
    update();
}

void GantTimerView::resetWorkProcesses(){
    leftWorkProcesses->clear();
    rightWorkProcesses->clear();
    basicWorkProcesses->clear();
    resizeClear();
}

void GantTimerView::onEnter(){
    update();
    emit entered();
}

void GantTimerView::onLeaving(){
    emit saveWorkProcessFrequence(numBxFrequenz->getValue());
    emit left();
}

//PRIVATE SLOTS
void GantTimerView::btnZoomInClicked(){
    secPixel += 10;
    update();
}

void GantTimerView::btnZoomOutClicked(){
    if(secPixel > 10){
        secPixel -= 10;
        update();
    }
}

void GantTimerView::btnPlus(){
    numBxFrequenz->setValue(numBxFrequenz->getValue() + 1);
}

void GantTimerView::btnMinus(){
    if(numBxFrequenz->getValue() > 1)
        numBxFrequenz->setValue(numBxFrequenz->getValue() - 1);
}

void GantTimerView::btnWPLeftClicked(int id){
    workProcessClicked(id, AVType::LEFT);
}

void GantTimerView::btnWPRightClicked(int id){
    workProcessClicked(id, AVType::RIGHT);
}

void GantTimerView::btnWPBasicClicked(int id){
    workProcessClicked(id, AVType::BASIC);
}


//PRIVATE METHODS
void GantTimerView::workProcessClicked(int id, AVType type){
    emit saveWorkProcessFrequence(numBxFrequenz->getValue());
    emit selectWorkProcess(id, type);
    emit showView(ViewType::BODY_POSTURE_VIEW);
}

QHBoxLayout* GantTimerView::getLayout(int type){
    switch(type){
        case 1: return leftWP; break;
        case 2: return rightWP; break;
        case 3: return basicWP; break;
        default: return basicWP; break;
    }
}

void GantTimerView::resizeClear(){
    QLayoutItem *item;
    while((item = leftWP->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
    while((item = rightWP->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
    while((item = basicWP->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
}

void GantTimerView::update(){
    resizeClear();
    QTime lastEnd = QTime(0,0);
    for(int i = 0; i < leftWorkProcesses->count(); i = i + 3){
        int id = leftWorkProcesses->at(i).toInt();
        QTime curStart = leftWorkProcesses->at(i+1).toTime();
        QTime curEnd = leftWorkProcesses->at(i+2).toTime();
        WorkProcessButton *btn = new WorkProcessButton(id, id, curStart, curEnd, this);
        btn->setFixedSize(curStart.secsTo(curEnd) * secPixel, 50);
        btn->setText(QString("L %1: %2s").arg(id).arg(curStart.secsTo(curEnd)));
        if(selWP_ID == id && selWP_Type == 1)
            btn->setSelected(true);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(btnWPLeftClicked(int)));
        int freeSecs = lastEnd.secsTo(curStart);
        leftWP->addSpacerItem(new QSpacerItem(freeSecs * secPixel, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
        leftWP->addWidget(btn);
        lastEnd = curEnd;
    }
    leftWP->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    lastEnd = QTime(0,0);
    for(int i = 0; i < rightWorkProcesses->count(); i = i + 3){
        int id = rightWorkProcesses->at(i).toInt();
        QTime curStart = rightWorkProcesses->at(i+1).toTime();
        QTime curEnd = rightWorkProcesses->at(i+2).toTime();
        WorkProcessButton *btn = new WorkProcessButton(id, id, curStart, curEnd, this);
        btn->setFixedSize(curStart.secsTo(curEnd) * secPixel, 50);
        btn->setText(QString("R %1: %2s").arg(id).arg(curStart.secsTo(curEnd)));
        if(selWP_ID == id && selWP_Type == 2)
            btn->setSelected(true);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(btnWPRightClicked(int)));
        int freeSecs = lastEnd.secsTo(curStart);
        rightWP->addSpacerItem(new QSpacerItem(freeSecs * secPixel, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
        rightWP->addWidget(btn);
        lastEnd = curEnd;
    }
    rightWP->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    for(int i = 0; i < basicWorkProcesses->count(); i = i + 3){
        int id = basicWorkProcesses->at(i).toInt();
        QTime curStart = basicWorkProcesses->at(i+1).toTime();
        QTime curEnd = basicWorkProcesses->at(i+2).toTime();
        WorkProcessButton *btn = new WorkProcessButton(id, id, curStart, curEnd, this);
        btn->setText(QString("AV %1: %2s").arg(id).arg(curStart.secsTo(curEnd)));
        btn->setFixedSize(curStart.secsTo(curEnd) * secPixel, 50);
        if(selWP_ID == id && selWP_Type == 3)
            btn->setSelected(true);
        connect(btn, SIGNAL(clickedWithID(int)), this, SLOT(btnWPBasicClicked(int)));
        basicWP->addWidget(btn);
    }
    basicWP->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

}


