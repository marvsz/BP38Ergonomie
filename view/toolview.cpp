#include "toolview.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QScroller>
#include "valuecontrol.h"

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


    QVector<QString*>* typeValues = new QVector<QString*>();
    (*typeValues) << new QString("Halten") << new QString("Umsetzen") << new QString("Tragen") << new QString("Ziehen und Schieben");
    type = new ValueControl(TEXT_CONTROL, categoryScrollArea);
    type->setValues(typeValues, new QString());
    type->setText("Lastenhandhabungsart:");

    QVector<int>* lastValues = new QVector<int>;
    (*lastValues)<<2<<3<<5<<10<<20;
    last = new ValueControl(VALUE_CONTROL, categoryScrollArea);
    last->setUnit("kg");
    last->setValues(1, 100, lastValues, new QString());
    last->setText("Last");

    QVector<int>* wegValues = new QVector<int>;
    (*wegValues)<<2<<3<<5<<10<<20;
    weg = new ValueControl(VALUE_CONTROL, categoryScrollArea);
    weg->setValues(0, 20, wegValues, new QString());
    weg->setText("Weg");
    weg->setUnit("m");

    QVector<QString*>* handValues = new QVector<QString*>();
    (*handValues) << new QString("Links") << new QString("Beide") << new QString("Rechts");
    hand = new ValueControl(TEXT_CONTROL, categoryScrollArea);
    hand->setValues(handValues, new QString());
    hand->setText("Benutzte Hand:");

    QVector<QString>* options = new QVector<QString>();
    options->append("Bockrollen");
    options->append("Bremsen");
    tools = new ListCon("Hilfsmittel", options, this);

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
