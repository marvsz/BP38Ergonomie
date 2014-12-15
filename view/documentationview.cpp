#include "documentationview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QUrl>
#include "angleview.h"
#include "transportview.h"
#include "actionforceview.h"
#include "executionconditionview.h"

/**
 * @brief Constructs a DocumentationView widget which is a child of parent.
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
DocumentationView::DocumentationView(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout* tabBarLayout = new QHBoxLayout;
    tabBarLayout->setAlignment(tabBarLayout, Qt::AlignBottom);

    //backButton = new QPushButton("< Zurück");

    // CAMERA BUTTON INITIALIZATION
    cameraButton = new QPushButton;
    cameraButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    cameraButton->setIcon(QIcon(":/icons/camera.png"));
    cameraButton->setIconSize(QSize(30,30));
<<<<<<< HEAD
=======
    cameraButton->setObjectName("cameraButton");
>>>>>>> origin/master

    // ADD QTABWIDGET AND STOPWATCH
    this->tabs = new QTabWidget(this);
    this->timer = new StopWatch;

    // ADD TABS
    tabs->addTab(new AngleView, "Körperhaltung");
    tabs->addTab(new TransportView, "Lastenhandhabung");
    tabs->addTab(new ActionForceView, "Aktionskraft");
    tabs->addTab(new ExecutionConditionView, "Ausführungsbedingungen");
    tabs->addTab(timer->btnView, "AV anzeigen");

    // INCLUDE QML-CAMERA
    this->view.setResizeMode(QQuickView::SizeRootObjectToView);
    this->view.setSource(QUrl("qrc:///declarative-camera.qml"));
    this->view.resize(600, 480);
    connect(view.engine(), SIGNAL(quit()), this, SLOT(hideCamera()));
    connect(cameraButton, SIGNAL(clicked()), this, SLOT(showCamera()));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    //LAYOUT
    //tabBarLayout->addWidget(backButton);
    tabBarLayout->addWidget(this->tabs->tabBar());
    tabBarLayout->addWidget(cameraButton);

    mainLayout->addLayout(tabBarLayout);
    mainLayout->addWidget(tabs);
    mainLayout->addWidget(timer);
    this->setLayout(mainLayout);
}

/**
 * @brief opens a view for the the QML-Camera
 */
void DocumentationView::showCamera(){
    this->view.show();
}

/**
 * @brief closes the view for the the QML-Camera
 */
void DocumentationView::hideCamera(){
    this->view.hide();
}
