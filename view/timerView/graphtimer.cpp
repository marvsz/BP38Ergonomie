#include "graphtimer.h"
#include "flickcharm.h"
#include <QVBoxLayout>

GraphTimer::GraphTimer(QWidget *parent) :
    QWidget(parent),
    paintX(10),
    graphArea(new QWidget()),
    lblGraph(new QLabel("")),
    picture(),
    painter(),
    scrollAreaGraph(new QScrollArea),
{
    QVBoxLayout *mainLayout = QVBoxLayout;

    lblGraph->setFixedHeight(150);
    graphArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollAreaGraph->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollAreaGraph->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollAreaGraph->setWidget(graphArea);
    scrollAreaGraph->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(scrollAreaGraph);

    mainLayout->addWidget(graphArea);
    setLayout(mainLayout);
}

void GraphTimer::drawGraph(QList<int> ){

}

void GraphTimer::clear(){

}


