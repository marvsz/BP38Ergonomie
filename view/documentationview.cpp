#include "documentationview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include "angleview.h"
#include "transportview.h"
#include "actionforceview.h"
#include "executionconditionview.h"

DocumentationView::DocumentationView(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* tabBarLayout = new QHBoxLayout;
    backButton = new QPushButton("< Zurück");
    cameraButton = new QPushButton;
    cameraButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    cameraButton->setIcon(QIcon(":/specialPurposeIcons/camera.png"));
    cameraButton->setIconSize(QSize(50,50));

    this->tabs = new QTabWidget(this);
    this->timer = new StopWatch;

    tabs->addTab(new AngleView, "Körperhaltung");
    tabs->addTab(new TransportView, "Lastenhandhabung");
    tabs->addTab(new ActionForceView, "Aktionskraft");
    tabs->addTab(new ExecutionConditionView, "Ausführungsbedingungen");

    QVBoxLayout *mainLayout = new QVBoxLayout;

    tabBarLayout->addWidget(backButton);
    tabBarLayout->addWidget(this->tabs->tabBar());
    tabBarLayout->addWidget(cameraButton);

    mainLayout->addLayout(tabBarLayout);
    mainLayout->addWidget(tabs);
    mainLayout->addWidget(timer);
    this->setLayout(mainLayout);


}
