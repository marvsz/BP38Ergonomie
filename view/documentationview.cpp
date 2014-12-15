#include "documentationview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QUrl>
#include "angleview.h"
#include "transportview.h"
#include "actionforceview.h"
#include "executionconditionview.h"

DocumentationView::DocumentationView(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* tabBarLayout = new QHBoxLayout;
    //backButton = new QPushButton("< Zurück");
    cameraButton = new QPushButton;
    cameraButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    cameraButton->setIcon(QIcon(":/icons/camera.png"));
    cameraButton->setIconSize(QSize(30,30));

    this->tabs = new QTabWidget(this);
    this->timer = new StopWatch;

    tabs->addTab(new AngleView, "Körperhaltung");
    tabs->addTab(new TransportView, "Lastenhandhabung");
    tabs->addTab(new ActionForceView, "Aktionskraft");
    tabs->addTab(new ExecutionConditionView, "Ausführungsbedingungen");
    tabs->addTab(timer->btnView, "AV anzeigen");

    this->view.setResizeMode(QQuickView::SizeRootObjectToView);
    this->view.setSource(QUrl("qrc:///declarative-camera.qml"));
    this->view.resize(600, 480);
    connect(view.engine(), SIGNAL(quit()), this, SLOT(hideCamera()));
    connect(cameraButton, SIGNAL(clicked()), this, SLOT(showCamera()));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    //tabBarLayout->addWidget(backButton);
    tabBarLayout->addWidget(this->tabs->tabBar());
    tabBarLayout->addWidget(cameraButton);

    mainLayout->addLayout(tabBarLayout);
    mainLayout->addWidget(tabs);
    mainLayout->addWidget(timer);
    this->setLayout(mainLayout);


}

void DocumentationView::showCamera(){
    this->view.show();
}

void DocumentationView::hideCamera(){
    this->view.hide();
}
