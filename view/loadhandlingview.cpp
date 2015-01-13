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

    vlcGraspType = new ValueControl(TEXT,categoryScrollArea);
    vlcGraspType->setValues(false, graspValues,graspValues,QString(tr("GraspTypeIcons")));
    vlcGraspType->setText(tr("Grasptype:"));

    vlcHandlingType = new ValueControl(TEXT, categoryScrollArea);
    vlcHandlingType->setValues(true,HandlingTypeValues, HandlingTypeValues,QString());
    vlcHandlingType->setText(tr("loadhandling type:"));
    connect(vlcHandlingType, SIGNAL(valueChanged(QString)), this, SLOT(typeChanged(QString)));


    vlcWeight = new ValueControl(VALUE, categoryScrollArea);
    vlcWeight->setUnit(tr("kg"));
    vlcWeight->setValues(1, 100, weightValues, QString());
    vlcWeight->setText(tr("Last"));


    vlcDistance = new ValueControl(VALUE, categoryScrollArea);
    vlcDistance->setUnit(tr("m"));
    vlcDistance->setValues(0, 20, distanceValues, QString());
    vlcDistance->setText(tr("Weg"));



    QVector<QString>* options = new QVector<QString>();
    options->append(tr("Bockrollen"));
    options->append(tr("Bremsen"));

    topGroupLayout->addWidget(vlcGraspType);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(vlcHandlingType);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(vlcWeight);
    topGroupLayout->addWidget(new Separator(Qt::Horizontal, 3, this));
    topGroupLayout->addWidget(vlcDistance);


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
        vlcWeight->setValues(1, 2000, heavyWeightValues, QString());
    else
        vlcWeight->setValues(1, 100, weightValues, QString());
}

LoadHandlingView::~LoadHandlingView()
{
}

// GETTER

QString LoadHandlingView::getHandlingType() const {
    return vlcHandlingType->getText();
}

QString LoadHandlingView::getGraspType() const{
    return vlcGraspType->getText();
}

int LoadHandlingView::getWeight() {
    return vlcWeight->getValue();
}

int LoadHandlingView::getDistance(){
    return vlcDistance->getValue();
}

// SETTER

void LoadHandlingView::setHandlingType(const QString &handlingType){
    vlcHandlingType->setText(handlingType);
}

void LoadHandlingView::setGraspType(const QString &graspType){
    vlcGraspType->setText(graspType);
}

void LoadHandlingView::setWeight(int &weight){
    vlcWeight->setValue(weight);
}

void LoadHandlingView::setDistance(int &distance){
    vlcDistance->setValue(distance);
}
