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

   resizeLayout->addWidget(btnMinus);
   resizeLayout->addWidget(btnPlus);

   main->setLayout(mainLayout);

   this->setCentralWidget(main);

   connect(btnPlus, SIGNAL(clicked()), SLOT(btnPlusClicked()));
   connect(btnMinus, SIGNAL(clicked()), SLOT(btnMinusClicked()));
}

    void ButtonTimelineView::btnMinusClicked(){

    }

    void ButtonTimelineView::btnPlusClicked(){

    }
