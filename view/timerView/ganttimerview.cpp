#include "ganttimerview.h"
#include "flickcharm.h"
#include <QVBoxLayout>
#include <QScrollArea>

const QStringList GantTimerView::typePrefix = QStringList()<<"L"<<"R"<<"AV";

GantTimerView::GantTimerView(QWidget *parent) : QWidget(parent),
    secPixel(100),
    numBxFrequenz(new NumberLineEdit()),
    btnZoomIn(new QPushButton()),
    btnZoomOut(new QPushButton()),
    btnFrequenzPlus(new QPushButton()),
    btnFrequenzMinus(new QPushButton()),
    leftWP(new QHBoxLayout),
    rightWP(new QHBoxLayout),
    basicWP(new QHBoxLayout),
    leftWPBtns(new QVector<WorkProcessButton*>()),
    rightWPBtns(new QVector<WorkProcessButton*>()),
    basicWPBtns(new QVector<WorkProcessButton*>())
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
    lastLineLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    lastLineLayout->addWidget(btnZoomIn);
    lastLineLayout->addWidget(btnZoomOut);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(scMain);
    mainLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    mainLayout->addLayout(lastLineLayout);

    setLayout(mainLayout);
}

GantTimerView::~GantTimerView()
{

}

//PUBLIC SLOTS
void GantTimerView::add(int id, int type, const QTime &start, const QTime &end){
    QHBoxLayout *layout = getLayout(type);
    QVector<WorkProcessButton*> *btnVector = getButtonVector(type);
    WorkProcessButton* lastBtn = btnVector->last();
    WorkProcessButton* curBtn = new WorkProcessButton(id, type, start, end, this);
    curBtn->setFixedSize(start.secsTo(end) * secPixel, 50);
    connect(curBtn, SIGNAL(clickedWithIDValue(int,int)), this, SIGNAL(workProcessSelected(int,int)));
    int freeSecs = lastBtn->getEndTime().secsTo(start);
    layout->addSpacerItem(new QSpacerItem(freeSecs * secPixel, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
    layout->addWidget(curBtn);
}

void GantTimerView::clear(){
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

void GantTimerView::setSelectedWorkProcess(int id, int type, int frequenz){
    QVector<WorkProcessButton*> *btnVector = getButtonVector(type);
    for(int i = 0; i < btnVector->count(); ++i){
        WorkProcessButton *btn = btnVector->at(i);
        if(btn->getID() == id)
            btn->setSelected(true);
        else
            btn->setSelected(false);
    }
    numBxFrequenz->setValue(frequenz);
}


//PRIVATE SLOTS
void GantTimerView::btnZoomInClicked(){
    secPixel += 10;
    clear();
    for(int i = 0; i < leftWPBtns->count(); ++i){
        WorkProcessButton *btn = leftWPBtns->at(i);
        add(btn->getID(), btn->getValue().toInt(), btn->getStartTime(), btn->getEndTime());
    }
    for(int i = 0; i < rightWPBtns->count(); ++i){
        WorkProcessButton *btn = rightWPBtns->at(i);
        add(btn->getID(), btn->getValue().toInt(), btn->getStartTime(), btn->getEndTime());
    }
    for(int i = 0; i < basicWPBtns->count(); ++i){
        WorkProcessButton *btn = basicWPBtns->at(i);
        add(btn->getID(), btn->getValue().toInt(), btn->getStartTime(), btn->getEndTime());
    }
}

void GantTimerView::btnZoomOutClicked(){
    secPixel -= 10;
    clear();
    for(int i = 0; i < leftWPBtns->count(); ++i){
        WorkProcessButton *btn = leftWPBtns->at(i);
        add(btn->getID(), btn->getValue().toInt(), btn->getStartTime(), btn->getEndTime());
    }
    for(int i = 0; i < rightWPBtns->count(); ++i){
        WorkProcessButton *btn = rightWPBtns->at(i);
        add(btn->getID(), btn->getValue().toInt(), btn->getStartTime(), btn->getEndTime());
    }
    for(int i = 0; i < basicWPBtns->count(); ++i){
        WorkProcessButton *btn = basicWPBtns->at(i);
        add(btn->getID(), btn->getValue().toInt(), btn->getStartTime(), btn->getEndTime());
    }
}

void GantTimerView::btnPlus(){
    numBxFrequenz->setValue(numBxFrequenz->getValue() + 1);
}

void GantTimerView::btnMinus(){
    numBxFrequenz->setValue(numBxFrequenz->getValue() - 1);
}



//PRIVATE METHODS
QHBoxLayout* GantTimerView::getLayout(int type){
    switch(type){
        case 1: return leftWP; break;
        case 2: return rightWP; break;
        case 3: return basicWP; break;
        default: return basicWP; break;
    }
}

QVector<WorkProcessButton*>* GantTimerView::getButtonVector(int type){
    switch(type){
        case 1: return leftWPBtns; break;
        case 2: return rightWPBtns; break;
        case 3: return basicWPBtns; break;
        default: return basicWPBtns; break;
    }
}

void GantTimerView::resizeClear(){
    clear();
    leftWPBtns->clear();
    rightWPBtns->clear();
    basicWPBtns->clear();
}


