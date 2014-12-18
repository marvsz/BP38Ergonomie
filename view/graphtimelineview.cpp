#include "graphtimelineview.h"

#include <QScroller>
#include <QScrollBar>

/**
 * @brief constructs a new View in which the small graph for the three timelines is displayed
 * @param parent
 */
GraphTimelineView::GraphTimelineView(QWidget *parent) : QMainWindow(parent)
  , graph(new QLabel(""))
  , picture()
  , painter()
  , graphArea(new QScrollArea)
  , paintX(10)
{
   QScroller::grabGesture(graphArea->viewport(), QScroller::LeftMouseButtonGesture);


   graphArea->setMaximumHeight(160);
   graphArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   graphArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   graphArea->setWidget(graph);

   graph->setFixedHeight(150);

   this->setCentralWidget(graphArea);
}

/**
 * @brief renders the graph
 * @param lstAV, list of the AVs: an end of an AV is signaled by "true"
 * @param lstLeftAVs, list of the left AVs: "false" at position i means no left AV at position i
 * @param lstRightAVs, list of the right AVs: "false" at position i means no right AV at position i
 */
void GraphTimelineView::updateGraph(QList<bool> *lstAV, QList<bool> *lstLeftAVs, QList<bool> *lstRightAVs){
    painter.begin(&picture);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::gray, 0, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(0, -40, 0, -40);

    paintX = 10;
    for(int i = 0; i < lstLeftAVs->count(); ++i){
        bool s = lstLeftAVs->at(i);
        painter.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap));
        if(s == true)
            painter.drawLine(paintX -10, -40, paintX, -40);
        paintX = paintX +10;

    }

    paintX = 10;
    for(int i = 0; i < lstRightAVs->count(); ++i){
        bool s = lstRightAVs->at(i);
        painter.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap));
        if(s == true)
            painter.drawLine(paintX -10, 0, paintX, 0);
        paintX = paintX +10;
    }

    paintX = 10;
    if(lstAV->empty()== false){
        for(int i = 0; i < (lstAV->count() + 5); ++i){
            painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
            if(i%5 == 0){
                painter.drawLine(paintX -10, 55, paintX -10, 65);
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
                painter.drawLine(paintX -10, 58, paintX -10, 62);
            paintX = paintX +10;
        }
    }

    paintX = 10;
    for(int i = 0; i < lstAV->count(); ++i){
        bool s = lstAV->at(i);

        painter.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap));
        if(s == true){
            painter.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap));
            painter.drawLine(paintX -10, 30, paintX -10, 50);
            painter.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap));
            painter.drawLine(paintX - 10, 40, paintX, 40);
        }
        else
            painter.drawLine(paintX - 10, 40, paintX, 40);
        paintX = paintX +10;
    }


    painter.end();

    graph->setPicture(picture);
    graph->repaint();
    graph->adjustSize();

    graphArea->horizontalScrollBar()->setValue(graphArea->horizontalScrollBar()->maximum());
}
