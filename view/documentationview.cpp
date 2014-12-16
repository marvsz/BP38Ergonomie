#include "documentationview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QIcon>
#include <QUrl>
#include <QList>
#include <QStringList>
#include "angleview.h"
#include "transportview.h"
#include "actionforceview.h"
#include "executionconditionview.h"
#include "separator.h"

/**
 * @brief Constructs a DocumentationView widget which is a child of parent.
 * @param parent If parent is 0, the new widget becomes a window.
 * If parent is another widget, this widget becomes a child window inside parent.
 * The new widget is deleted when its parent is deleted.
 */
DocumentationView::DocumentationView(QWidget *parent) :
    QWidget(parent)
{
    //QHBoxLayout* tabBarLayout = new QHBoxLayout;
    QGridLayout *mainLayout = new QGridLayout;

    // CAMERA BUTTON INITIALIZATION
    cameraButton = new QPushButton;
    cameraButton->setObjectName("cameraButton");

    // NO FUNCTION YET
    backButton = new QPushButton("< Zurück");
    backButton->setMaximumSize(100, 40);
    backButton->setObjectName("backButton");


    // TAB SOLUTION
    /*
    // ADD QTABWIDGET
    this->tabs = new QTabWidget(this);
    // ADD TABS
    tabs->addTab(new AngleView, "Körperhaltung");
    tabs->addTab(new TransportView, "Lastenhandhabung");
    tabs->addTab(new ActionForceView, "Aktionskraft");
    tabs->addTab(new ExecutionConditionView, "Ausführungsbedingungen");
    tabs->addTab(timer->btnView, "AV anzeigen");*/

    // COMBOBOX SOLUTON
    QList<QString> viewNames = QList<QString>();
    viewNames.append("Körperhaltung");
    viewNames.append("Lastenhandhabung");
    viewNames.append("Aktionskraft");
    viewNames.append("Ausführungbedingungen");
    this->views = new QComboBox();
    this->views->setMinimumSize(280, 40);
    this->views->addItems(QStringList(viewNames));

    mainContent = new QStackedWidget;
    mainContent->addWidget(new AngleView);
    mainContent->addWidget(new TransportView);
    mainContent->addWidget(new ActionForceView);
    mainContent->addWidget(new ExecutionConditionView);

    connect(views, SIGNAL(currentIndexChanged(int)), mainContent, SLOT(setCurrentIndex(int)));

    // INCLUDE QML-CAMERA
    this->cameraView.setResizeMode(QQuickView::SizeRootObjectToView);
    this->cameraView.setSource(QUrl("qrc:///declarative-camera.qml"));
    this->cameraView.setFlags(Qt::FramelessWindowHint);

    connect(cameraView.engine(), SIGNAL(quit()), this, SLOT(hideCamera()));
    connect(cameraButton, SIGNAL(clicked()), this, SLOT(showCamera()));

    // ADD TIMER
    this->timer = new StopWatch;

    /*
    //LAYOUT
    //tabBarLayout->addWidget(backButton);
    tabBarLayout->addWidget(this->tabs->tabBar());
    tabBarLayout->addWidget(cameraButton);
    mainLayout->addLayout(tabBarLayout);*/

    // GRID LAYOUT
    mainLayout->addWidget(backButton, 0, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(views, 0, 1, 1, 1, Qt::AlignHCenter);
    mainLayout->addWidget(cameraButton, 0, 2, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 1, 0, 1, 3, Qt::AlignTop);
    mainLayout->addWidget(mainContent, 2, 0, 1, 3, 0);
    mainLayout->addWidget(new Separator(Qt::Horizontal, 3, this), 3, 0, 1, 3, Qt::AlignBottom);
    mainLayout->addWidget(timer, 4, 0, 1, 3,Qt::AlignBottom);
    setLayout(mainLayout);
}

/**
 * @brief Opens a view for the the QML-Camera
 */
void DocumentationView::showCamera(){
    this->cameraView.show();
}

/**
 * @brief Closes the view for the the QML-Camera
 */
void DocumentationView::hideCamera(){
    this->cameraView.hide();
}
