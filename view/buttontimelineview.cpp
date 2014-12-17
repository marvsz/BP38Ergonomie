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
   QHBoxLayout *resizeLayout = new QHBoxLayout;

   QScroller::grabGesture(scrollArea->viewport(), QScroller::LeftMouseButtonGesture);


   leftButtonLayout = new QHBoxLayout();
   rightButtonLayout = new QHBoxLayout();
   avButtonLayout = new QHBoxLayout();

   mainButtonLayout->addLayout(leftButtonLayout);
   mainButtonLayout->addLayout(rightButtonLayout);
   mainButtonLayout->addLayout(avButtonLayout);
   mainButtonLayout->setAlignment(leftButtonLayout, Qt::AlignLeft);
   mainButtonLayout->setAlignment(rightButtonLayout, Qt::AlignLeft);
   mainButtonLayout->setAlignment(avButtonLayout, Qt::AlignLeft);

   mainButton->setLayout(mainButtonLayout);
   scrollArea->setWidget(mainButton);

   scrollArea->setWidgetResizable(true);

   mainLayout->addWidget(scrollArea);
   mainLayout->addLayout(resizeLayout);

   btnPlus = new QPushButton("+");
   btnMinus = new QPushButton("-");
   btnPlus->setFixedSize(60, 60);
   btnMinus->setFixedSize(60,60);

   currentTime = 100;

   resizeLayout->addWidget(btnMinus);
   resizeLayout->addWidget(btnPlus);

   main->setLayout(mainLayout);

   this->setCentralWidget(main);

   connect(btnPlus, SIGNAL(clicked()), SLOT(btnPlusClicked()));
   connect(btnMinus, SIGNAL(clicked()), SLOT(btnMinusClicked()));
}

    void ButtonTimelineView::btnMinusClicked(){
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

    void ButtonTimelineView::btnPlusClicked(){
        btnMinus->setEnabled(true);
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
