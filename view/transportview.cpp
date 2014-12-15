#include "transportview.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QScroller>
#include "valuecontrol.h"
#include "separator.h"
#include "flickcharm.h"
#include <QDebug>

/**
 * @brief Constructs a new Transportview
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
TransportView::TransportView(QWidget *parent) :
    QMainWindow(parent)
{

    main = new QWidget(this);
    control = new QWidget(this);

    QGroupBox *topGroup = new QGroupBox;
    QVBoxLayout *topGroupLayout = new QVBoxLayout;
    QHBoxLayout *menuLineLayout = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *categoryLayout = new QVBoxLayout;
    QScrollArea *categoryScrollArea = new QScrollArea;

    QVector<QString*>* typeValues = new QVector<QString*>();
    (*typeValues) << new QString("Halten") << new QString("Umsetzen") << new QString("Tragen") << new QString("Ziehen und Schieben");
    type = new ValueControl(TEXT_CONTROL, categoryScrollArea);
    type->setValues(typeValues, typeValues,  new QString());
    type->setText("Lastenhandhabungsart:");
    connect(type, SIGNAL(valueChanged(QString)), this, SLOT(typeChanged(QString)));

    lastValues = new QVector<int>;
    (*lastValues)<<2<<3<<5<<10<<20;
    heavyLastValues = new QVector<int>;
    (*heavyLastValues)<<100<<500<<1000<<1500<<2000;
    last = new ValueControl(VALUE_CONTROL, categoryScrollArea);
    last->setUnit("kg");
    last->setValues(1, 100, lastValues, new QString());
    last->setText("Last");

    QVector<int>* wegValues = new QVector<int>;
    (*wegValues)<<2<<3<<5<<10<<20;
    weg = new ValueControl(VALUE_CONTROL, categoryScrollArea);
    weg->setUnit("m");
    weg->setValues(0, 20, wegValues, new QString());
    weg->setText("Weg");

    QVector<QString*>* handValues = new QVector<QString*>();
    (*handValues) << new QString("Links") << new QString("Beide") << new QString("Rechts");
    hand = new ValueControl(TEXT_CONTROL, categoryScrollArea);
    hand->setValues(handValues, handValues, new QString());
    hand->setText("Benutzte Hand:");

    QVector<QString>* options = new QVector<QString>();
    options->append("Bockrollen");
    options->append("Bremsen");

    tools = new TransportationListControl("Transportmittel", options, this);

    topGroupLayout->addWidget(type);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(last);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(weg);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(hand);
    topGroup->setLayout(topGroupLayout);

    categoryLayout->addWidget(topGroup);
    categoryLayout->addWidget(tools);
    control->setLayout(categoryLayout);

    categoryScrollArea->setWidget(control);
    categoryScrollArea->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(categoryScrollArea);

    mainLayout->addLayout(menuLineLayout);
    mainLayout->addWidget(categoryScrollArea);

    main->setLayout(mainLayout);
    this->setCentralWidget(main);
}

void TransportView::typeChanged(QString newType){
    qDebug() << newType;
    if(newType == "Ziehen und Schieben")
        last->setValues(1, 2000, heavyLastValues, new QString());
    else
        last->setValues(1, 100, lastValues, new QString());
}

TransportView::~TransportView()
{
}
