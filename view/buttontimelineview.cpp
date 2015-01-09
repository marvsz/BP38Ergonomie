#include "buttontimelineview.h"
#include <QScrollArea>
#include <QScroller>

ButtonTimelineView::ButtonTimelineView(QWidget *parent) :
    QMainWindow(parent)
{

   main = new QWidget();
   mainButton = new QWidget();

   QVBoxLayout *mainLayout = new QVBoxLayout;
   QVBoxLayout *mainButtonLayout = new QVBoxLayout;
   QScrollArea *scrollArea = new QScrollArea;
   QVBoxLayout *occurrenceLayoutV = new QVBoxLayout;
   QHBoxLayout *occurrenceLayoutH = new QHBoxLayout;
   QHBoxLayout *resizeLayout = new QHBoxLayout;

   QScroller::grabGesture(scrollArea->viewport(), QScroller::LeftMouseButtonGesture);

   lblOccurrences = new QLabel(tr("frequenzy:"));
   occurrences = new QLineEdit("0");
   occurrences->setFixedSize(80,60);
   occurrences->setAlignment(Qt::AlignCenter);
   btnPlus = new QPushButton("+");
   btnMinus = new QPushButton("-");
   btnPlus->setFixedSize(60,60);
   btnMinus->setFixedSize(60,60);
   btnZoomIn = new QPushButton();
   btnZoomOut = new QPushButton();
   btnZoomIn->setFixedSize(60,60);
   btnZoomOut->setFixedSize(60,60);

   btnZoomIn->setIcon(QIcon(":/timer/icons/Timer/zoomIn.png"));
   btnZoomIn->setObjectName("btnTimer");
   btnZoomIn->setIconSize(QSize(45,45));
   btnZoomOut->setIcon(QIcon(":/timer/icons/Timer/zoomOut.png"));
   btnZoomOut->setObjectName("btnTimer");
   btnZoomOut->setIconSize(QSize(45,45));

   leftButtonLayout = new QHBoxLayout();
   rightButtonLayout = new QHBoxLayout();
   avButtonLayout = new QHBoxLayout();

   mainButtonLayout->addLayout(leftButtonLayout);
   mainButtonLayout->addLayout(rightButtonLayout);
   mainButtonLayout->addLayout(avButtonLayout);
   mainButtonLayout->setAlignment(leftButtonLayout, Qt::AlignLeft);
   mainButtonLayout->setAlignment(rightButtonLayout, Qt::AlignLeft);
   mainButtonLayout->setAlignment(avButtonLayout, Qt::AlignLeft);

   occurrenceLayoutH->addWidget(btnMinus);
   occurrenceLayoutH->addWidget(occurrences);
   occurrenceLayoutH->addWidget(btnPlus);
   occurrenceLayoutV->addWidget(lblOccurrences);
   occurrenceLayoutV->addLayout(occurrenceLayoutH);
   occurrenceLayoutV->setAlignment(lblOccurrences, Qt::AlignCenter);

   resizeLayout->addLayout(occurrenceLayoutV);
   resizeLayout->addWidget(btnZoomOut);
   resizeLayout->addWidget(btnZoomIn);
   resizeLayout->setAlignment(occurrenceLayoutV, Qt::AlignLeft);

   mainButton->setLayout(mainButtonLayout);
   scrollArea->setWidget(mainButton);

   scrollArea->setWidgetResizable(true);

   mainLayout->addWidget(scrollArea);
   mainLayout->addLayout(resizeLayout);

   currentTime = 100;

   main->setLayout(mainLayout);

   this->setCentralWidget(main);

   connect(btnPlus, SIGNAL(clicked()), SLOT(btnPlusClicked()));
   connect(btnMinus, SIGNAL(clicked()), SLOT(btnMinusClicked()));
   connect(btnZoomIn, SIGNAL(clicked()), SLOT(btnZoomInClicked()));
   connect(btnZoomOut, SIGNAL(clicked()), SLOT(btnZoomOutClicked()));
}

    void ButtonTimelineView::btnMinusClicked(){
        if(count > 0){
            count--;
            const QString str = QString("%1").arg(count);
            occurrences->setText(str);
        }
    }

    void ButtonTimelineView::btnPlusClicked(){
        count++;
        const QString str = QString("%1").arg(count);
        occurrences->setText(str);
    }

    void ButtonTimelineView::btnZoomOutClicked(){
        if(currentTime -20 > 0){
            int timeFactor = currentTime;
            currentTime = currentTime -20;
            for(int i = 0; i < leftButtonLayout->count(); ++i){
                if(leftButtonLayout->itemAt(i)->widget() != 0){
                    int oldW = leftButtonLayout->itemAt(i)->widget()->width();
                    leftButtonLayout->itemAt(i)->widget()->setFixedWidth(oldW - (oldW/timeFactor)*20);
                }
                else
                    leftButtonLayout->itemAt(i)->spacerItem()->changeSize(currentTime, 60);
            }
            for(int i = 0; i < rightButtonLayout->count(); ++i){
                if(rightButtonLayout->itemAt(i)->widget() != 0){
                    int oldW = rightButtonLayout->itemAt(i)->widget()->width();
                    rightButtonLayout->itemAt(i)->widget()->setFixedWidth(oldW - (oldW/timeFactor)*20);
                }
                else
                    rightButtonLayout->itemAt(i)->spacerItem()->changeSize(currentTime, 60);
            }
            for(int i = 0; i < avButtonLayout->count(); ++i){
                if(avButtonLayout->itemAt(i)->widget() != 0){
                    int oldW = avButtonLayout->itemAt(i)->widget()->width();
                    avButtonLayout->itemAt(i)->widget()->setFixedWidth(oldW - (oldW/timeFactor)*20);
                }
                else
                    avButtonLayout->itemAt(i)->spacerItem()->changeSize(currentTime, 60);
            }
       }
        else
            btnMinus->setEnabled(false);
    }


    void ButtonTimelineView::btnZoomInClicked(){
        btnZoomIn->setEnabled(true);
        int timeFactor = currentTime;
        currentTime = currentTime +20;
        for(int i = 0; i < leftButtonLayout->count(); ++i){
             if(leftButtonLayout->itemAt(i)->widget() != 0){
                int oldW = leftButtonLayout->itemAt(i)->widget()->width();
                leftButtonLayout->itemAt(i)->widget()->setFixedWidth(oldW + (oldW/timeFactor)*20);
             }
             else
                leftButtonLayout->itemAt(i)->spacerItem()->changeSize(currentTime, 60);
        }
        for(int i = 0; i < rightButtonLayout->count(); ++i){
             if(rightButtonLayout->itemAt(i)->widget() != 0){
                int oldW = rightButtonLayout->itemAt(i)->widget()->width();
                rightButtonLayout->itemAt(i)->widget()->setFixedWidth(oldW + (oldW/timeFactor)*20);
             }
             else
                rightButtonLayout->itemAt(i)->spacerItem()->changeSize(currentTime, 60);
        }
        for(int i = 0; i < avButtonLayout->count(); ++i){
             if(avButtonLayout->itemAt(i)->widget() != 0){
                int oldW = avButtonLayout->itemAt(i)->widget()->width();
                avButtonLayout->itemAt(i)->widget()->setFixedWidth(oldW + (oldW/timeFactor)*20);
             }
             else
                avButtonLayout->itemAt(i)->spacerItem()->changeSize(currentTime, 60);
        }
    }

    void ButtonTimelineView::clearButtons(){
        QLayoutItem *item;
        while((item = leftButtonLayout->takeAt(0)) != NULL){
            delete item->widget();
            delete item;
        }
        while((item = rightButtonLayout->takeAt(0)) != NULL){
            delete item->widget();
            delete item;
        }
        while((item = avButtonLayout->takeAt(0)) != NULL){
            delete item->widget();
            delete item;
        }

    }
