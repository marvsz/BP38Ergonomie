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

    QWidget *topGroup = new QWidget;
    QVBoxLayout *topGroupLayout = new QVBoxLayout;
    QHBoxLayout *menuLineLayout = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *categoryLayout = new QVBoxLayout;
    QScrollArea *categoryScrollArea = new QScrollArea;


    type = new ValueControl(TEXT_CONTROL, categoryScrollArea);
    type->setValues(true, typeValues, typeValues,  new QString());
    type->setText(tr("loadhandling type:"));
    connect(type, SIGNAL(valueChanged(QString)), this, SLOT(typeChanged(QString)));


    last = new ValueControl(VALUE_CONTROL, categoryScrollArea);
    last->setUnit(tr("kg"));
    last->setValues(1, 100, lastValues, new QString());
    last->setText(tr("Last"));


    weg = new ValueControl(VALUE_CONTROL, categoryScrollArea);
    weg->setUnit(tr("m"));
    weg->setValues(0, 20, wegValues, new QString());
    weg->setText(tr("Weg"));


    hand = new ValueControl(TEXT_CONTROL, categoryScrollArea);
    hand->setValues(true, handValues, handValues, new QString());
    hand->setText(tr("Benutzte Hand:"));

    QVector<QString>* options = new QVector<QString>();
    options->append(tr("Bockrollen"));
    options->append(tr("Bremsen"));

    tools = new TransportationListControl(options, this);

    topGroupLayout->addWidget(type);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, topGroup));
    topGroupLayout->addWidget(last);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, topGroup));
    topGroupLayout->addWidget(weg);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, topGroup));
    topGroupLayout->addWidget(hand);
    topGroup->setLayout(topGroupLayout);

    categoryLayout->addWidget(topGroup);
    categoryLayout->addWidget(new Separator(Qt::Horizontal, 3, control));
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
    if(newType == tr("pulling and pushing"))
        last->setValues(1, 2000, heavyLastValues, new QString());
    else
        last->setValues(1, 100, lastValues, new QString());
}

TransportView::~TransportView()
{
}
