#include "graphtimelineview.h"

#include <QScroller>
#include <QScrollBar>
#include <QColor>
#include <QTime>

/**
 * @brief constructs a new View in which the small graph for the three timelines is displayed
 * @param parent
 */
GraphTimelineView::GraphTimelineView(QWidget *parent) : QMainWindow(parent)
  , graph(new QLabel(""))
  , picture()
  , painter()
  , graphArea(new QScrollArea)
{
   QScroller::grabGesture(graphArea->viewport(), QScroller::LeftMouseButtonGesture);

   graphArea->setMinimumHeight(160);
   graphArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   graphArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   graphArea->setWidget(graph);

   setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   this->setMinimumHeight(160);
   this->setCentralWidget(graphArea);
}

void GraphTimelineView::leftStarted(const QTime &startTime){
    leftWPs->append(0);
    leftWPs->append(startTime);
}

void GraphTimelineView::leftEnded(const QTime &endTime){
    leftWPs->append(endTime);
}

void GraphTimelineView::rightStarted(const QTime &startTime){
    rightWPs->append(0);
    rightWPs->append(startTime);
}

void GraphTimelineView::rightEnded(const QTime &endTime){
    rightWPs->append(endTime);
}

void GraphTimelineView::basicStarted(const QTime &startTime){
    basicWPs->append(0);
    basicWPs->append(startTime);
}

void GraphTimelineView::basicEnded(const QTime &endTime){
    basicWPs->append(endTime);
}

void GraphTimelineView::initialize(QVector<QVariant> *leftWPs, QVector<QVariant> *rightWPs, QVector<QVariant> *basicWPs){
    this->leftWPs = new QVector<QVariant>(*leftWPs);
    this->rightWPs = new QVector<QVariant>(*rightWPs);
    this->basicWPs = new QVector<QVariant>(*basicWPs);
}

void GraphTimelineView::updateGraphTimeLine(const QTime &currentTime){
    painter.begin(&picture);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(255,255,255,0), 0, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(0, -70, 1, -70);
    painter.drawLine(0, 80, 1, 80);

    painter.setPen(QPen(QColor(142, 142, 147), 6, Qt::SolidLine, Qt::FlatCap));

    if(!basicWPs->empty()){
        QTime lastEnd = QTime(0,0);
        paintX = 0;
        for(int i = 0; i < leftWPs->count(); i = i +3){
            QTime curStart = leftWPs->at(i+1).toTime();
            int duration = 0;
            int freeSecs = lastEnd.secsTo(curStart);

            if(i+2 < leftWPs->count()){
               QTime curEnd = leftWPs->at(i+2).toTime();
               duration = curStart.secsTo(curEnd);
               painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::FlatCap));
               painter.drawLine(paintX + freeSecs*10, -50, paintX + freeSecs*10, -30);
               painter.drawLine(paintX + (freeSecs + duration)*10, -50, paintX + (freeSecs + duration)*10, -30);
               painter.setPen(QPen(QColor(142, 142, 147), 6, Qt::SolidLine, Qt::FlatCap));
               painter.drawLine(paintX + freeSecs*10, -40, paintX + (freeSecs + duration)*10, -40);
               lastEnd = curEnd;
            }
            else {
               duration = curStart.secsTo(currentTime);
               painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::FlatCap));
               painter.drawLine(paintX + freeSecs*10, -50, paintX + freeSecs*10, -30);
               painter.setPen(QPen(QColor(142, 142, 147), 6, Qt::SolidLine, Qt::FlatCap));
               painter.drawLine(paintX + freeSecs*10, -40, paintX + (freeSecs + duration)*10, -40);
            }
            paintX = paintX + (freeSecs + duration)*10;
        }

        lastEnd = QTime(0,0);
        paintX = 0;
        for(int i = 0; i < rightWPs->count(); i = i +3){
            QTime curStart = rightWPs->at(i+1).toTime();
            int duration = 0;
            int freeSecs = lastEnd.secsTo(curStart);

            if(i+2 < rightWPs->count()){
               QTime curEnd = rightWPs->at(i+2).toTime();
               duration = curStart.secsTo(curEnd);
               painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::FlatCap));
               painter.drawLine(paintX + freeSecs*10, -10, paintX + freeSecs*10, 10);
               painter.drawLine(paintX + (freeSecs + duration)*10, -10, paintX + (freeSecs + duration)*10, 10);
               painter.setPen(QPen(QColor(142, 142, 147), 6, Qt::SolidLine, Qt::FlatCap));
               painter.drawLine(paintX + freeSecs*10, 0, paintX + (freeSecs + duration)*10, 0);
               lastEnd = curEnd;
            }
            else {
               duration = curStart.secsTo(currentTime);
               painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::FlatCap));
               painter.drawLine(paintX + freeSecs*10, -10, paintX + freeSecs*10, 10);
               painter.setPen(QPen(QColor(142, 142, 147), 6, Qt::SolidLine, Qt::FlatCap));
               painter.drawLine(paintX + freeSecs*10, 0, paintX + (freeSecs + duration)*10, 0);
            }
            paintX = paintX + (freeSecs + duration)*10;
        }

        lastEnd = QTime(0,0);
        paintX = 0;
        for(int i = 0; i < basicWPs->count(); i = i +3){
            QTime curStart = basicWPs->at(i+1).toTime();
            int duration = 0;
            int freeSecs = lastEnd.secsTo(curStart);

            if(i+2 < basicWPs->count()){
               QTime curEnd = basicWPs->at(i+2).toTime();
               duration = curStart.secsTo(curEnd);
               painter.drawLine(paintX + freeSecs*10, 40, paintX + (freeSecs + duration)*10, 40);
               painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine, Qt::FlatCap));
               painter.drawLine(paintX + (freeSecs + duration)*10, 30, paintX + (freeSecs + duration)*10, 50);
               painter.setPen(QPen(QColor(142, 142, 147), 6, Qt::SolidLine, Qt::FlatCap));
               lastEnd = curEnd;
            }
            else {
               duration = curStart.secsTo(currentTime);
               painter.drawLine(paintX + freeSecs*10, 40, paintX + (freeSecs + duration)*10, 40);
            }
            paintX = paintX + (freeSecs + duration)*10;
        }

        lastEnd = QTime(0,0);
        paintX = 0;
        for(int i = 0; i < ((basicWPs->at(1).toTime().secsTo(currentTime)) + 5); ++i){
            painter.setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::FlatCap));
            if(i%5 == 0){
                painter.drawLine(paintX, 55, paintX, 65);
                unsigned int m = (i/ 60);
                unsigned int s = (i - 60*m);
                const QString diff = QString("%1:%2")
                .arg(m, 2, 10, QChar('0'))
                .arg(s, 2, 10, QChar('0'));
                QFont font=painter.font() ;
                font.setPointSize(7);
                painter.setFont(font);
                painter.drawText(QPoint(paintX -26, 78), diff);
            }
            else
                painter.drawLine(paintX, 58, paintX, 62);
            paintX = paintX +10;
        }


    }
    painter.end();

    graph->setPicture(picture);
    graph->repaint();
    graph->adjustSize();

    graphArea->horizontalScrollBar()->setValue(graphArea->horizontalScrollBar()->maximum());
}
