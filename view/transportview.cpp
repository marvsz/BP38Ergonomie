#include "transportview.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QScroller>
#include "valuecontrol.h"
#include "seperator.h"


TransportView::TransportView(QString windowName, QWidget *parent) :
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

    QGroupBox *topGroup = new QGroupBox;
    QVBoxLayout *topGroupLayout = new QVBoxLayout;
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
    weg->setUnit("m");
    weg->setText("Weg");

    QVector<QString*>* handValues = new QVector<QString*>();
    (*handValues) << new QString("Links") << new QString("Beide") << new QString("Rechts");
    hand = new ValueControl(TEXT_CONTROL, categoryScrollArea);
    hand->setValues(handValues, new QString());
    hand->setText("Benutzte Hand:");

    QVector<QString>* options = new QVector<QString>();
    options->append("Bockrollen");
    options->append("Bremsen");

    tools = new ListControl("Transportmittel", options, this);

    topGroupLayout->addWidget(type);
    topGroupLayout->addWidget(new Seperator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(last);
    topGroupLayout->addWidget(new Seperator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(weg);
    topGroupLayout->addWidget(new Seperator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(hand);
    topGroup->setLayout(topGroupLayout);

    categoryLayout->addWidget(backButton);
    categoryLayout->addWidget(label);
    categoryLayout->addWidget(topGroup);
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

TransportView::~TransportView()
{
}

void TransportView::openMenuView(){
    emit menuViewSelected();
}
