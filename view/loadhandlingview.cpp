#include "loadhandlingview.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include "valuecontrol.h"
#include "separator.h"
#include "flickcharm.h"

/**
 * @brief Constructs a new Transportview
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
LoadHandlingView::LoadHandlingView(QWidget *parent) :
    QWidget(parent)
{

    main = new QWidget(this);
    control = new QWidget(this);

    QVBoxLayout *topGroupLayout = new QVBoxLayout;
    QHBoxLayout *menuLineLayout = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QScrollArea *categoryScrollArea = new QScrollArea;


    type = new ValueControl(TEXT, categoryScrollArea);
    type->setValues(true, typeValues, typeValues, QString());
    type->setText(tr("loadhandling type:"));
    connect(type, SIGNAL(valueChanged(QString)), this, SLOT(typeChanged(QString)));


    last = new ValueControl(VALUE, categoryScrollArea);
    last->setUnit(tr("kg"));
    last->setValues(1, 100, lastValues, QString());
    last->setText(tr("Last"));


    weg = new ValueControl(VALUE, categoryScrollArea);
    weg->setUnit(tr("m"));
    weg->setValues(0, 20, wegValues, QString());
    weg->setText(tr("Weg"));



    QVector<QString>* options = new QVector<QString>();
    options->append(tr("Bockrollen"));
    options->append(tr("Bremsen"));

    topGroupLayout->addWidget(type);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(last);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(weg);


    control->setLayout(topGroupLayout);

    categoryScrollArea->setWidget(control);
    categoryScrollArea->setWidgetResizable(true);
    FlickCharm *flickCharm = new FlickCharm(this);
    flickCharm->activateOn(categoryScrollArea);

    mainLayout->addLayout(menuLineLayout);
    mainLayout->addWidget(categoryScrollArea);

    main->setLayout(mainLayout);
    QVBoxLayout *contentLayout = new QVBoxLayout;
    contentLayout->addWidget(main);
    this->setLayout(contentLayout);
}

void LoadHandlingView::typeChanged(QString newType){
    if(newType == tr("pulling and pushing"))
        last->setValues(1, 2000, heavyLastValues, QString());
    else
        last->setValues(1, 100, lastValues, QString());
}

LoadHandlingView::~LoadHandlingView()
{
}
