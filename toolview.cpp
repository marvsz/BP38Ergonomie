#include "toolview.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QScroller>
#include "textcon.h"

ToolView::ToolView(QString windowName, QWidget *parent) :
    QMainWindow(parent)
{

    main = new QWidget(this);
    control = new QWidget(this);
    lblViewName = new QLabel("Lastenhandhabung");

    backButton = new QPushButton(this);
    backButton->setText("< Zurück");
    backButton->setFixedSize(120, 45);
    connect(backButton, SIGNAL(clicked()), this, SLOT(openMenuView()));

    label = new QLabel(this);
    label->setText(windowName);

    QHBoxLayout *menuLineLayout = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *categoryLayout = new QVBoxLayout;
    QScrollArea *categoryScrollArea = new QScrollArea;


    type = new TextCon(4, new QString[4]{"Halten", "Umsetzen", "Tragen", "Ziehen und Schieben"}, categoryScrollArea);
    type->setText("Lastenhandhabungsart:");
    QVector<int>* lastValues = new QVector<int>;
    (*lastValues)<<2<<3<<5<<10<<20;
    last = new OwnCon();
    last->setValues(1, 100, lastValues, new QString());
    last->setText("Last [kg]:");
    QVector<int>* wegValues = new QVector<int>;
    (*wegValues)<<2<<3<<5<<10<<20;
    weg = new OwnCon(categoryScrollArea);
    weg->setValues(0, 20, wegValues, new QString());
    weg->setText("Weg [m]:");
    hand = new TextCon(3, new QString[3]{"Beide", "Links", "Rechts"}, categoryScrollArea);
    hand->setText("Benutzte Hand:");
    tools = new ListCon("Hilfsmittel", "Bockrollen", "Bremsen", this);

    categoryLayout->addWidget(backButton);
    categoryLayout->addWidget(label);
    categoryLayout->addWidget(type);
    categoryLayout->addWidget(last);
    categoryLayout->addWidget(weg);
    categoryLayout->addWidget(hand);
    categoryLayout->addWidget(tools);
    control->setLayout(categoryLayout);

    categoryScrollArea->setWidget(control);
    categoryScrollArea->setWidgetResizable(true);
    QScroller::grabGesture(categoryScrollArea->viewport(), QScroller::LeftMouseButtonGesture);

    menuLineLayout->addWidget(backButton);
    menuLineLayout->addWidget(lblViewName,0,Qt::AlignCenter);

    mainLayout->addLayout(menuLineLayout);
    mainLayout->addWidget(categoryScrollArea);

    main->setLayout(mainLayout);
    this->setCentralWidget(main);
}

ToolView::~ToolView()
{
}

void ToolView::openMenuView(){
    emit menuViewSelected();
}
